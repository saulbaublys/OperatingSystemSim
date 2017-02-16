#include "OperatingSystem.h"
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <sys/time.h>

using namespace std;

const int CONST_PRIORITY = 1;


#ifndef OPERATINGSYSTEM_CPP
#define OPERATINGSYSTEM_CPP


OperatingSystem::OperatingSystem(SimpleTimer &timer)
	{
	
	}

OperatingSystem::~OperatingSystem()
	{

	}

bool OperatingSystem::configure(string configFile, SimpleTimer &timer)
	{
     systemConfiguration = SystemConfig(configFile);
     logObject.configure(systemConfiguration);
     logObject.logSimLine(timer, "Operating system starting");
     return true;
	}

int OperatingSystem::uploadProcesses(SimpleTimer &timer)
	{
	 //Variables
	 ifstream fin;
	 int runningTime;
	 int processID = 0;
	 Task tempTask;
	 ProcessControlBlock tempProcess;
	 
	 fin.open(getMetadataFile().c_str());
	 if(!fin.good())
	 	{
	 	 cout << "Failed to open metadata file." << endl << endl << "Program terminated";
	 	 cout << endl;
	 	 return 0;
	 	}


	 fin.ignore(256, '\n');
	 
	 uploadTaskInfo(fin, tempTask);

	 if(tempTask.getTaskType() == 'S' && tempTask.getTaskName().compare("start") == 0)
	 	{
		 logObject.logSimLine(timer, "OS: preparing all processes");

 	 	 //Prime loop
 	 	 uploadTaskInfo(fin, tempTask);

 	 	 while(tempTask.getTaskType() != 'S' && tempTask.getTaskName().compare("end") != 0)
 	 	 	{
		 	 if(tempTask.getTaskType() == 'A' && tempTask.getTaskName().compare("start") == 0)
		 	 	{
		 	 	 runningTime = 0;
		 	 	 processID++;
		 	 	 tempProcess.addTask(tempTask);
		 	 	 do
	 	 	 	 {
	 	 	 	  uploadTaskInfo(fin, tempTask);
	 	 	 	  runningTime += calculateTaskRunTime(tempTask);
	 	 	 	  tempProcess.addTask(tempTask);
	 	 	 	 }
			 	 while(tempTask.getTaskType() != 'A' && tempTask.getTaskName().compare("end") != 0);
		 	 	}
		 	 tempProcess.addTask(tempTask);
		 	 tempProcess.setProcessID(processID);
		 	 tempProcess.setLengthOfProcess(runningTime);
		 	 tempProcess.setStateOfProcess("Ready");

		 	 if(systemConfiguration.getScheduleType().compare("FIFO-P") == 0)
		 	 	{
		 	 	 tempProcess.setPriority(CONST_PRIORITY);
		 	 	 readyQueue.enqueue(CONST_PRIORITY, tempProcess);
		 	 	}

		 	 //Reset the tempProcess to blank
		 	 tempProcess.setNumberOfTasks(0);

		 	 // Reprime loop
		 	 uploadTaskInfo(fin, tempTask);
 	 	 	}
	 	}

	 fin.close();
	 return 0;
	}

string OperatingSystem::getMetadataFile()
	{
	 return systemConfiguration.getFilePath();
	}

void OperatingSystem::uploadTaskInfo(ifstream& fin, Task& newTask)
	{
	 char taskType;
	 string taskName;
	 int numberOfCycles;
	 char dummy;

	 fin >> taskType;
	 fin >> dummy;

	 getline(fin, taskName, ')');

	 fin >> numberOfCycles;
	 fin >> dummy;

	 newTask.setTask(taskType, taskName, numberOfCycles);
	}

void OperatingSystem::wait(int mSeconds)
	{
	 struct timeval startTimeval, elapsedTimeval;
	 int elapsedSec, elapsedUSec, endSec, endUSec, elapsedTime, endTime;


	 // Calculate endTime in usec
	 endSec = mSeconds / 1000;
	 endUSec = (mSeconds % 1000) * 1000;
	 endTime = (endSec * 1000000) + endUSec;

	 gettimeofday(&startTimeval, NULL);

	 do
	 {
	  gettimeofday(&elapsedTimeval, NULL);

	  elapsedSec = elapsedTimeval.tv_sec - startTimeval.tv_sec;
	  elapsedUSec = elapsedTimeval.tv_usec - startTimeval.tv_usec;

	  if(elapsedUSec < 0)
	  	{
	  	 elapsedUSec = elapsedUSec + 1000000;
	  	 elapsedSec--;
	  	}
	  // Calculate elapsedTime in usec
	  elapsedTime = (elapsedSec * 1000000) + elapsedUSec;
	 }
	 while(elapsedTime < endTime);
	}

