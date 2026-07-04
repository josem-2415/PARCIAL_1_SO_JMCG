//
// Created by jcard on 3/07/2026.
//

//
// Created by jcard on 3/07/2026.
//

#include "Process.h"

/**
 * Constructor por defecto.
 *
 * Inicializa todos los atributos del proceso con valores
 * predeterminados para evitar datos sin inicializar.
 */
Process::Process()
{
    id = "";
    burstTime = 0;
    arrivalTime = 0;
    queue = 0;

    remainingTime = 0;

    waitingTime = 0;
    completionTime = 0;
    responseTime = -1;
    turnaroundTime = 0;

    started = false;
    admitted = false;
}

/**
 * Constructor parametrizado.
 *
 * Inicializa el proceso con la información leída desde el archivo
 * de entrada. El tiempo restante comienza siendo igual al Burst Time.
 */
Process::Process(std::string id,
                 int burstTime,
                 int arrivalTime,
                 int queue)
{
    this->id = id;
    this->burstTime = burstTime;
    this->arrivalTime = arrivalTime;
    this->queue = queue;

    // Al inicio aún no se ha ejecutado ninguna unidad de CPU.
    remainingTime = burstTime;

    waitingTime = 0;
    completionTime = 0;
    responseTime = -1;
    turnaroundTime = 0;

    started = false;
    admitted = false;
}

//======================================================
// Métodos Getters
// Permiten consultar la información del proceso.
//======================================================

std::string Process::getId() const
{
    return id;
}

int Process::getBurstTime() const
{
    return burstTime;
}

int Process::getArrivalTime() const
{
    return arrivalTime;
}

int Process::getQueue() const
{
    return queue;
}

int Process::getRemainingTime() const
{
    return remainingTime;
}

int Process::getWaitingTime() const
{
    return waitingTime;
}

int Process::getCompletionTime() const
{
    return completionTime;
}

int Process::getResponseTime() const
{
    return responseTime;
}

int Process::getTurnaroundTime() const
{
    return turnaroundTime;
}

bool Process::hasStarted() const
{
    return started;
}

bool Process::isAdmitted() const
{
    return admitted;
}

//======================================================
// Métodos Setters
// Permiten actualizar las métricas calculadas durante
// la simulación del algoritmo MLQ.
//======================================================

void Process::setRemainingTime(int remainingTime)
{
    this->remainingTime = remainingTime;
}

void Process::setWaitingTime(int waitingTime)
{
    this->waitingTime = waitingTime;
}

void Process::setCompletionTime(int completionTime)
{
    this->completionTime = completionTime;
}

void Process::setResponseTime(int responseTime)
{
    this->responseTime = responseTime;
}

void Process::setTurnaroundTime(int turnaroundTime)
{
    this->turnaroundTime = turnaroundTime;
}

void Process::setStarted(bool started)
{
    this->started = started;
}

void Process::setAdmitted(bool admitted)
{
    this->admitted = admitted;
}