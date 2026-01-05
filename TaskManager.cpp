#include "TaskManager.h"

TaskManager::TaskManager(): personsNumber(0),taskNumber(0) {
    persons = new Person[MAX_PERSONS];
}

TaskManager::~TaskManager() {
    delete[] persons;
}


int TaskManager::SearchPerson(const string &personName) const {
    int i=0;
    while(i < personsNumber&&persons[i].getName()!=personName) {
        i++;
    }
    return i;
}

void TaskManager::assignTask(const string &personName, const Task &task) {
    int i=SearchPerson(personName);
    if (i == MAX_PERSONS) {
        throw std::runtime_error("Cannot add more people");
    }
    if (i == personsNumber) {
        persons[i]= Person(personName);
        personsNumber++;
    }
    Task newTask(task);
    newTask.setId(taskNumber);
    taskNumber++;
    persons[i].assignTask(newTask);
}

void TaskManager::completeTask(const string &personName) {
    int i=SearchPerson(personName);
    if (i == personsNumber) {
        return;
    }
    persons[i].completeTask();
}


void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    if (priority<=0) return;
    for (int i=0; i<personsNumber; i++) {
        //its very complicated and saves like 2 lines of code but it avoids duplication
        persons[i].setTasks(persons[i].getTasks().apply([type,priority](const Task& task)
        {if (type==task.getType()) {
            Task newTask(task.getPriority()+priority,task.getType(),task.getDescription());
            newTask.setId(task.getId());
            return Task(newTask);
        }
            return Task(task); }));
    }
}

void TaskManager::printAllEmployees() const {
    for (int i=0; i<personsNumber; i++) {
        std::cout << persons[i] << std::endl;
    }
}

SortedList<Task> TaskManager::GetAllTasks() const {
    SortedList<Task> allTasks;
    for (int i=0; i<personsNumber; i++) {
        for (const Task& task : persons[i].getTasks()) {
            allTasks.insert(task);
        }
    }
    return allTasks;
}


void TaskManager::printAllTasks() const {
    SortedList<Task> allTasks = GetAllTasks();
    for (const Task& task : allTasks) {
        std::cout << task << std::endl;
    }
}

void TaskManager::printTasksByType(TaskType type) const {
    SortedList<Task> allTasks = GetAllTasks();
    for (const Task& task : allTasks) {
        if (type==task.getType()) {
            std::cout << task << std::endl;
        }
    }
}


