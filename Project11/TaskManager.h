#pragma once
#include <string>
#include <vector>

enum class Priority { HIGH, MEDIUM, LOW };
struct Task {
    std::string title;
    std::string description;
    Priority priority;
};

class TaskManager {
public:
    void addTask(const std::string& title, const std::string& description, Priority priority);
    void executeTask();
    void showAllTasks() const;
    void editTask(int index);
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
private:
    std::vector<Task> tasks;
};

Priority getPriorityFromInput(int input);
Priority stringToPriority(const std::string& value);
