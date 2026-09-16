# Laboratorio 2 - Evaluación del desempeño de algoritmos y comportamiento de la memoria caché

## Descripción

Este repositorio contiene las implementaciones y experimentos realizados para el **Laboratorio 2 de Programación Paralela**.

El laboratorio analiza el desempeño de diferentes formas de acceso y procesamiento de matrices, considerando principalmente el uso de la **memoria caché** y el movimiento de datos.

Los casos estudiados son:

1. Bucles anidados del Capítulo 2 de Pacheco (**row-major vs. column-major**).
2. Multiplicación clásica de matrices mediante tres bucles anidados.
3. Multiplicación de matrices por bloques mediante seis bucles anidados.
4. Análisis del movimiento de datos y comportamiento de la memoria caché.
5. Evaluación mediante **Valgrind, Cachegrind y KCachegrind**.

---

## Estructura del repositorio

```text
lab2-cache/
│
├── README.md
│
├── src/
│   ├── bucles.cpp
│   ├── clasica.cpp
│   ├── bloques.cpp
│   └── cachetest.cpp
│
└── resultados/
    └── cachegrind/
        ├── cg_clasica_256.out
        ├── cg_clasica_512.out
        ├── cg_clasica_800.out
        ├── cg_bloques_256.out
        ├── cg_bloques_512.out
        └── cg_bloques_800.out
```

### Descripción de los directorios

| Directorio               | Descripción                                     |
| ------------------------ | ----------------------------------------------- |
| `src/`                   | Contiene los programas fuente en C++.           |
| `resultados/cachegrind/` | Contiene los archivos generados por Cachegrind. |

---

## Requisitos

Para ejecutar los experimentos se necesita:

* **g++** con soporte para C++11 o superior.
* **Valgrind** para el análisis de memoria caché.
* **KCachegrind** para visualizar los resultados de Cachegrind.

### Instalación en Ubuntu

```bash
sudo apt update
sudo apt install g++ valgrind kcachegrind
```

---

## Compilación

Desde el directorio raíz del proyecto:

```bash
g++ -O3 -o bucles src/bucles.cpp
g++ -O3 -o clasica src/clasica.cpp
g++ -O3 -o bloques src/bloques.cpp
g++ -O0 -g -o cachetest src/cachetest.cpp
```

> **Nota:** `cachetest` se compila con `-O0` para evitar optimizaciones del compilador que puedan modificar el comportamiento del programa durante las mediciones realizadas con Cachegrind.

---

# Ejecución

## Punto 1: Bucles anidados

Ejecutar:

```bash
./bucles 500 5
./bucles 1000 5
./bucles 2000 5
./bucles 3000 5
```

Los argumentos corresponden a:

```text
./bucles <tamaño_matriz> <repeticiones>
```

Por ejemplo:

```bash
./bucles 1000 5
```

ejecuta el experimento utilizando una matriz de tamaño `1000 × 1000` y realiza `5` repeticiones.

---

## Punto 2: Multiplicación clásica de matrices

Ejecutar:

```bash
./clasica
```

El programa realiza automáticamente las pruebas para los siguientes tamaños de matriz:

```text
N = 100, 200, 300, 400, 500, 600, 800, 1000
```

La multiplicación utiliza el método clásico mediante **tres bucles anidados**.

---

## Punto 3: Multiplicación de matrices por bloques

Ejecutar:

```bash
./bloques
```

El programa compara la multiplicación clásica con la multiplicación por bloques utilizando los siguientes tamaños de bloque:

```text
B = 16, 32, 64, 128
```

Las pruebas se realizan para:

```text
N = 200, 400, 600, 800, 1000
```

La multiplicación por bloques busca mejorar el aprovechamiento de la **memoria caché**, procesando los datos en grupos que pueden permanecer temporalmente en los niveles de caché.

---

# Análisis de memoria caché

## Punto 5: Cachegrind

Para analizar la multiplicación clásica con una matriz de `256 × 256`:

```bash
valgrind \
    --tool=cachegrind \
    --cache-sim=yes \
    --cachegrind-out-file=resultados/cachegrind/cg_clasica_256.out \
    ./cachetest clasica 256
```

Para analizar la multiplicación por bloques:

```bash
valgrind \
    --tool=cachegrind \
    --cache-sim=yes \
    --cachegrind-out-file=resultados/cachegrind/cg_bloques_256.out \
    ./cachetest bloques 256 64
```

En este caso, `64` corresponde al tamaño del bloque.

---

## Visualización de resultados con `cg_annotate`

Para obtener un resumen de los resultados directamente en la terminal:

```bash
cg_annotate \
    --show=Ir,Dr,Dw,I1mr,D1mr,D1mw,ILmr,DLmr,DLmw \
    resultados/cachegrind/cg_clasica_256.out | head -40
```

Entre las métricas obtenidas se encuentran:

* `Ir`: instrucciones ejecutadas.
* `Dr`: lecturas de datos.
* `Dw`: escrituras de datos.
* `I1mr`: fallos de caché de instrucciones L1.
* `D1mr`: fallos de lectura de datos en caché L1.
* `D1mw`: fallos de escritura de datos en caché L1.
* `ILmr`: fallos de caché de instrucciones de último nivel.
* `DLmr`: fallos de lectura de datos de último nivel.
* `DLmw`: fallos de escritura de datos de último nivel.

---

## Visualización con KCachegrind

Para abrir los resultados de la multiplicación clásica:

```bash
kcachegrind resultados/cachegrind/cg_clasica_256.out
```

Para abrir los resultados de la multiplicación por bloques:

```bash
kcachegrind resultados/cachegrind/cg_bloques_256.out
```

KCachegrind permite visualizar de manera gráfica las métricas obtenidas por Cachegrind y analizar dónde se concentra el trabajo del programa.

---

# Resultados

Los archivos `.out` ubicados en:

```text
resultados/cachegrind/
```

contienen los resultados completos obtenidos mediante **Cachegrind** para las diferentes combinaciones de algoritmo y tamaño de matriz.

Estos archivos pueden analizarse utilizando:

```bash
cg_annotate
```

o mediante:

```bash
kcachegrind
```

---


