#include <iostream>
#include <fstream>
#include <string>

#include "FileManager.h"
#include "Scheduler.h"

using namespace std;

/**
 * @brief Función principal del programa.
 *
 * Este método coordina toda la ejecución del algoritmo
 * Multi-Level Queue (MLQ).
 *
 * El flujo general del programa es el siguiente:
 *
 * 1. Leer los procesos desde el archivo de entrada.
 * 2. Verificar que la lectura se haya realizado correctamente.
 * 3. Crear el planificador (Scheduler).
 * 4. Cargar los procesos en el Scheduler.
 * 5. Ejecutar la simulación del algoritmo MLQ.
 * 6. Escribir las métricas obtenidas en el archivo.
 * 7. Mostrar el contenido del archivo por consola.
 * 8. Liberar la memoria utilizada por los procesos.
 *
 * @return 0 si el programa finaliza correctamente.
 */
int main()
{
    /*
     * Objeto encargado de administrar
     * la lectura y escritura del archivo.
     */
    FileManager fileManager;

    /*
     * Leer todos los procesos almacenados
     * en el archivo de entrada.
     */
    vector<Process*> processes =
        fileManager.readProcesses("mlq001.txt");

    /*
     * Verificar que la lectura del archivo
     * se haya realizado correctamente.
     */
    if (processes.empty())
    {
        cout << "Error al leer el archivo mlq001.txt" << endl;
        return 1;
    }

    /*
     * Crear el Scheduler que ejecutará
     * el algoritmo MLQ.
     */
    Scheduler scheduler;

    /*
     * Cargar los procesos y ejecutar
     * la simulación.
     */
    scheduler.loadProcesses(processes);
    scheduler.execute();

    /*
     * Escribir nuevamente el archivo
     * incluyendo las métricas calculadas
     * para cada proceso.
     */
    fileManager.writeResults(
        "mlq001.txt",
        scheduler.getProcesses());

    cout << "\n===== CONTENIDO DE mlq001.txt =====\n\n";

    /*
     * Abrir el archivo generado para
     * mostrar su contenido en pantalla.
     *
     * Esto facilita verificar los resultados
     * obtenidos por el algoritmo.
     */
    ifstream file("mlq001.txt");

    if (file.is_open())
    {
        string line;

        /*
         * Leer e imprimir cada línea
         * del archivo.
         */
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

    /*
     * Liberar la memoria dinámica utilizada
     * por los procesos creados durante
     * la lectura del archivo.
     */
    for (Process* process : processes)
    {
        delete process;
    }

    return 0;
}