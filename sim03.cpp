#include "OperatingSystem.h"
#include "ProcessControlBlock.h"
#include "SimpleTimer.cpp"
#include "Task.h"
#include <iostream>

int main(int argc, char* argv[])
{
 // Variables
 string configFile;
 SimpleTimer timer;

 timer.start();

 // Check to make sure Config File was given
 if(argc < 2)
 	{
 	 cout << "No configuration file was given. Please add the configuration ";
 	 cout << "file name when executing process."<< endl <<"Program terminated" << endl;
 	 return 0;
 	}
 else
 	{
 	 configFile = argv[1];
 	}

 OperatingSystem opSys(timer);
 opSys.configure(argv[1], timer);
 opSys.uploadProcesses(timer);
 opSys.simulate(timer);
 timer.stop();
 
 return 0;
}
