//
// Created by jcard on 3/07/2026.
//

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>

#include "Process.h"
#include "Queue.h"

class Scheduler
{
private:

    // Colas del algoritmo MLQ
    Queue rr1;    // Round Robin - Quantum 1
    Queue rr3;    // Round Robin - Quantum 3
    Queue sjf;    // Shortest Job First (No Expropiativo)

    // Todos los procesos leídos del archivo
    std::vector<Process*> processes;

    // Tiempo global de la simulación
    int currentTime;

public:

    Scheduler();

    // Carga los procesos leídos por FileManager
    void loadProcesses(const std::vector<Process*>& processes);

    // Ejecuta toda la simulación
    void execute();

    // Devuelve los procesos ya con sus métricas calculadas
    const std::vector<Process*>& getProcesses() const;

private:

    // Agrega a las colas los procesos cuyo Arrival Time
    // sea igual al tiempo actual
    void addArrivedProcesses();

    // Ejecuta una cola Round Robin
    void executeRR(Queue& queue);

    // Ejecuta la cola SJF
    void executeSJF();

    // Calcula CT, WT y TAT cuando un proceso termina
    void finishProcess(Process* process);

    // Verifica si todos los procesos terminaron
    bool allFinished() const;
};

#endif