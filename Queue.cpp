//
// Created by jcard on 3/07/2026.
//

#include "Queue.h"

#include <algorithm>

Queue::Queue(int id,
             Algorithm algorithm,
             int quantum)
{
    this->id = id;
    this->algorithm = algorithm;
    this->quantum = quantum;
}

void Queue::push(Process* process)
{
    if (algorithm == RR)
    {
        rrQueue.push(process);
    }
    else
    {
        sjfQueue.push_back(process);

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

Process* Queue::front()
{
    if (algorithm == RR)
    {
        return rrQueue.front();
    }

    return sjfQueue.front();
}

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

bool Queue::empty() const
{
    if (algorithm == RR)
    {
        return rrQueue.empty();
    }

    return sjfQueue.empty();
}

int Queue::getQuantum() const
{
    return quantum;
}

Algorithm Queue::getAlgorithm() const
{
    return algorithm;
}

int Queue::getId() const
{
    return id;
}