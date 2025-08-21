#include "../include/utils.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

void Utils::printHelp() {
    cout << "---Task Tracker---" << endl;
    cout << "Usage: task-cli [command] [options]\n\n";
    cout << "Commands:\n";
    cout << "  add \"description\"     - Add a new task\n";
    cout << "  update id \"desc\"      - Update task description\n";
    cout << "  delete id             - Delete a task\n";
    cout << "  mark-in-progress id   - Mark task as in progress\n";
    cout << "  mark-done id          - Mark task as done\n";
    cout << "  list [status]         - List all tasks or by status\n";
}

void Utils::listTasks(const vector<Task>& tasks, const string& filter){
    cout << setw(5) << "ID" << " | "
         << setw(20) << "Description" << " | "
         << setw(15) << "Status" << " | " << "Created At" << endl;
    cout << string(70, '-') << endl;

    for (const auto& task : tasks){
        if (!filter.empty() && task.statusToString() != filter){
            continue;
        }

        cout << setw(5) << task.getId() << " | "
        << setw(20) << task.getDescription().substr(0,20) << " | "
        << setw(15) << task.statusToString() << " | ";
        time_t createdAt = task.getCreatedAt();
        tm* tm_ptr = localtime(&createdAt);
        cout << put_time(tm_ptr, "%Y-%m-%d %H:%M") << endl;
    }
}

TaskStatus Utils::stringToSatutus(const string& statusStr) {
    if (statusStr == "In progress") return TaskStatus::IN_PROGRESS;
    if (statusStr == "Done") return TaskStatus::DONE;
    return TaskStatus::TODO;
}

bool Utils::isValidId(const string& idStr) {
    return !idStr.empty() && all_of(idStr.begin(), idStr.end(), ::isdigit);
}

int Utils::stringToInt(const string& str){
    return stoi(str);
}
