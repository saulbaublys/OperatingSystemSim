CC = g++
DEBUG = -g
PTHREAD = -pthread
CFLAGS = -Wall -c
LFLAGS = -Wall

sim03: sim03.o SystemConfig.o OperatingSystem.o PriorityQueue.o SimpleTimer.o ProcessControlBlock.o SimpleVector.o Task.o
	$(CC) $(LFLAGS) $(PTHREAD) sim03.o SystemConfig.o OperatingSystem.o PriorityQueue.o ProcessControlBlock.o SimpleVector.o Task.o -o sim03

sim03.o: sim03.cpp OperatingSystem.h SimpleTimer.h OperatingSystem.cpp PriorityQueue.cpp ProcessControlBlock.h ProcessControlBlock.cpp SimpleVector.h SimpleVector.cpp 
	$(CC) $(CFLAGS) sim03.cpp

OperatingSystem.o: OperatingSystem.h log.cpp SimpleTimer.h SystemConfig.h OperatingSystem.cpp ProcessControlBlock.h PriorityQueue.cpp ProcessControlBlock.cpp
	$(CC) $(CFLAGS) $(PTHREAD) OperatingSystem.cpp

PriorityQueue.o: PriorityQueue.h ProcessControlBlock.h
	$(CC) $(CFLAGS) $(PTHREAD) PriorityQueue.cpp

SystemConfig.o: SystemConfig.h SystemConfig.cpp
	$(CC) $(CFLAGS) SystemConfig.cpp

ProcessControlBlock.o: ProcessControlBlock.h SimpleVector.h Task.h
	$(CC) $(CFLAGS) ProcessControlBlock.cpp

SimpleVector.o: SimpleVector.h SimpleVector.cpp
	$(CC) $(CFLAGS) SimpleVector.cpp

Task.o: Task.h Task.cpp
	$(CC) $(CFLAGS) Task.cpp

clean:
	\rm *.o sim03
