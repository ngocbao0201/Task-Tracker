#pragma once
#include <vector>
#include <string>
#include "task.h"

using namespace std;

class FileManager {
private:
    string filename;

public:
    FileManager(const string& filename = "data/tasks.json");

    vector<Task> loadTasks(); // đọc file Json, trả về danh sách task
    bool saveTasks(const vector<Task>& task); // lưu danh sách task vào file json
    int getNextId(); // lấy id mới cho task tiếp theo
};