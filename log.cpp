#include "SimpleVector.h"
#include "SimpleTimer.h"
#include "ProcessControlBlock.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


const int LOG_TO_CONSOLE = 1;
const int LOG_TO_FILE = 2;
const int LOG_TO_BOTH = 3;


struct log
{
 stringstream stream;
 SimpleVector<string> logData;
 int whereToLog;
 int lineNumber;

 log()
 	{
 	 lineNumber = 0;
 	}

 void configure( SystemConfig systemConfiguration)
 	{
 	 if(systemConfiguration.getWhereToLog() == "Log to Console")
 	 	{
 	 	 whereToLog = LOG_TO_CONSOLE;
 	 	}
 	 else if(systemConfiguration.getWhereToLog() == "Log to File")
 	 	{
 	 	 whereToLog = LOG_TO_FILE;
 	 	}
 	 else if(systemConfiguration.getWhereToLog() == "Log to Both")
 	 	{
 	 	 whereToLog = LOG_TO_BOTH;
 	 	}
 	 else
 	 	{
 	 	 cout << "ERROR: Invalid 'Where to log' parameter in configuration file" << endl;
 	 	}
 	}

 void logSimLine(SimpleTimer timer, string data)
 	{
 	 stream.str("");
 	 stream.clear();

 	 if(whereToLog == LOG_TO_FILE)
 	 	{
	 	 stream << getTime(timer) << data << endl;	 	 
 	 	}
 	 else
 	 	{
	 	 cout << getTime(timer) << data << endl; 	
	 	 stream << getTime(timer) << data << endl;
 	 	}
 	 
 	 addLineToLogData(stream.str());
 	}

 void logOSLine(SimpleTimer &timer, ProcessControlBlock process, string data)
 	{
 	 stream.str("");
 	 stream.clear();

 	 if(whereToLog == LOG_TO_FILE)
 	 	{
	 	 stream << getTime(timer) << data << process.getProcessID() << endl;	 	 
 	 	}
 	 else
 	 	{
	 	 cout << getTime(timer) << data << process.getProcessID() << endl; 	
	 	 stream << getTime(timer) << data << process.getProcessID() << endl; 	
 	 	}

 	 addLineToLogData(stream.str());
 	}

