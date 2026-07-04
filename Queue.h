//
// Created by jcard on 3/07/2026.
//

#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include <vector>

#include "Process.h"

enum Algorithm
{
    RR,
    SJF
};

class Queue
{
private:

    int id;

    Algorithm algorithm;

    int quantum;

    std::queue<Process*> rrQueue;

    std::vector<Process*> sjfQueue;

public:

    Queue(int id,
          Algorithm algorithm,
          int quantum = 0);

    void push(Process* process);

    Process* pop();

    Process* front();

    bool empty() const;

    int getQuantum() const;

    Algorithm getAlgorithm() const;

    int getId() const;
};

#endif