#ifndef OPERATINGSYSTEM_H
#define OPERATINGSYSTEM_H


#include "SystemConfig.h"
#include "Task.h"
#include "ProcessControlBlock.h"
#include "SimpleTimer.h"
#include "PriorityQueue.h"
#include "PriorityQueue.cpp"
#include "log.cpp"
#include <pthread.h>


struct interruptData
	{
	 SimpleVector<int> interruptVector;
	 int callingProcessID;
	 int delayTime;
	};

class OperatingSystem
{
 public:
 	OperatingSystem(SimpleTimer &timer);
 	~OperatingSystem();
 	bool configure(string configFile, SimpleTimer &timer);
 	int uploadProcesses(SimpleTimer &timer);
 	string getMetadataFile();
 	void uploadTaskInfo(ifstream& fin, Task& newTask);
 	static void wait(int mSeconds);
 	void simulate(SimpleTimer &timer);
 	void runProcess(ProcessControlBlock& process, SimpleTimer &timer);
 	int calculateTaskRunTime(Task currentTask);
 	void printTime(SimpleTimer timer);
 	void moveToBlocked(ProcessControlBlock &process);
 	void moveToReady(ProcessControlBlock &process);
 	bool interruptHandler(SimpleTimer timer);
	
 private:
 	SystemConfig systemConfiguration;
 	PriorityQueue<ProcessControlBlock> readyQueue;
 	SimpleVector<ProcessControlBlock> blockedProcesses;
  	interruptData interruptLine;
 	static void *IOthread(void *newThreadData);
 	struct log logObject;
};

#endif