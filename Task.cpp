#include "Task.h"
#include <iostream>
using namespace std;

#ifndef TASK_CPP
#define TASK_CPP

Task::Task()
	{

	}

Task::Task(string newName, int numberOfNewCycles, char newTaskType)
	{
	 taskName = newName;
	 numberOfCycles = numberOfNewCycles;
	 cyclesRemaining = numberOfNewCycles;
	 taskType = newTaskType;
	}

Task::~Task()
	{
	 
	}

string Task::getTaskName()
	{
	 return taskName;
	}

int Task::getNumberOfTaskCycles()
	{
	 return numberOfCycles;
	}

int Task::getNumberOfCyclesRemaining()
	{
	 return cyclesRemaining;
	}

char Task::getTaskType()
	{
	 return taskType;
	}

Task& Task::operator=(const Task &other)
	{
	 if(this != &other)
	 	{
	 	 taskType = other.taskType;
	 	 taskName = other.taskName;
	 	 numberOfCycles = other.numberOfCycles;
	 	 cyclesRemaining = other.cyclesRemaining;
	 	}
	 return *this;
	}

void Task::decrementCyclesRemaining()
	{
	 cyclesRemaining--;
	}

void Task::setTask(char newTaskType, string newTaskName, int newNumberOfCycles)
	{
	 taskType = newTaskType;
	 taskName = newTaskName;
	 numberOfCycles = newNumberOfCycles;
	 cyclesRemaining = newNumberOfCycles;
	}


#endif