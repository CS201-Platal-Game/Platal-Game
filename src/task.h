#pragma once

#include <string>

class SubTask {
};

class Task {
    Task();
    ~Task();

  private:
    std::string title_;
    std::string description_;
};

class TaskList {
};