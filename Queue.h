//
// Created by jcard on 3/07/2026.
//

#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include <vector>

#include "Process.h"

/**
 * @enum Algorithm
 * @brief Representa los algoritmos de planificación soportados por una cola.
 */
enum Algorithm
{
    /// Round Robin.
    RR,

    /// Shortest Job First.
    SJF
};

/**
 * @class Queue
 * @brief Representa una cola de planificación dentro del algoritmo MLQ.
 *
 * Cada objeto Queue implementa uno de los algoritmos de planificación
 * soportados por el proyecto:
 *
 * - Round Robin.
 * - Shortest Job First (SJF).
 *
 * Dependiendo del algoritmo seleccionado, la clase utiliza una estructura
 * de datos diferente para almacenar los procesos.
 */
class Queue
{
private:

    /// Identificador de la cola.
    int id;

    /// Algoritmo utilizado por la cola.
    Algorithm algorithm;

    /// Quantum utilizado por Round Robin.
    int quantum;

    /// Cola FIFO utilizada cuando el algoritmo es Round Robin.
    std::queue<Process*> rrQueue;

    /// Vector utilizado para mantener ordenados los procesos en SJF.
    std::vector<Process*> sjfQueue;

public:

    /**
     * @brief Constructor de la cola.
     *
     * @param id Identificador de la cola.
     * @param algorithm Algoritmo utilizado.
     * @param quantum Quantum (solo para Round Robin).
     */
    Queue(int id,
          Algorithm algorithm,
          int quantum = 0);

    /**
     * @brief Inserta un proceso dentro de la cola.
     *
     * Si la cola es Round Robin, el proceso se agrega al final.
     * Si la cola es SJF, el vector se ordena automáticamente
     * según el Burst Time.
     *
     * @param process Proceso que será agregado.
     */
    void push(Process* process);

    /**
     * @brief Obtiene y elimina el siguiente proceso a ejecutar.
     *
     * @return Proceso seleccionado.
     */
    Process* pop();

    /**
     * @brief Obtiene el siguiente proceso sin eliminarlo.
     *
     * @return Primer proceso de la cola.
     */
    Process* front();

    /**
     * @brief Verifica si la cola está vacía.
     *
     * @return true si no existen procesos.
     */
    bool empty() const;

    /**
     * @brief Devuelve el quantum de la cola.
     *
     * @return Quantum.
     */
    int getQuantum() const;

    /**
     * @brief Devuelve el algoritmo utilizado.
     *
     * @return Tipo de algoritmo.
     */
    Algorithm getAlgorithm() const;

    /**
     * @brief Devuelve el identificador de la cola.
     *
     * @return Id de la cola.
     */
    int getId() const;
};

#endif