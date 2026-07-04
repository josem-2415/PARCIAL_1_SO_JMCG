//
// Created by jcard on 3/07/2026.
//

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>

#include "Process.h"

/**
 * @class FileManager
 * @brief Gestiona la lectura y escritura de archivos del proyecto.
 *
 * Esta clase es responsable de:
 *
 * • Leer el archivo de entrada que contiene los procesos.
 * • Crear los objetos Process correspondientes.
 * • Escribir nuevamente el archivo con las métricas
 *   calculadas por el Scheduler.
 *
 * De esta manera se mantiene separada la lógica de manejo
 * de archivos de la lógica del algoritmo de planificación.
 */
class FileManager
{
public:

    /**
     * @brief Lee el archivo de entrada.
     *
     * Interpreta cada línea del archivo, crea un objeto
     * Process y lo almacena dentro de un vector.
     *
     * @param filename Nombre del archivo a leer.
     * @return Vector con todos los procesos encontrados.
     */
    std::vector<Process*> readProcesses(const std::string& filename);

    /**
     * @brief Escribe los resultados de la simulación.
     *
     * Sobrescribe el archivo original agregando las métricas
     * calculadas para cada proceso y los promedios generales.
     *
     * @param filename Nombre del archivo de salida.
     * @param processes Vector de procesos finalizados.
     */
    void writeResults(const std::string& filename,
                      const std::vector<Process*>& processes);
};

#endif