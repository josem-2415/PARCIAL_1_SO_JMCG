//
// Created by jcard on 3/07/2026.
//

#include "Scheduler.h"

/**
 * @brief Constructor del Scheduler.
 *
 * Inicializa las tres colas que conforman el algoritmo MLQ:
 *
 * - Cola 1: Round Robin con quantum de 1.
 * - Cola 2: Round Robin con quantum de 3.
 * - Cola 3: Shortest Job First (SJF).
 *
 * Además, inicializa el reloj de la simulación en cero.
 */
Scheduler::Scheduler()
    : rr1(1, RR, 1),
      rr3(2, RR, 3),
      sjf(3, SJF),
      currentTime(0)
{
}

/**
 * @brief Carga todos los procesos que serán planificados.
 *
 * Los procesos son almacenados dentro del Scheduler para
 * posteriormente ejecutar la simulación.
 *
 * @param processes Vector con todos los procesos leídos desde el archivo.
 */
void Scheduler::loadProcesses(const std::vector<Process*>& processes)
{
    this->processes = processes;
}

/**
 * @brief Devuelve la lista completa de procesos.
 *
 * Este método es utilizado principalmente por FileManager
 * para escribir las métricas finales en el archivo.
 *
 * @return Vector de procesos.
 */
const std::vector<Process*>& Scheduler::getProcesses() const
{
    return processes;
}

/**
 * @brief Ejecuta la simulación completa del algoritmo MLQ.
 *
 * Mientras existan procesos pendientes:
 *
 * 1. Se agregan los procesos cuyo tiempo de llegada ya se cumplió.
 * 2. Se selecciona la cola de mayor prioridad disponible.
 * 3. Se ejecuta el algoritmo correspondiente.
 *
 * La prioridad entre colas es:
 *
 * RR (Quantum = 1)
 *      ↓
 * RR (Quantum = 3)
 *      ↓
 * SJF
 *
 * Si no existe ningún proceso listo para ejecutarse,
 * simplemente se incrementa el reloj del sistema.
 */
void Scheduler::execute()
{
    while (!allFinished())
    {
        // Agregar procesos que ya hayan llegado al sistema.
        addArrivedProcesses();

        /*
         * Siempre se ejecuta primero la cola
         * con mayor prioridad.
         */
        if (!rr1.empty())
            executeRR(rr1);

        else if (!rr3.empty())
            executeRR(rr3);

        else if (!sjf.empty())
            executeSJF();

        else
            currentTime++;
    }
}

/**
 * @brief Incorpora al sistema los procesos que ya llegaron.
 *
 * Recorre la lista completa de procesos y verifica
 * si el Arrival Time ya fue alcanzado.
 *
 * Cada proceso se agrega únicamente una vez utilizando
 * el atributo "admitted".
 */
void Scheduler::addArrivedProcesses()
{
    for (Process* process : processes)
    {
        if (!process->isAdmitted() &&
            process->getArrivalTime() <= currentTime)
        {
            /*
             * Cada proceso es enviado
             * a la cola indicada en el archivo.
             *
             * En un MLQ los procesos nunca
             * cambian de cola.
             */
            switch (process->getQueue())
            {
            case 1:
                rr1.push(process);
                break;

            case 2:
                rr3.push(process);
                break;

            case 3:
                sjf.push(process);
                break;
            }

            process->setAdmitted(true);
        }
    }
}

/**
 * @brief Ejecuta una cola Round Robin.
 *
 * El proceso recibe CPU durante el quantum correspondiente
 * o hasta terminar completamente.
 *
 * Si aún le queda tiempo de ejecución,
 * vuelve al final de la misma cola.
 *
 * @param queue Cola Round Robin que será ejecutada.
 */
void Scheduler::executeRR(Queue& queue)
{
    Process* process = queue.pop();

    /*
     * La primera vez que un proceso recibe CPU
     * se calcula el Response Time.
     */
    if (!process->hasStarted())
    {
        process->setStarted(true);
        process->setResponseTime(currentTime - process->getArrivalTime());
    }

    int quantum = queue.getQuantum();

    /*
     * El proceso únicamente ejecuta
     * el tiempo correspondiente al quantum.
     */
    int executed = (process->getRemainingTime() < quantum)
                     ? process->getRemainingTime()
                     : quantum;

    process->setRemainingTime(process->getRemainingTime() - executed);

    currentTime += executed;

    /*
     * Durante la ejecución pueden haber llegado
     * nuevos procesos.
     */
    addArrivedProcesses();

    /*
     * Si terminó, se calculan las métricas.
     * De lo contrario vuelve al final
     * de la misma cola.
     */
    if (process->getRemainingTime() == 0)
    {
        finishProcess(process);
    }
    else
    {
        queue.push(process);
    }
}

/**
 * @brief Ejecuta la cola Shortest Job First.
 *
 * Se selecciona el proceso con menor Burst Time
 * y se ejecuta completamente.
 *
 * Como SJF es no expropiativo,
 * el proceso no puede ser interrumpido
 * hasta finalizar.
 */
void Scheduler::executeSJF()
{
    Process* process = sjf.pop();

    /*
     * Calcular Response Time únicamente
     * la primera vez que obtiene CPU.
     */
    if (!process->hasStarted())
    {
        process->setStarted(true);
        process->setResponseTime(currentTime - process->getArrivalTime());
    }

    /*
     * El proceso ejecuta toda su ráfaga.
     */
    currentTime += process->getRemainingTime();

    process->setRemainingTime(0);

    addArrivedProcesses();

    finishProcess(process);
}

/**
 * @brief Calcula las métricas finales de un proceso.
 *
 * Una vez finalizada la ejecución se calculan:
 *
 * Completion Time (CT)
 * Turnaround Time (TAT)
 * Waiting Time (WT)
 *
 * Response Time ya fue calculado la primera vez
 * que el proceso recibió CPU.
 *
 * @param process Proceso finalizado.
 */
void Scheduler::finishProcess(Process* process)
{
    /*
     * Tiempo en el que finaliza el proceso.
     */
    process->setCompletionTime(currentTime);

    /*
     * Tiempo total que el proceso permaneció
     * dentro del sistema.
     *
     * TAT = CT - AT
     */
    process->setTurnaroundTime(
        process->getCompletionTime() -
        process->getArrivalTime());

    /*
     * Tiempo total esperando CPU.
     *
     * WT = TAT - BT
     */
    process->setWaitingTime(
        process->getTurnaroundTime() -
        process->getBurstTime());
}

/**
 * @brief Verifica si todos los procesos finalizaron.
 *
 * Recorre todos los procesos comprobando
 * que su tiempo restante sea igual a cero.
 *
 * @return true si todos finalizaron.
 */
bool Scheduler::allFinished() const
{
    for (Process* process : processes)
    {
        if (process->getRemainingTime() > 0)
            return false;
    }

    return true;
}
