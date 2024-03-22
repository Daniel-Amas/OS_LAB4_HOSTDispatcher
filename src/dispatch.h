#ifndef DISPATCH_H
#define DISPATCH_H

// Constants for resource availability
#define MAX_PRINTERS 2
#define MAX_SCANNERS 1
#define MAX_MODEMS 1
#define MAX_CDS 2
#define TOTAL_MEMORY 1024 // in MBytes
#define REAL_TIME_MEMORY 64 // in MBytes

// Structure to represent a process
typedef struct {
    int arrival_time;
    int priority;
    int processor_time;
    int memory_required;
    int printers;
    int scanners;
    int modems;
    int cds;
    int pid; // Process ID
} Process;

// Function prototypes
void runRealTime(Process process);
void runUserProcess(Process process);
void runRoundRobinUser(Process process);
void lowerPriority(Process *process);
void displayProcessInfo(Process process);
void allocateResources(Process *process);
void freeResources(Process *process);

#endif /* DISPATCH_H */
