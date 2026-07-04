//
// Created by jcard on 3/07/2026.
//

//
// Created by jcard on 3/07/2026.
//

#ifndef PROCESS_H
#define PROCESS_H

#include <string>

/**
 * @class Process
 * @brief Representa un proceso dentro de la simulación del algoritmo MLQ.
 *
 * Esta clase almacena toda la información relacionada con un proceso,
 * incluyendo los datos de entrada (identificador, tiempo de llegada,
 * tiempo de ráfaga y cola de planificación) y las métricas calculadas
 * durante la ejecución del algoritmo.
 */
class Process
{
private:

    /// Identificador del proceso (A, B, C, etc.).
    std::string id;

    /// Tiempo total de CPU requerido por el proceso.
    int burstTime;

    /// Instante en el que el proceso llega al sistema.
    int arrivalTime;

    /// Cola de planificación a la que pertenece el proceso.
    int queue;

    /// Tiempo de CPU restante para finalizar la ejecución.
    int remainingTime;

    /// Tiempo total de espera del proceso.
    int waitingTime;

    /// Tiempo en el que el proceso termina completamente.
    int completionTime;

    /// Tiempo transcurrido hasta que el proceso recibe CPU por primera vez.
    int responseTime;

    /// Tiempo total que el proceso permanece en el sistema.
    int turnaroundTime;

    /// Indica si el proceso ya comenzó a ejecutarse.
    bool started;

    /// Indica si el proceso ya fue agregado a la cola correspondiente.
    bool admitted;

public:

    /**
     * @brief Constructor por defecto.
     */
    Process();

    /**
     * @brief Constructor que inicializa un proceso.
     *
     * @param id Identificador del proceso.
     * @param burstTime Tiempo de ráfaga.
     * @param arrivalTime Tiempo de llegada.
     * @param queue Cola de planificación asignada.
     */
    Process(std::string id,
            int burstTime,
            int arrivalTime,
            int queue);

    //=====================
    // Getters
    //=====================

    /// Obtiene el identificador del proceso.
    std::string getId() const;

    /// Obtiene el Burst Time.
    int getBurstTime() const;

    /// Obtiene el Arrival Time.
    int getArrivalTime() const;

    /// Obtiene la cola de planificación.
    int getQueue() const;

    /// Obtiene el tiempo restante de ejecución.
    int getRemainingTime() const;

    /// Obtiene el Waiting Time.
    int getWaitingTime() const;

    /// Obtiene el Completion Time.
    int getCompletionTime() const;

    /// Obtiene el Response Time.
    int getResponseTime() const;

    /// Obtiene el Turnaround Time.
    int getTurnaroundTime() const;

    /// Indica si el proceso ya comenzó a ejecutarse.
    bool hasStarted() const;

    /// Indica si el proceso ya fue admitido en una cola.
    bool isAdmitted() const;

    //=====================
    // Setters
    //=====================

    /// Actualiza el tiempo restante del proceso.
    void setRemainingTime(int remainingTime);

    /// Actualiza el Waiting Time.
    void setWaitingTime(int waitingTime);

    /// Actualiza el Completion Time.
    void setCompletionTime(int completionTime);

    /// Actualiza el Response Time.
    void setResponseTime(int responseTime);

    /// Actualiza el Turnaround Time.
    void setTurnaroundTime(int turnaroundTime);

    /// Marca si el proceso ya comenzó a ejecutarse.
    void setStarted(bool started);

    /// Marca si el proceso ya fue admitido en una cola.
    void setAdmitted(bool admitted);
};

#endif