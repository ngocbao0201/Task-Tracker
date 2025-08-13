#pragma once
#include <string>
#include <vector>
#include "task.h"

using namespace std;

namespace Utils {
    void printHelp(); // in ra hướng dẫn sử dụng 
    void listTasks(const vector<Task>& Tasks, const string& filter = ""); // in danh sách task ra màn hình, tham số là filter
    TaskStatus stringToSatutus(const string& statusStr); // chuyển string về enum
    string getCurrentTimestamp(); // lấy thời gian hiện tại dưới dạng string
    bool isValidId(const string& idStr); // kiểm tra Id nhập vào
    int stringToInt(const string& str); // chuyển Id về dạng int
}