#include "../include/file_manager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "../include/utils.h"
#include "../include/json.hpp"

using json = nlohmann::json;
using namespace std;

FileManager::FileManager(const string& filename): filename(filename) {
}

vector<Task> FileManager::loadTasks() {
    vector<Task> tasks;
    ifstream file(filename);

    if (!file.is_open()){
        return tasks;
    }

    try {
        json j;
        file >> j;
        if (j.is_array()){
            for (const auto& item : j){
                if (item.contains("id") && item.contains("description")){
                    int id = item["id"];
                    string desc = item["description"];
                    int status = item.value("status", 0);
                    Task task(id, desc);
                    task.setStatus(static_cast<TaskStatus>(status));

                    if (item.contains("createdAt")){
                        string createdAtStr = item["createdAt"].get<string>();
                        task.setCreatedAt(stol(createdAtStr)); // Convert string to long
                    }

                    if (item.contains("updatedAt")){
                        string updatedAtStr = item["updatedAt"].get<string>();
                        task.setUpdatedAt(stol(updatedAtStr)); // Convert string to long
                    }
                    tasks.push_back(task);
                }
            }
        }
    } catch (const json::exception& e) {
        cerr << "JSON parsing error: " << e.what() << endl;
    }

    file.close();
    return tasks;
}

bool FileManager::saveTasks(const vector<Task>& tasks){
    try{
        json j = json::array();

        for (const auto& task : tasks){
            json taskJson;
            taskJson["id"] = task.getId();
            taskJson["description"] = task.getDescription();
            taskJson["status"] = static_cast<int>(task.getStatus());
            taskJson["createdAt"] = to_string(task.getCreatedAt()); // Chuyển thành string
            taskJson["updatedAt"] = to_string(task.getUpdatedAt()); // Chuyển thành string
            j.push_back(taskJson);
        }

        ofstream file(filename);
        if (!file.is_open()){
            cerr << "Could not open file for writing: " << filename << endl;
            return false;
        }

        file << j.dump(2);
        file.close();
        return true;
    } catch (const json::exception& e) {
        cerr << "JSON saving error: " << e.what() << endl;
        return false;
    }
}

int FileManager::getNextId() {
    auto tasks = loadTasks();
    if(tasks.empty()){
        return 1;
    }

    int maxId = 0;
    for(const auto& task: tasks){
        if (task.getId() > maxId){
            maxId = task.getId();
        }
    }
    return maxId + 1;
}