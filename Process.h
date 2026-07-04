//
// Created by jcard on 3/07/2026.
//

#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process
{
private:

    std::string id;

    int burstTime;
    int arrivalTime;
    int queue;

    int remainingTime;

    int waitingTime;
    int completionTime;
    int responseTime;
    int turnaroundTime;

    bool started;
    bool admitted;

public:

    Process();

    Process(std::string id,
            int burstTime,
            int arrivalTime,
            int queue);

    // Getters
    std::string getId() const;

    int getBurstTime() const;

    int getArrivalTime() const;

    int getQueue() const;

    int getRemainingTime() const;

    int getWaitingTime() const;

    int getCompletionTime() const;

    int getResponseTime() const;

    int getTurnaroundTime() const;

    bool hasStarted() const;

    bool isAdmitted() const;

    // Setters
    void setRemainingTime(int remainingTime);

    void setWaitingTime(int waitingTime);

    void setCompletionTime(int completionTime);

    void setResponseTime(int responseTime);

    void setTurnaroundTime(int turnaroundTime);

    void setStarted(bool started);

    void setAdmitted(bool admitted);
};

#endif