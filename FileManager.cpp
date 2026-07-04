//
// Created by jcard on 3/07/2026.
//

#include "FileManager.h"

#include <fstream>
#include <iomanip>
#include <sstream>

/**
 * @brief Lee los procesos almacenados en un archivo de texto.
 *
 * El archivo debe contener la información de cada proceso
 * con el siguiente formato:
 *
 * Etiqueta; Burst Time; Arrival Time; Queue
 *
 * Cada línea válida genera un nuevo objeto Process que será
 * utilizado posteriormente por el Scheduler.
 *
 * @param filename Nombre del archivo de entrada.
 * @return Vector con todos los procesos leídos.
 */
std::vector<Process*> FileManager::readProcesses(const std::string& filename)
{
    std::vector<Process*> processes;

    std::ifstream file(filename);

    if (!file.is_open())
    {
        return processes;
    }

    std::string line;

    /*
     * Leer el archivo línea por línea.
     */
    while (getline(file, line))
    {
        /*
         * Ignorar líneas vacías y comentarios.
         */
        if (line.empty() || line[0] == '#')
            continue;

        std::stringstream ss(line);

        std::string id;
        std::string token;

        int burstTime;
        int arrivalTime;
        int queue;

        getline(ss, id, ';');

        getline(ss, token, ';');
        burstTime = stoi(token);

        getline(ss, token, ';');
        arrivalTime = stoi(token);

        getline(ss, token, ';');
        queue = stoi(token);

        /*
         * Crear el nuevo proceso e incorporarlo
         * al vector.
         */
        processes.push_back(
            new Process(
                id,
                burstTime,
                arrivalTime,
                queue));
    }

    file.close();

    return processes;
}

/**
 * @brief Escribe los resultados obtenidos por la simulación.
 *
 * Para cada proceso se almacenan:
 *
 * • Waiting Time (WT)
 * • Completion Time (CT)
 * • Response Time (RT)
 * • Turnaround Time (TAT)
 *
 * Además, al final del archivo se calculan y escriben
 * los promedios de cada una de estas métricas.
 *
 * @param filename Archivo donde se escribirán los resultados.
 * @param processes Procesos finalizados.
 */
void FileManager::writeResults(
    const std::string& filename,
    const std::vector<Process*>& processes)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        return;
    }

    file << "# Archivo: " << filename << "\n";
    file << "# etiqueta; BT; AT; Q; WT; CT; RT; TAT\n";

    double totalWT = 0;
    double totalCT = 0;
    double totalRT = 0;
    double totalTAT = 0;

    /*
     * Escribir la información de cada proceso
     * y acumular las métricas para calcular
     * los promedios.
     */
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

    /*
     * Calcular los promedios de las métricas.
     */
    int n = processes.size();

    if (n > 0)
    {
        file << std::fixed << std::setprecision(1);

        file
            << "# WT=" << totalWT / n
            << "; CT=" << totalCT / n
            << "; RT=" << totalRT / n
            << "; TAT=" << totalTAT / n
            << ";";
    }

    file.close();
}