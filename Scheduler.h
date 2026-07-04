//
// Created by jcard on 3/07/2026.
//

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>

#include "Process.h"
#include "Queue.h"

/**
 * @class Scheduler
 * @brief Implementa el algoritmo de planificación Multi-Level Queue (MLQ).
 *
 * Esta clase constituye el núcleo de la simulación. Su responsabilidad es
 * administrar el tiempo del sistema, incorporar los procesos cuando llegan,
 * seleccionar la cola de mayor prioridad disponible y ejecutar el algoritmo
 * correspondiente hasta que todos los procesos finalicen.
 *
 * La implementación utiliza tres colas de planificación:
 *
 * • Cola 1: Round Robin con quantum de 1.
 * • Cola 2: Round Robin con quantum de 3.
 * • Cola 3: Shortest Job First (SJF) no expropiativo.
 *
 * Las colas poseen prioridad fija:
 *
 * RR(q=1) > RR(q=3) > SJF
 *
 * Los procesos nunca cambian de cola durante su ejecución,
 * ya que el algoritmo implementado corresponde a un MLQ y no
 * a un Multi-Level Feedback Queue (MLFQ).
 */
class Scheduler
{
private:

    /// Lista con todos los procesos cargados desde el archivo.
    std::vector<Process*> processes;

    /// Primera cola de planificación (Round Robin, quantum = 1).
    Queue rr1;

    /// Segunda cola de planificación (Round Robin, quantum = 3).
    Queue rr3;

    /// Tercera cola de planificación (Shortest Job First).
    Queue sjf;

    /// Tiempo actual de la simulación.
    int currentTime;

    /**
     * @brief Agrega los procesos cuyo tiempo de llegada ya se cumplió.
     *
     * Recorre todos los procesos del sistema y verifica si el
     * Arrival Time es menor o igual al tiempo actual.
     *
     * Cada proceso es agregado únicamente una vez a la cola
     * correspondiente utilizando el atributo "admitted".
     */
    void addArrivedProcesses();

    /**
     * @brief Ejecuta un proceso utilizando Round Robin.
     *
     * El proceso recibe CPU durante un quantum o hasta terminar
     * completamente su ejecución.
     *
     * Si el proceso no finaliza, vuelve al final de la misma cola,
     * respetando el comportamiento del algoritmo MLQ.
     *
     * @param queue Cola Round Robin que será ejecutada.
     */
    void executeRR(Queue& queue);

    /**
     * @brief Ejecuta el algoritmo Shortest Job First.
     *
     * Selecciona el proceso con menor Burst Time y lo ejecuta
     * completamente hasta finalizar, ya que el algoritmo utilizado
     * es SJF no expropiativo.
     */
    void executeSJF();

    /**
     * @brief Calcula las métricas finales de un proceso.
     *
     * Una vez que el proceso termina su ejecución, esta función
     * calcula:
     *
     * • Completion Time (CT)
     * • Turnaround Time (TAT)
     * • Waiting Time (WT)
     *
     * @param process Proceso que ha finalizado.
     */
    void finishProcess(Process* process);

    /**
     * @brief Verifica si todos los procesos finalizaron.
     *
     * @return true cuando no existen procesos pendientes.
     */
    bool allFinished() const;

public:

    /**
     * @brief Constructor del Scheduler.
     *
     * Inicializa las tres colas del algoritmo MLQ y el
     * reloj de la simulación.
     */
    Scheduler();

    /**
     * @brief Carga todos los procesos del sistema.
     *
     * @param processes Vector de procesos leído desde el archivo.
     */
    void loadProcesses(const std::vector<Process*>& processes);

    /**
     * @brief Ejecuta la simulación completa del algoritmo MLQ.
     *
     * Mientras existan procesos pendientes:
     *
     * 1. Agrega los procesos que hayan llegado.
     * 2. Selecciona la cola de mayor prioridad disponible.
     * 3. Ejecuta el algoritmo correspondiente.
     * 4. Actualiza el tiempo del sistema.
     */
    void execute();

    /**
     * @brief Devuelve todos los procesos con sus métricas calculadas.
     *
     * @return Vector de procesos.
     */
    const std::vector<Process*>& getProcesses() const;
};

#endif