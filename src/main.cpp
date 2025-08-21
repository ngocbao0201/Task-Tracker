#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "../include/task.h"
#include "../include/file_manager.h"
#include "../include/utils.h"

using namespace std;

int main(int argc, char*argv[]) {
    if(argc < 2){
        Utils::printHelp();
        return 1;
    }

    FileManager fileManager;
    string command = argv[1];
    auto tasks = fileManager.loadTasks();

    if (command == "add" && argc >= 3) {
        int newId = fileManager.getNextId();
        Task newTask(newId, argv[2]);
        tasks.push_back(newTask);

        if(fileManager.saveTasks(tasks)) {
            cout << "Task added successfully (ID: " << newId << ")" << endl;
        }
        else {
            cout << "Error: Failed to save task" << endl;
            return 1;
        }
    }

    else if (command == "list"){
        string filter = (argc==3) ? argv[2] : "";
        Utils::listTasks(tasks, filter);
    }

    else if (command == "update" && argc >= 4){
        string idStr = argv[2];
        string newDescription = argv[3];
        
        // Validate ID
        if (!Utils::isValidId(idStr)) {
            cout << "Error: Invalid task ID '" << idStr << "'" << endl;
            return 1;
        }
        
        int taskId = Utils::stringToInt(idStr);
        bool found = false;
        
        // Tìm và update task
        for (auto& task : tasks) {
            if (task.getId() == taskId) {
                task.setDescription(newDescription);
                found = true;
                break;
            }
        }
        
        if (found) {
            if (fileManager.saveTasks(tasks)) {
                cout << "Task " << taskId << " updated successfully" << endl;
            } else {
                cout << "Error: Failed to save updated task" << endl;
                return 1;
            }
        } else {
            cout << "Error: Task with ID " << taskId << " not found" << endl;
            return 1;
        }
    }

    else if (command == "delete" && argc >= 3) {
        string idStr = argv[2];
        
        // Validate ID
        if (!Utils::isValidId(idStr)) {
            cout << "Error: Invalid task ID '" << idStr << "'" << endl;
            return 1;
        }
        
        int taskId = Utils::stringToInt(idStr);
        auto originalSize = tasks.size();
        
        // Xóa task có ID tương ứng
        tasks.erase(
            remove_if(tasks.begin(), tasks.end(),[taskId](const Task& task) {
                    return task.getId() == taskId;
                }
            ),
            tasks.end()
        );
        
        if (tasks.size() < originalSize) {
            if (fileManager.saveTasks(tasks)) {
                cout << "Task " << taskId << " deleted successfully" << endl;
            } else {
                cout << "Error: Failed to save after deletion" << endl;
                return 1;
            }
        } else {
            cout << "Error: Task with ID " << taskId << " not found" << endl;
            return 1;
        }
    }

     else if (command == "mark-in-progress" && argc >= 3) {
        string idStr = argv[2];
        
        // Validate ID
        if (!Utils::isValidId(idStr)) {
            cout << "Error: Invalid task ID '" << idStr << "'" << endl;
            return 1;
        }
        
        int taskId = Utils::stringToInt(idStr);
        bool found = false;
        
        // Tìm và mark task as in-progress
        for (auto& task : tasks) {
            if (task.getId() == taskId) {
                task.setStatus(TaskStatus::IN_PROGRESS);
                found = true;
                break;
            }
        }
        
        if (found) {
            if (fileManager.saveTasks(tasks)) {
                cout << "Task " << taskId << " marked as in-progress" << endl;
            } else {
                cout << "Error: Failed to save task status" << endl;
                return 1;
            }
        } else {
            cout << "Error: Task with ID " << taskId << " not found" << endl;
            return 1;
        }
    }

    else if (command == "mark-done" && argc >= 3) {
        string idStr = argv[2];
        
        // Validate ID
        if (!Utils::isValidId(idStr)) {
            cout << "Error: Invalid task ID '" << idStr << "'" << endl;
            return 1;
        }
        
        int taskId = Utils::stringToInt(idStr);
        bool found = false;
        
        // Tìm và mark task as done
        for (auto& task : tasks) {
            if (task.getId() == taskId) {
                task.setStatus(TaskStatus::DONE);
                found = true;
                break;
            }
        }
        
        if (found) {
            if (fileManager.saveTasks(tasks)) {
                cout << "Task " << taskId << " marked as done" << endl;
            } else {
                cout << "Error: Failed to save task status" << endl;
                return 1;
            }
        } else {
            cout << "Error: Task with ID " << taskId << " not found" << endl;
            return 1;
        }
    }

    else{
        Utils::printHelp();
        return 1;
    }
    return 0;
}