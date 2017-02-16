#ifndef PROCESSCONTROLBLOCK_H
#define PROCESSCONTROLBLOCK_H

//Process Control Block Class defenition
#include <string>
#include "SimpleVector.cpp"
#include "SystemConfig.h"
#include "Task.h"
using namespace std;

class ProcessControlBlock
{
 public:
 	ProcessControlBlock();
 	~ProcessControlBlock();
 	int getNumberOfTasks();
 	void setNumberOfTasks(int newNumberOfTasks);
 	int getProcessID();
 	void setProcessID(int ID);
 	Task& getNextTaskToExecute();
 	void incrementTaskIndex();
 	void addTask(Task& task);
 	void setPriority(int newPriority);
 	int getPriority();
 	void setLengthOfProcess(int newLengthOfProcess);
 	int getLengthOfProcess();
 	void setStateOfProcess(string newState);
 	string getStateOfProcess();
 	void updateTask(Task &updatedTask);

 private:
 	SimpleVector<Task> tasks;
 	int priority;
 	int lengthOfProcess;
 	int numberOfTasks;
 	int taskIndex;
 	int processID;
 	string state;
};

#endif