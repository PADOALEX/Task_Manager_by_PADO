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
        cout << "\n=== ���� ===\n"
            << "1. ������ ��������\n"
            << "2. �������� ��������\n"
            << "3. �������� �� ��������\n"
            << "4. ���������� ��������\n"
            << "5. �������� � ����\n"
            << "0. �����\n"
            << "��� ����: ";
        cin >> choice;
        cin.ignore();
        if (choice == 1)
        {
            string title, desc;
            int prio;
            cout << "�����: "; getline(cin, title);
            cout << "����: "; getline(cin, desc);
            cout << "�������� (1-�������, 2-�������, 3-�������): "; cin >> prio;
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
            cout << "������ ������ �������� (0 - �����): ";
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
