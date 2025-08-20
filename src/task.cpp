#include "../include/task.h"
#include <sstream>
#include <iomanip>

using namespace std;

// Constructor
Task::Task(int id, const string& desc) : id(id), description(desc), status(TaskStatus::TODO) {
    createdAt = updatedAt = time(nullptr);
}

// Getters
int Task::getId() const { return id; }
string Task::getDescription() const { return description; }
TaskStatus Task::getStatus() const { return status; }
time_t Task::getCreatedAt() const { return createdAt; }
time_t Task::getUpdatedAt() const { return updatedAt; }

//Setters
void Task::setDescription( const string& desc ){
    description = desc;
    updatedAt = time(nullptr);
}

void Task::setStatus( TaskStatus newStatus){
    status = newStatus;
    updatedAt = time(nullptr);
}

string Task::statusToString() const {
    switch (status)
    {
    case TaskStatus::TODO: return "To do";
    case TaskStatus::IN_PROGRESS: return "In progress";
    case TaskStatus::DONE: return "Done";    
    default:
        return "To do";
    }
}

void Task::setCreatedAt(std::time_t timestamp) {
    createdAt = timestamp;
}

void Task::setUpdatedAt(std::time_t timestamp) {
    updatedAt = timestamp;
}

// Tạo chuỗi Json mô tả Task hiện tại
string Task::toJsonString() const {
    stringstream ss;
    ss << "{\n";
    ss << "     \"id\": " << id << ",\n";
    ss << "     \"description\": \"" << description << "\",\n";
    ss << "     \"status\": \"" << statusToString() << "\",\n";
    ss << "     \"createdAt\": " << createdAt << ",\n";
    ss << "     \"updatedAt\": " << updatedAt << ",\n";
    ss << " }";
    return ss.str();
}