// SystemConfig implementation

#include "SystemConfig.h"
#include <fstream>
#include <iostream>

using namespace std;

#ifndef SYSTEMCONFIG_CPP
#define SYSTEMCONFIG_CPP

SystemConfig::SystemConfig()
	{

	}

SystemConfig::SystemConfig(string configFile)
	{
	 string dummy;
 	 ifstream fin;

	 fin.open(configFile.c_str());

	 // Version number
	 fin.ignore(256,'\n');
	 fin.ignore(256,':');
	 fin >> version;

	 // Metadata
	 fin.ignore(256,':');
	 fin.ignore(1,' ');
	 getline(fin, filePath);

	 // Schedule type
	 fin.ignore(256,':');
	 fin.ignore(1,' ');
	 getline(fin, scheduleType);	

	 // Quantum time
	 fin.ignore(256,':');
	 fin >> quantumTime;	  

	 // Processor cycle time
	 fin.ignore(256,':');
	 fin >> processorCycleTime;

	 // Monitor display time
	 fin.ignore(256,':');
	 fin >> monitorDisplayTime;

	 // Hard drive display time
	 fin.ignore(256,':');
	 fin >> hddCycleTime;

	 // Printer cycle time
	 fin.ignore(256,':');
	 fin >> printerCycleTime;	 

	 // Keyboard cycle time
	 fin.ignore(256,':');
	 fin >> keyboardCycleTime;

	 // Where to Log
	 fin.ignore(256,':');
	 fin.ignore(1,' ');
	 getline(fin, whereToLog);

	 // Log file path
	 fin.ignore(256,':');
	 fin.ignore(1,' ');
	 getline(fin, logFilePath);
	}

SystemConfig::~SystemConfig()
	{

	}

string SystemConfig::getFilePath()
	{
	 return filePath;
	}	

string SystemConfig::getScheduleType()
	{
	 return scheduleType;
	}

int SystemConfig::getQuantumTime()
	{
	 return quantumTime;
	}

int SystemConfig::getProcessorCycleTime()
	{
	 return processorCycleTime;
	}

int SystemConfig::getMonitorDisplayTime()
	{
	 return monitorDisplayTime;
	}

int SystemConfig::getHDDCycleTime()
	{
	 return hddCycleTime;
	}

int SystemConfig::getPrinterCycleTime()
	{
	 return printerCycleTime;
	}

int SystemConfig::getKeyboardCycleTime()
	{
	 return keyboardCycleTime;
	}

string SystemConfig::getWhereToLog()
	{
	 return whereToLog;
	}

string SystemConfig::getLogFilePath()
	{
	 return logFilePath;
	}

SystemConfig& SystemConfig::operator=(const SystemConfig& rhConfig)
	{
	 if(this != &rhConfig)
	 	{
	 	 version = rhConfig.version;
		 filePath = rhConfig.filePath;
		 scheduleType = rhConfig.scheduleType;
		 processorCycleTime = rhConfig.processorCycleTime;
		 quantumTime = rhConfig.quantumTime;
		 monitorDisplayTime = rhConfig.monitorDisplayTime;
		 hddCycleTime = rhConfig.hddCycleTime;
		 printerCycleTime = rhConfig.printerCycleTime;
		 keyboardCycleTime = rhConfig.keyboardCycleTime;
		 whereToLog = rhConfig.whereToLog;
		 logFilePath = rhConfig.logFilePath;
	 	}

	 return *this;
	}

#endif