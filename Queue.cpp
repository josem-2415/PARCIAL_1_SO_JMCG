//
// Created by jcard on 3/07/2026.
//

#include "Queue.h"

#include <algorithm>

/**
 * Constructor de la cola.
 *
 * Inicializa la cola con su identificador, el algoritmo de planificación
 * correspondiente y el quantum (únicamente para Round Robin).
 */
Queue::Queue(int id,
             Algorithm algorithm,
             int quantum)
{
    this->id = id;
    this->algorithm = algorithm;
    this->quantum = quantum;
}

/**
 * Inserta un proceso dentro de la cola.
 *
 * El comportamiento depende del algoritmo utilizado:
 *
 * • Round Robin:
 *      El proceso se agrega al final de la cola FIFO.
 *
 * • Shortest Job First:
 *      El proceso se almacena en un vector que posteriormente
 *      es ordenado de menor a mayor Burst Time.
 */
void Queue::push(Process* process)
{
    if (algorithm == RR)
    {
        rrQueue.push(process);
    }
    else
    {
        sjfQueue.push_back(process);

        /*
         * Se ordena el vector para garantizar que siempre
         * el proceso con menor Burst Time sea el primero
         * en ejecutarse.
         *
         * Si dos procesos poseen el mismo Burst Time,
         * se utiliza el Arrival Time como criterio
         * de desempate.
         */
        std::sort(sjfQueue.begin(),
                  sjfQueue.end(),
                  [](Process* a, Process* b)
                  {
                      if (a->getBurstTime() == b->getBurstTime())
                          return a->getArrivalTime() < b->getArrivalTime();

                      return a->getBurstTime() < b->getBurstTime();
                  });
    }
}

/**
 * Obtiene el siguiente proceso de la cola sin eliminarlo.
 *
 * @return Proceso que será ejecutado.
 */
Process* Queue::front()
{
    if (algorithm == RR)
    {
        return rrQueue.front();
    }

    return sjfQueue.front();
}

/**
 * Obtiene y elimina el siguiente proceso de la cola.
 *
 * Para Round Robin se elimina el primer elemento
 * de la cola FIFO.
 *
 * Para SJF se elimina el primer elemento del vector,
 * que corresponde al proceso con menor Burst Time.
 *
 * @return Proceso seleccionado.
 */
Process* Queue::pop()
{
    Process* process;

    if (algorithm == RR)
    {
        process = rrQueue.front();
        rrQueue.pop();
    }
    else
    {
        process = sjfQueue.front();
        sjfQueue.erase(sjfQueue.begin());
    }

    return process;
}

/**
 * Verifica si la cola contiene procesos pendientes.
 *
 * @return true si la cola está vacía.
 */
bool Queue::empty() const
{
    if (algorithm == RR)
    {
        return rrQueue.empty();
    }

    return sjfQueue.empty();
}

/**
 * Devuelve el quantum asociado a la cola.
 *
 * Este valor únicamente es utilizado por
 * el algoritmo Round Robin.
 *
 * @return Quantum.
 */
int Queue::getQuantum() const
{
    return quantum;
}

/**
 * Devuelve el algoritmo utilizado por la cola.
 *
 * @return RR o SJF.
 */
Algorithm Queue::getAlgorithm() const
{
    return algorithm;
}

/**
 * Devuelve el identificador de la cola.
 *
 * @return Id de la cola.
 */
int Queue::getId() const
{
    return id;
}