//
// Created by jcard on 3/07/2026.
//

#include "Scheduler.h"

Scheduler::Scheduler()
    : rr1(1, RR, 1),
      rr3(2, RR, 3),
      sjf(3, SJF),
      currentTime(0)
{
}

void Scheduler::loadProcesses(const std::vector<Process*>& processes)
{
    this->processes = processes;
}

const std::vector<Process*>& Scheduler::getProcesses() const
{
    return processes;
}

void Scheduler::execute()
{
    while (!allFinished())
    {
        addArrivedProcesses();

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

void Scheduler::addArrivedProcesses()
{
    for (Process* process : processes)
    {
        if (!process->isAdmitted() &&
            process->getArrivalTime() <= currentTime)
        {
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

void Scheduler::executeRR(Queue& queue)
{
    Process* process = queue.pop();

    if (!process->hasStarted())
    {
        process->setStarted(true);
        process->setResponseTime(currentTime - process->getArrivalTime());
    }

    int quantum = queue.getQuantum();
    int executed = (process->getRemainingTime() < quantum)
                     ? process->getRemainingTime()
                     : quantum;

    process->setRemainingTime(process->getRemainingTime() - executed);
    currentTime += executed;

    addArrivedProcesses();

    if (process->getRemainingTime() == 0)
    {
        finishProcess(process);
    }
    else
    {
        queue.push(process);
    }
}

void Scheduler::executeSJF()
{
    Process* process = sjf.pop();

    if (!process->hasStarted())
    {
        process->setStarted(true);
        process->setResponseTime(currentTime - process->getArrivalTime());
    }

    currentTime += process->getRemainingTime();
    process->setRemainingTime(0);

    addArrivedProcesses();

    finishProcess(process);
}

void Scheduler::finishProcess(Process* process)
{
    process->setCompletionTime(currentTime);

    process->setTurnaroundTime(
        process->getCompletionTime() -
        process->getArrivalTime());

    process->setWaitingTime(
        process->getTurnaroundTime() -
        process->getBurstTime());
}

bool Scheduler::allFinished() const
{
    for (Process* process : processes)
    {
        if (process->getRemainingTime() > 0)
            return false;
    }

    return true;
}
