//Task Class definition
#include <string>
#include <fstream>

using namespace std;

#ifndef TASK_H
#define TASK_H

class Task
{
 public:
 	Task();
 	Task(string newName, int numberOfCycles, char newTaskType);
 	~Task();
 	string getTaskName();
 	int getNumberOfTaskCycles();
 	int getNumberOfCyclesRemaining();
 	int setNumberOfCyclesRemaining();
 	char getTaskType();
 	void setTask(char newTaskType, string newTaskName, int newNumberOfCycles);
 	void decrementCyclesRemaining();
 	Task& operator=(const Task &other);

 private:
 	string taskName;
 	int numberOfCycles;
 	int cyclesRemaining;
 	char taskType;
};

#endif