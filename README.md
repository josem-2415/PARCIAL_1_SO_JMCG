# # Multi-Level Queue (MLQ) Scheduler en C++

Implementación de un algoritmo de planificación **Multi-Level Queue (MLQ)** desarrollada en **C++** como proyecto para la asignatura de **Sistemas Operativos**.

El programa simula la planificación de procesos utilizando tres colas con diferentes algoritmos de planificación y calcula las principales métricas de rendimiento de cada proceso.

---

## Características

- Implementación del algoritmo **Multi-Level Queue (MLQ)**.
- Tres colas de planificación:
    - **Round Robin (Quantum = 1)**
    - **Round Robin (Quantum = 3)**
    - **Shortest Job First (SJF) no expropiativo**
- Los procesos **no cambian de cola** durante toda su ejecución.
- Lectura automática de procesos desde un archivo `.txt`.
- Escritura automática de los resultados sobre el mismo archivo.
- Cálculo de las métricas:
    - Waiting Time (WT)
    - Completion Time (CT)
    - Response Time (RT)
    - Turnaround Time (TAT)
- Cálculo de los promedios de todas las métricas.

---

# Estructura del proyecto

```
PARCIAL_SO
│
├── main.cpp
├── Process.h
├── Process.cpp
├── Queue.h
├── Queue.cpp
├── Scheduler.h
├── Scheduler.cpp
├── FileManager.h
├── FileManager.cpp
├── mlq001.txt
├── CMakeLists.txt
└── README.md
```

---

# Diseño del proyecto

El proyecto fue desarrollado utilizando programación orientada a objetos.

## Process

Representa un proceso del sistema operativo.

Almacena:

- Etiqueta
- Burst Time
- Arrival Time
- Cola asignada
- Tiempo restante
- Waiting Time
- Completion Time
- Response Time
- Turnaround Time

Además incorpora dos indicadores auxiliares:

- `started`
- `admitted`

que permiten controlar el estado del proceso durante la simulación.

---

## Queue

Implementa las colas de planificación.

Dependiendo del algoritmo utiliza estructuras diferentes:

### Round Robin

Implementado mediante

```cpp
std::queue<Process*>
```

manteniendo el orden FIFO de los procesos.

### Shortest Job First

Implementado mediante

```cpp
std::vector<Process*>
```

ordenado por **Burst Time**, permitiendo seleccionar siempre el proceso más corto.

---

## Scheduler

Es el núcleo del algoritmo.

Se encarga de:

- controlar el tiempo global de la simulación
- incorporar procesos cuando llegan
- seleccionar la cola de mayor prioridad
- ejecutar RR o SJF
- calcular todas las métricas

Prioridad entre colas:

```
RR (Quantum = 1)
        ↓
RR (Quantum = 3)
        ↓
SJF
```

Las colas poseen prioridad fija.

Un proceso **permanece siempre en la cola indicada por el archivo de entrada**.

---

## FileManager

Responsable de:

- leer el archivo de entrada
- crear los procesos
- escribir los resultados finales

---

# Archivo de entrada

Ejemplo:

```text
# Archivo: mlq001.txt
# Etiqueta; BT; AT; Q

A;6;0;1
B;9;0;1
C;10;0;2
D;15;0;2
E;8;0;3
```

---

# Archivo de salida

```text
# Archivo: mlq001.txt
# Etiqueta; BT; AT; Q; WT; CT; RT; TAT

A;6;0;1;5;11;0;11
B;9;0;1;6;15;1;15
C;10;0;2;24;34;15;34
D;15;0;2;25;40;18;40
E;8;0;3;40;48;40;48

# WT=20.0; CT=29.6; RT=14.8; TAT=29.6
```

---

# Métricas calculadas

## Waiting Time (WT)

Tiempo que un proceso permanece esperando CPU.

```
WT = TAT - BT
```

---

## Completion Time (CT)

Instante en que finaliza completamente el proceso.

---

## Turnaround Time (TAT)

Tiempo total que el proceso permanece en el sistema.

```
TAT = CT - AT
```

---

## Response Time (RT)

Tiempo transcurrido desde la llegada del proceso hasta que recibe CPU por primera vez.

---

# Compilación

Con CMake:

```bash
mkdir build
cd build

cmake ..
cmake --build .
```

O directamente desde CLion.

---

# Ejecución

El programa:

1. Lee el archivo `mlq001.txt`.
2. Ejecuta la simulación del algoritmo MLQ.
3. Calcula las métricas.
4. Sobrescribe el archivo con los resultados.
5. Imprime el contenido del archivo en consola.

---

# Tecnologías utilizadas

- C++
- STL
- CMake
- CLion

---

# Autor

**Jose Manuel Cardona Gil**

Proyecto desarrollado para la asignatura de **Sistemas Operativos**.