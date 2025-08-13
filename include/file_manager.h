#pragma once
#include <vector>
#include <string>
#include "task.h"

using namespace std;

class FileManager {
private:
    string filename;

public:
    FileManager(const string& filename = "data\tasks.json");

    vector<Task> loadTasks();
    bool saveTasks(const vector<Task>& task);
    int getNextId();
};