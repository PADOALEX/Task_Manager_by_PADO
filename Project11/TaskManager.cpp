#include "TaskManager.h"
#include <iostream>
#include <fstream>
using namespace std;
void TaskManager::addTask(const string& title, const string& description, Priority priority)
{
    Task t{ title, description, priority };
    allTasks.push_back(t);
    switch (priority)
    {
    case Priority::HIGH:   highQueue.push(t); break;
    case Priority::MEDIUM: medQueue.push(t); break;
    case Priority::LOW:    lowQueue.push(t); break;
    }
}
void TaskManager::executeTask()
{
    if (!highQueue.empty())
    {
        cout << "Виконано: " << highQueue.front().title << endl;
        highQueue.pop();
    }
    else if (!medQueue.empty())
    {
        cout << "Виконано: " << medQueue.front().title << endl;
        medQueue.pop();
    }
    else if (!lowQueue.empty())
    {
        cout << "Виконано: " << lowQueue.front().title << endl;
        lowQueue.pop();
    }
    else
    {
        cout << "Немає завдань.\n";
    }
}
void TaskManager::showAllTasks() const
{
    cout << "\n=== Високий пріоритет ===\n";
    showQueue(highQueue);
    cout << "\n=== Середній пріоритет ===\n";
    showQueue(medQueue);
    cout << "\n=== Низький пріоритет ===\n";
    showQueue(lowQueue);
}
void TaskManager::showQueue(queue<Task> q) const
{
    while (!q.empty())
    {
        Task t = q.front();
        cout << "- " << t.title << " (" << t.description << ")\n";
        q.pop();
    }
}
void TaskManager::editTask(int index)
{
    if (index < 0 || index >= allTasks.size())
    {
        cout << "Невірний індекс.\n";
        return;
    }
    Task& t = allTasks[index];
    cout << "Редагування: " << t.title << endl;
    cout << "Нова назва (або залиш порожньо): ";
    string newTitle;
    getline(cin, newTitle);
    if (!newTitle.empty()) t.title = newTitle;
    cout << "Новий опис (або залиш порожньо): ";
    string newDesc;
    getline(cin, newDesc);
    if (!newDesc.empty()) t.description = newDesc;
    cout << "Новий пріоритет (1-Високий, 2-Середній, 3-Низький, 0 - без змін): ";
    int p;
    cin >> p;
    cin.ignore();
    if (p >= 1 && p <= 3)
    {
        t.priority = getPriorityFromInput(p);
    }
    cout << "Завдання оновлено.\n";
}
void TaskManager::saveToFile(const string& filename) const
{
    ofstream fout(filename);
    for (const Task& t : allTasks)
    {
        fout << priorityToString(t.priority) << '\n'
            << t.title << '\n'
            << t.description << '\n';
    }
    fout.close();
    cout << "Збережено у файл.\n";
}
void TaskManager::loadFromFile(const string& filename)
{
    ifstream fin(filename);
    if (!fin.is_open()) return;
    string prioStr, title, desc;
    while (getline(fin, prioStr) && getline(fin, title) && getline(fin, desc))
    {
        addTask(title, desc, stringToPriority(prioStr));
    }
    fin.close();
}
string TaskManager::priorityToString(Priority p) const
{
    switch (p)
    {
    case Priority::HIGH: return "HIGH";
    case Priority::MEDIUM: return "MEDIUM";
    case Priority::LOW: return "LOW";
    }
    return "";
}
Priority getPriorityFromInput(int input)
{
    switch (input)
    {
    case 1: return Priority::HIGH;
    case 2: return Priority::MEDIUM;
    default: return Priority::LOW;
    }
}
Priority stringToPriority(const string& str)
{
    if (str == "HIGH") return Priority::HIGH;
    if (str == "MEDIUM") return Priority::MEDIUM;
    return Priority::LOW;
}