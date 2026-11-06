#include "TaskManager.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace {
std::string priorityName(Priority priority) {
    switch (priority) {
        case Priority::HIGH: return "HIGH";
        case Priority::MEDIUM: return "MEDIUM";
        case Priority::LOW: return "LOW";
    }
    throw std::invalid_argument("Invalid priority");
}
}

void TaskManager::addTask(const std::string& title, const std::string& description, Priority priority) {
    if (title.empty() || title.find_first_of("\r\n") != std::string::npos || description.find_first_of("\r\n") != std::string::npos)
        throw std::invalid_argument("Use a nonempty, single-line task title and single-line description");
    priorityName(priority);
    tasks.push_back({title, description, priority});
}

void TaskManager::executeTask() {
    if (tasks.empty()) {
        std::cout << "No pending tasks.\n";
        return;
    }
    auto next = std::min_element(tasks.begin(), tasks.end(), [](const Task& left, const Task& right) {
        return left.priority < right.priority;
    });
    std::cout << "Executing: " << next->title << '\n';
    tasks.erase(next);
}

void TaskManager::showAllTasks() const {
    for (Priority priority : {Priority::HIGH, Priority::MEDIUM, Priority::LOW}) {
        for (std::size_t index = 0; index < tasks.size(); ++index) {
            const auto& task = tasks[index];
            if (task.priority == priority)
                std::cout << index << ": " << priorityName(priority) << " | " << task.title << " | " << task.description << '\n';
        }
    }
}

void TaskManager::editTask(int index) {
    if (index < 0 || static_cast<std::size_t>(index) >= tasks.size()) {
        std::cout << "Invalid task index.\n";
        return;
    }
    auto updated = tasks[static_cast<std::size_t>(index)];
    std::string title, description;
    int priority;
    std::cout << "New title (empty keeps current): ";
    if (!std::getline(std::cin,title)) return;
    std::cout << "New description (empty keeps current): ";
    if (!std::getline(std::cin,description)) return;
    std::cout << "Priority (1=HIGH, 2=MEDIUM, 3=LOW, 0=unchanged): ";
    if (!(std::cin >> priority)) {
        if (!std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    if (priority < 0 || priority > 3) return;
    if (!title.empty()) updated.title = title;
    if (!description.empty()) updated.description = description;
    if (priority != 0) updated.priority = getPriorityFromInput(priority);
    tasks[static_cast<std::size_t>(index)] = updated;
}

void TaskManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) throw std::runtime_error("Cannot open task file for writing");
    for (const auto& task : tasks)
        file << priorityName(task.priority) << '\n' << task.title << '\n' << task.description << '\n';
    file.close();
    if (!file) throw std::runtime_error("Task file write failed");
}

void TaskManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    std::vector<Task> loaded;
    std::string priority, title, description;
    while (std::getline(file,priority)) {
        if (!std::getline(file,title) || !std::getline(file,description) || title.empty())
            throw std::runtime_error("Incomplete task record");
        loaded.push_back({title, description, stringToPriority(priority)});
    }
    if (file.bad()) throw std::runtime_error("Task file read failed");
    tasks.swap(loaded);
}

Priority getPriorityFromInput(int input) {
    switch(input) {
        case 1: return Priority::HIGH;
        case 2: return Priority::MEDIUM;
        case 3: return Priority::LOW;
        default: throw std::invalid_argument("Priority must be 1, 2 or 3");
    }
}

Priority stringToPriority(const std::string& value) {
    if (value == "HIGH") return Priority::HIGH;
    if (value == "MEDIUM") return Priority::MEDIUM;
    if (value == "LOW") return Priority::LOW;
    throw std::runtime_error("Unknown priority in task file");
}
