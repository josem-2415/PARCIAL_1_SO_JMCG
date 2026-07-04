//
// Created by jcard on 3/07/2026.
//

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>

#include "Process.h"

class FileManager
{
public:

    std::vector<Process*> readProcesses(const std::string& filename);

    void writeResults(const std::string& filename,
                      const std::vector<Process*>& processes);
};

#endif