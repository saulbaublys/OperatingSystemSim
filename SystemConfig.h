// SystemConfig defenition
#include <string>

using namespace std;

#ifndef SYSTEMCONFIG_H
#define SYSTEMCONFIG_H
 
class SystemConfig
{
 public:
 	SystemConfig();
 	SystemConfig(string configFile);
 	~SystemConfig();
 	string getFilePath();
 	string getScheduleType();
 	int getQuantumTime();
 	int getProcessorCycleTime();
 	int getMonitorDisplayTime();
 	int getHDDCycleTime();
 	int getPrinterCycleTime();
 	int getKeyboardCycleTime();
 	string getWhereToLog();
 	string getLogFilePath();
 	SystemConfig &operator=(const SystemConfig& rhConfig);
 	

 private:
 	double version;
 	string filePath;
 	string scheduleType;
 	int quantumTime;
 	int processorCycleTime;
 	int monitorDisplayTime;
 	int hddCycleTime;
 	int printerCycleTime;
 	int keyboardCycleTime;
 	string whereToLog;
 	string logFilePath;
};

#endif