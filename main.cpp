#include <iostream>
#include <fstream>
#include <string>

#include "FileManager.h"
#include "Scheduler.h"

using namespace std;

int main()
{
    FileManager fileManager;

    vector<Process*> processes =
        fileManager.readProcesses("mlq001.txt");

    if (processes.empty())
    {
        cout << "Error al leer el archivo mlq001.txt" << endl;
        return 1;
    }

    Scheduler scheduler;

    scheduler.loadProcesses(processes);
    scheduler.execute();

    fileManager.writeResults(
        "mlq001.txt",
        scheduler.getProcesses());

    cout << "\n===== CONTENIDO DE mlq001.txt =====\n\n";

    ifstream file("mlq001.txt");

    if (file.is_open())
    {
        string line;

        while (getline(file, line))
        {
            cout << line << endl;
        }

        file.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }

    // Liberar memoria
    for (Process* process : processes)
    {
        delete process;
    }

    return 0;
}