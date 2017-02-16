#include "ProcessControlBlock.h"
#include "Task.h"
#include <iostream>
using namespace std;

#ifndef PROCESSCONTROLBLOCK_CPP
#define PROCESSCONTROLBLOCK_CPP

ProcessControlBlock::ProcessControlBlock()
	{
	 numberOfTasks = 0;
	 taskIndex = 0;
	 state = "Enter/Start";
	}

ProcessControlBlock::~ProcessControlBlock()
	{

	}

int ProcessControlBlock::getNumberOfTasks()
	{
	 return numberOfTasks;
	}

void ProcessControlBlock::setNumberOfTasks(int newNumberOfTasks)
	{
	 numberOfTasks = newNumberOfTasks;
	}

int ProcessControlBlock::getProcessID()
	{
	 return processID;
	}

void ProcessControlBlock::setProcessID(int ID)
	{
	 processID = ID;
	}

Task& ProcessControlBlock::getNextTaskToExecute()
	{
	 return tasks[taskIndex];
	}

void ProcessControlBlock::incrementTaskIndex()
	{
	 taskIndex++;
	}

void ProcessControlBlock::addTask(Task &task)
	{
	 // Check to make sure simplevector isn't goind out of bounds
	 if(tasks.getCapacity() <= tasks.getSize())
	 	{
	 	 tasks.grow(tasks.getCapacity());
	 	}

	 // Add task to vector
	 tasks[numberOfTasks] = task;
	 numberOfTasks++;
	 tasks.incrementSize();
	}

void ProcessControlBlock::setPriority(int newPriority)
	{
	 priority = newPriority;
	}

int ProcessControlBlock::getPriority()
	{
	 return priority;
	}

void ProcessControlBlock::setLengthOfProcess(int newLengthOfProcess)
	{
	 lengthOfProcess = newLengthOfProcess;
	}

int ProcessControlBlock::getLengthOfProcess()
	{
	 return lengthOfProcess;
	}

void ProcessControlBlock::setStateOfProcess(string newState)
	{
	 state = newState;
	}

string ProcessControlBlock::getStateOfProcess()
	{
	 return state;
	}	

void ProcessControlBlock::updateTask(Task &updatedTask)
	{
	 tasks[taskIndex] = updatedTask;
	}

#endif