 void logProcessLine(SimpleTimer &timer, ProcessControlBlock process, Task task,
               string stage, SystemConfig systemConfiguration)
  	{
  	 stream.str("");
 	 stream.clear();

 	 // INPUT LINES /////////////////////////////////
  	 if(task.getTaskType() == 'I' && stage == "start")
  	 	{
  	 	 if(whereToLog == LOG_TO_FILE)
	 	 	{
		 	 stream << getTime(timer) << "Process " << process.getProcessID() << ": " << task.getTaskName() << " input - start" << endl; 	 
	 	 	}
	 	 else
	 	 	{
		 	 cout << getTime(timer) << "Process " << process.getProcessID() << ": " << task.getTaskName() << " input - start" << endl; 	 
		 	 stream << getTime(timer) << "Process " << process.getProcessID() << ": " << task.getTaskName() << " input - start" << endl; 	 
	 	 	}
  	 	}

  	 else if(task.getTaskType() == 'I' && stage == "end")
	  	{
	 	 if(whereToLog == LOG_TO_FILE)
	 	 	{
		 	 stream << getTime(timer) << "Process " << process.getProcessID() << ": " << task.getTaskName() << " input - end" << endl; 	 
	 	 	}
	 	 else
	 	 	{
		 	 cout << getTime(timer) << "Process " << process.getProcessID() << ": " << task.getTaskName() << " input - end" << endl; 	 
		 	 stream << getTime(timer) << "Process " << process.getProcessID() << ": " << task.getTaskName() << " input - end" << endl; 	 
	 	 	}
	  	}

  	 else if(task.getTaskType() == 'I' && stage == "block")
	  	{
	 	 if(whereToLog == LOG_TO_FILE)
	 	 	{
		 	 stream << getTime(timer) << "Process " << process.getProcessID() << ": block for " << task.getTaskName() << " input" << endl; 	 
	 	 	}
	 	 else
	 	 	{
		 	 cout << getTime(timer) << "Process " << process.getProcessID() << ": block for " << task.getTaskName() << " input" << endl; 	 
		 	 stream << getTime(timer) << "Process " << process.getProcessID() << ": block for " << task.getTaskName() << " input" << endl; 	 
	 	 	}
	  	}

  	 else if(task.getTaskType() == 'I' && stage == "complete")
	  	{
	 	 if(whereToLog == LOG_TO_FILE)
	 	 	{
		 	 stream << getTime(timer) << "Interrupt: Process " << process.getProcessID() << " - " <<  task.getTaskName() << " input complete" << endl; 	 
	 	 	}
	 	 else
	 	 	{
		 	 cout << getTime(timer) << "Interrupt: Process " << process.getProcessID() << " - " <<  task.getTaskName() << " input complete" << endl; 	 
		 	 stream << getTime(timer) << "Interrupt: Process " << process.getProcessID() << " - " <<  task.getTaskName() << " input complete" << endl; 	 
	 	 	}
	  	}	  		  	


	 // OUTPUT LINES//////////////////////////////
	 else if(task.getTaskType() == 'O' && stage == "start")
	 	{
	 	 if(whereToLog == LOG_TO_FILE)
	 	 	{
		 	 stream << getTime(timer) << "Process " << process.getProcessID() << ": " << task.getTaskName() << " output - start" << endl; 	 
	 	 	}
	 	 else
	 	 	{
		 	 cout << getTime(timer) << "Process " << process.getProcessID() << ": " << task.getTaskName() << " output - start" << endl; 	 
		 	 stream << getTime(timer) << "Process " << process.getProcessID() << ": " << task.getTaskName() << " output - start" << endl; 	 
	 	 	}
	 	}

  	 else if(task.getTaskType() == 'O' && stage == "block")
	  	{
	 	 if(whereToLog == LOG_TO_FILE)
	 	 	{
		 	 stream << getTime(timer) << "Process " << process.getProcessID() << ": block for " << task.getTaskName() << " output" << endl; 	 
	 	 	}
	 	 else
	 	 	{
		 	 cout << getTime(timer) << "Process " << process.getProcessID() << ": block for " << task.getTaskName() << " output" << endl; 	 
		 	 stream << getTime(timer) << "Process " << process.getProcessID() << ": block for " << task.getTaskName() << " output" << endl; 	 
	 	 	}
	  	}	

  	 else if(task.getTaskType() == 'O' && stage == "complete")
	  	{
	 	 if(whereToLog == LOG_TO_FILE)
	 	 	{
		 	 stream << getTime(timer) << "Interrupt: Process " << process.getProcessID() << " - " <<  task.getTaskName() << " output complete" << endl; 	 
	 	 	}
	 	 else
	 	 	{
		 	 cout << getTime(timer) << "Interrupt: Process " << process.getProcessID() << " - " <<  task.getTaskName() << " output complete" << endl; 	 
		 	 stream << getTime(timer) << "Interrupt: Process " << process.getProcessID() << " - " <<  task.getTaskName() << " output complete" << endl; 	 
	 	 	}
	  	}	  

	 // PROCESSING LINES ////////////////////////////////////////
	 else if(stage == "start")
	 	{
	 	 if(whereToLog == LOG_TO_FILE)
	 	 	{
		 	 stream << getTime(timer) << "Process " << process.getProcessID() << ": processing action - start" << endl;
	 	 	}
	 	 else
	 	 	{
		 	 cout << getTime(timer) << "Process " << process.getProcessID() << ": processing action - start" << endl;
		 	 stream << getTime(timer) << "Process " << process.getProcessID() << ": processing action - start" << endl;
	 	 	}
	 	}

	 else if(stage == "continue")
	 	{
	 	 if(whereToLog == LOG_TO_FILE)
	 	 	{
		 	 stream << getTime(timer) << "Process " << process.getProcessID() << ": processing action - continue" << endl;
	 	 	}
	 	 else
	 	 	{
		 	 cout << getTime(timer) << "Process " << process.getProcessID() << ": processing action - continue" << endl;
		 	 stream << getTime(timer) << "Process " << process.getProcessID() << ": processing action - continue" << endl;
	 	 	}
	 	}	 	

	 else if(stage == "end")
	 	{
		 if(whereToLog == LOG_TO_FILE)
	 	 	{
		 	 stream << getTime(timer) << "Process " << process.getProcessID() << ": processing action - end" << endl;
	 	 	}
	 	 else
	 	 	{
		 	 cout << getTime(timer) << "Process " << process.getProcessID() << ": processing action - end" << endl;
		 	 stream << getTime(timer) << "Process " << process.getProcessID() << ": processing action - end" << endl;
	 	 	}
	 	}

	 // INTERRUPT LINES //////////////////////////////////
	 else 
	 	{
		 if(whereToLog == LOG_TO_FILE)
	 	 	{
		 	 stream << getTime(timer) << "Interrupt: Process " << process.getProcessID() << " - " << stage << endl;
	 	 	}
	 	 else
	 	 	{
		 	 cout << getTime(timer) << "Interrupt: Process " << process.getProcessID() << " - " << stage << endl;
		 	 stream << getTime(timer) << "Interrupt: Process " << process.getProcessID() << " - " << stage << endl;
	 	 	}
	 	}	
  	 
  	 addLineToLogData(stream.str());
  	}

 void printTime(SimpleTimer timer)
 	{
 	 char * elapsedTime = new char[20];

	 timer.stop();
	 timer.getElapsedTime(elapsedTime);
	 cout << elapsedTime << " - ";

	 delete [] elapsedTime;
 	}

 string getTime(SimpleTimer timer)
 	{
 	 char* elapsedTime = new char[20];
 	 string elapsedTimeString;

 	 timer.stop();
 	 timer.getElapsedTime(elapsedTime);
 	 elapsedTimeString = string(elapsedTime) + " - ";

 	 delete [] elapsedTime;
 	 return elapsedTimeString;
 	}

 void addLineToLogData(string add)
 	{
 	 if(logData.getSize() >= logData.getCapacity())
 	 	{
 	 	 logData.grow(logData.getCapacity());
 	 	}

 	 logData[lineNumber] = add;
 	 lineNumber++;
 	 logData.incrementSize();
 	}

 void logToFile(string fileName)
 	{
 	 ofstream fout;
 	 int index;


 	 if(whereToLog == LOG_TO_FILE || whereToLog == LOG_TO_BOTH)
 	 	{
		 fout.open(fileName.c_str()); 
		
	 	 if(!fout.good())
	 	 	{
	 	 	 cout << "ERROR: Could not open the logfile. PROGRAM ENDING." << endl;
	 	 	}
		 
		 else
			{
	 	 	 for(index = 0; index < lineNumber; index++)
	 	 	 	{
	 	 	 	 fout << logData[index];
	 	 	 	}
			}
 	 	} 	 	 
 	 	

 	 fout.close();
 	}
};