void OperatingSystem::simulate(SimpleTimer &timer)
	{
	 ProcessControlBlock tempProcess;

	 if(systemConfiguration.getScheduleType().compare("FIFO-P") == 0)
	 	{
		 while(!readyQueue.isEmpty() || !blockedProcesses.isEmpty())
		 	{
		 	 if(!readyQueue.isEmpty())
		 	 	{
		 	 	 logObject.logSimLine(timer, "OS: selecting next process");
		 	 	 readyQueue.dequeue(tempProcess);
		 	 	 runProcess(tempProcess, timer);
		 	 	}
		 	 else
		 	 	{
		 	 	 interruptHandler(timer);
		 	 	}
		 	}
	 	}

	 else
	 	{
	 	 cout << endl << "ERROR: Scheduling type not available" << endl;
	 	}

	 logObject.logSimLine(timer, "Simulator program ending");
	 logObject.logToFile(systemConfiguration.getLogFilePath());
	}

void OperatingSystem::runProcess(ProcessControlBlock& process, SimpleTimer &timer)
	{
	 Task nextTaskToBeExecuted;
	 pthread_t thread;
	 int quantumRemaining = systemConfiguration.getQuantumTime();
	 bool intFlag = false;

	 nextTaskToBeExecuted = process.getNextTaskToExecute();

	 // Handle if process is starting or ending
	 if (nextTaskToBeExecuted.getTaskType() == 'A' && 
	     nextTaskToBeExecuted.getTaskName().compare("start") == 0)
	 	{
	 	 logObject.logOSLine(timer, process, "OS: starting process ");
	 	 process.incrementTaskIndex();
	 	 nextTaskToBeExecuted = process.getNextTaskToExecute();
	 	}

	 else if(nextTaskToBeExecuted.getTaskType() == 'A' && 
	     	 nextTaskToBeExecuted.getTaskName().compare("end") == 0)
	 	{
	 	 logObject.logOSLine(timer, process, "OS: removing process ");
	 	}


	 // I/O handling
 	 interruptLine.delayTime = calculateTaskRunTime(nextTaskToBeExecuted);
 	 interruptLine.callingProcessID = process.getProcessID();

 	 if(nextTaskToBeExecuted.getTaskType() == 'I')
 	    {
 	     logObject.logProcessLine(timer, process, nextTaskToBeExecuted, "start", systemConfiguration);
 	     pthread_create(&thread, NULL, IOthread, (void*)&interruptLine);
 	     pthread_detach(thread);
  	     moveToBlocked(process);
 	     logObject.logProcessLine(timer, process, nextTaskToBeExecuted, "block", systemConfiguration);
 	    }
 	 else if(nextTaskToBeExecuted.getTaskType() == 'O')
 	 	{
 	 	 logObject.logProcessLine(timer, process, nextTaskToBeExecuted, "start", systemConfiguration);
 	 	 pthread_create(&thread, NULL, IOthread, (void*)&interruptLine);
 	 	 pthread_detach(thread);
 	 	 moveToBlocked(process);
 	 	 logObject.logProcessLine(timer, process, nextTaskToBeExecuted, "block", systemConfiguration);
 	 	}


 	 // P(run) handling
 	 else if(nextTaskToBeExecuted.getTaskType() == 'P')
 	 	{
 	 	 // Log
 	 	 if(nextTaskToBeExecuted.getNumberOfCyclesRemaining() == nextTaskToBeExecuted.getNumberOfTaskCycles())
 	 	 	{
 	 	 	 logObject.logProcessLine(timer, process, nextTaskToBeExecuted, "start", systemConfiguration);
 	 	 	}
 	 	 else
 	 	 	{
 	 	 	 logObject.logProcessLine(timer, process, nextTaskToBeExecuted, "continue", systemConfiguration);
 	 	 	}

 	 	 // Loop through tasks & check for interrupts
 	 	 while(quantumRemaining > 0 && nextTaskToBeExecuted.getNumberOfCyclesRemaining() > 0 && !intFlag)
 	 	 	{
 	 	 	 wait(systemConfiguration.getProcessorCycleTime());
 	 	 	 quantumRemaining--;
 	 	 	 nextTaskToBeExecuted.decrementCyclesRemaining();
 	 	 	 process.updateTask(nextTaskToBeExecuted);
 	 	 	 if(interruptHandler(timer))
 	 	 	 	{
 	 	 	 	 intFlag = true;
 	 	 	 	}
 	 	 	}

 	 	 // Log
 	 	 if(quantumRemaining <= 0)
 	 	 	{
 	 	 	 logObject.logProcessLine(timer, process, nextTaskToBeExecuted, "quantum time out", systemConfiguration);
 	 	 	}
 	 	 else if(nextTaskToBeExecuted.getNumberOfCyclesRemaining() <= 0)
 	 	 	{
 	 	 	 process.incrementTaskIndex();
 	 	 	 logObject.logProcessLine(timer, process, nextTaskToBeExecuted, "end", systemConfiguration);
 	 	 	}

 	 	 readyQueue.enqueue(CONST_PRIORITY, process);
 	 	}
 	
	}

