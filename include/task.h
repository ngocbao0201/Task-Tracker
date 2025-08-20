#pragma once // các file thư viện chỉ dùng 1 lần
#include<string>
#include<ctime>

using namespace std;

// khai báo enum
enum class TaskStatus {
    TODO,
    IN_PROGRESS,
    DONE
};

class Task {
private:
    int id;
    string description;
    TaskStatus status;
    time_t createdAt;
    time_t updatedAt;

public:
    Task(int id, const string& desc);

    //Getters
    int getId() const;
    string getDescription() const;
    TaskStatus getStatus() const;
    time_t getCreatedAt() const;
    time_t getUpdatedAt() const;

    //Setters
    void setDescription(const string& desc);
    void setStatus(TaskStatus status);
    void setCreatedAt(std::time_t timestamp);
    void setUpdatedAt(std::time_t timestamp);

    //Utility
    string statusToString() const; // chuyển trạng thái từ enum sang string
    string toJsonString() const; // chuyển string sang json
};