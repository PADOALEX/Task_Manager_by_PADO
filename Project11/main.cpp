#include <iostream>
#include "TaskManager.h"
#include <Windows.h>
using namespace std;
int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
    TaskManager manager;
    manager.loadFromFile("aboba.txt");
    int choice;
    do
    {
        cout << "\n=== Меню ===\n"
            << "1. Додати завдання\n"
            << "2. Виконати завдання\n"
            << "3. Показати всі завдання\n"
            << "4. Редагувати завдання\n"
            << "5. Зберегти у файл\n"
            << "0. Вийти\n"
            << "Ваш вибір: ";
        cin >> choice;
        cin.ignore();
        if (choice == 1)
        {
            string title, desc;
            int prio;
            cout << "Назва: "; getline(cin, title);
            cout << "Опис: "; getline(cin, desc);
            cout << "Пріоритет (1-Високий, 2-Середній, 3-Низький): "; cin >> prio;
            cin.ignore();
            manager.addTask(title, desc, getPriorityFromInput(prio));
        }
        else if (choice == 2)
        {
            manager.executeTask();
        }
        else if (choice == 3)
        {
            manager.showAllTasks();
        }
        else if (choice == 4)
        {
            int index;
            cout << "Введіть індекс завдання (0 - перше): ";
            cin >> index;
            cin.ignore();
            manager.editTask(index);
        }
        else if (choice == 5)
        {
            manager.saveToFile("tasks.txt");
        }
    }while (choice != 0);
    manager.saveToFile("tasks.txt");
    return 0;
}
