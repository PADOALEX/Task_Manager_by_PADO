#include "TaskManager.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

int main() {
    try {
        TaskManager manager;
        manager.loadFromFile("tasks.txt");
        int choice;
        while (true) {
            std::cout << "1 Add | 2 Execute | 3 List | 4 Edit | 5 Save | 0 Exit\n";
            if (!(std::cin >> choice)) {
                if (std::cin.eof()) break;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            if (choice == 0) break;
            if (choice == 1) {
                std::string title, description;
                int priority;
                std::cout << "Title: ";
                if (!std::getline(std::cin,title)) break;
                std::cout << "Description: ";
                if (!std::getline(std::cin,description)) break;
                std::cout << "Priority (1=HIGH, 2=MEDIUM, 3=LOW): ";
                if (!(std::cin >> priority)) {
                    if (std::cin.eof()) break;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    continue;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                if (priority < 1 || priority > 3 || title.empty()) continue;
                manager.addTask(title,description,getPriorityFromInput(priority));
            }
            else if (choice == 2) manager.executeTask();
            else if (choice == 3) manager.showAllTasks();
            else if (choice == 4) {
                int index;
                if (!(std::cin >> index)) {
                    if (std::cin.eof()) break;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    continue;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                manager.editTask(index);
            }
            else if (choice == 5) manager.saveToFile("tasks.txt");
        }
        manager.saveToFile("tasks.txt");
    }
    catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
    return 0;
}
