//
// Created by jcard on 3/07/2026.
//

#include "FileManager.h"

#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

vector<Process*> FileManager::readProcesses(const string& filename)
{
    vector<Process*> processes;

    ifstream file(filename);

    if (!file.is_open())
        return processes;

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        if (line[0] == '#')
            continue;

        stringstream ss(line);

        string id;
        string bt;
        string at;
        string q;

        getline(ss, id, ';');
        getline(ss, bt, ';');
        getline(ss, at, ';');
        getline(ss, q, ';');

        Process* process = new Process(
            id,
            stoi(bt),
            stoi(at),
            stoi(q)
        );

        processes.push_back(process);
    }

    file.close();

    return processes;
}

void FileManager::writeResults(const string& filename,
                               const vector<Process*>& processes)
{
    ofstream file(filename);

    if (!file.is_open())
        return;

    file << "# Archivo: mlq001.txt\n";
    file << "# etiqueta; BT; AT; Q; WT; CT; RT; TAT\n";

    double totalWT = 0;
    double totalCT = 0;
    double totalRT = 0;
    double totalTAT = 0;

    for (Process* process : processes)
    {
        file
            << process->getId() << ";"
            << process->getBurstTime() << ";"
            << process->getArrivalTime() << ";"
            << process->getQueue() << ";"
            << process->getWaitingTime() << ";"
            << process->getCompletionTime() << ";"
            << process->getResponseTime() << ";"
            << process->getTurnaroundTime()
            << "\n";

        totalWT += process->getWaitingTime();
        totalCT += process->getCompletionTime();
        totalRT += process->getResponseTime();
        totalTAT += process->getTurnaroundTime();
    }

    int n = processes.size();

    if (n > 0)
    {
        file << fixed << setprecision(1);

        file << "# WT=" << totalWT / n
             << "; CT=" << totalCT / n
             << "; RT=" << totalRT / n
             << "; TAT=" << totalTAT / n
             << ";";
    }

    file.close();
}