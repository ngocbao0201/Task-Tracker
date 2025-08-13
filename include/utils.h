#pragma once
#include <string>
#include <vector>
#include "task.h"

using namespace std;

namespace Utils {
    void printHelp();
    void listTasks(const vector<Task>& Tasks, const string& filter = "");
    TaskStatus stringToSatutus(const string& statusStr);
    string getCurrentTimestamp();
    bool isValidId(const string& idStr);
    int stringToInt(const string& str);
}