void *OperatingSystem::IOthread(void *newThreadData)
	{
	 // Vars
	 int tempID;
	 int tempWait;

	 // Typecase from void to original type
     struct interruptData *threadData;
     threadData = (struct interruptData *) newThreadData;

     // Mutex lock while we copy over the info to temps, as it may get overwritten
	 // at any point during the thread if another thread is called
     tempID = threadData -> callingProcessID;
     tempWait = threadData -> delayTime;

     OperatingSystem::wait(tempWait);

	 // Upload interrupt
	 threadData -> interruptVector[threadData -> interruptVector.getSize()] = tempID;
	 threadData -> interruptVector.incrementSize();

	 // Grow vector as necessary
	 if(threadData -> interruptVector.getSize() >= threadData -> interruptVector.getCapacity())
	 	{
	 	 threadData -> interruptVector.grow(threadData -> interruptVector.getCapacity());
	 	}

	 pthread_exit(NULL);
	}

int OperatingSystem::calculateTaskRunTime(Task currentTask)
	{
	 string taskName = currentTask.getTaskName();
	 int numCycles = currentTask.getNumberOfTaskCycles();

	 if(taskName.compare("run") == 0)
	 	{
	 	 return numCycles * systemConfiguration.getProcessorCycleTime();
	 	}
	 else if(taskName.compare("monitor") == 0)
	 	{
	 	 return numCycles * systemConfiguration.getMonitorDisplayTime();
	 	}
	 else if(taskName.compare("hard drive") == 0)
	 	{
	 	 return numCycles * systemConfiguration.getHDDCycleTime();
	 	}
	 else if(taskName.compare("printer") == 0)
	 	{
	 	 return numCycles * systemConfiguration.getPrinterCycleTime();
	 	}
	 else if(taskName.compare("keyboard") == 0)
	 	{
	 	 return numCycles * systemConfiguration.getKeyboardCycleTime();
	 	}
	 else
	 	{
	 	 return 0;
	 	}
	}

void OperatingSystem::printTime(SimpleTimer timer)
	{
	 char * elapsedTime = new char[20];

	 timer.stop();
	 timer.getElapsedTime(elapsedTime);
	 cout << elapsedTime << " - ";
	}

void OperatingSystem::moveToBlocked(ProcessControlBlock &process)
	{
	 // Add the process
	 blockedProcesses[blockedProcesses.getSize()] = process;
	 blockedProcesses.incrementSize();

	 // Check to make sure vector stays within bounds
	 if(blockedProcesses.getSize() >= blockedProcesses.getCapacity())
	 	{
	 	 blockedProcesses.grow(blockedProcesses.getCapacity());
	 	}
	 if(blockedProcesses.getSize() < (blockedProcesses.getCapacity() / 4))
	    {
	     blockedProcesses.shrink(blockedProcesses.getCapacity()/2);
	    }
	}

void OperatingSystem::moveToReady(ProcessControlBlock &process)
	{
	 readyQueue.enqueue(CONST_PRIORITY, process);
	}

bool OperatingSystem::interruptHandler(SimpleTimer timer)
	{
	 int processID;
	 int indexFoundAt;

	 if(!interruptLine.interruptVector.isEmpty())
	 	{
		 while(!interruptLine.interruptVector.isEmpty())
		 	{
		 	 // Fetch calling process ID and delete interrupt
		 	 processID = interruptLine.interruptVector[0];
		 	 interruptLine.interruptVector.removeAtIndex(0);

		 	 // Find the process in blocked vector , move to ready, delete from blocked
		 	 indexFoundAt = blockedProcesses.findItem(processID);
		 	 logObject.logProcessLine(timer, blockedProcesses[indexFoundAt], 
		 	                blockedProcesses[indexFoundAt].getNextTaskToExecute(),
		 	                "complete", systemConfiguration);


		 	 blockedProcesses[indexFoundAt].incrementTaskIndex();
		 	 moveToReady(blockedProcesses[indexFoundAt]);


		 	 blockedProcesses.removeAtIndex(indexFoundAt);
		 	}	 	 
		 return true;
	 	}
	 return false;
	}

#endif




