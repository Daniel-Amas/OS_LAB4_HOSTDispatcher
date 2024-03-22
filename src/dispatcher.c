#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

int main() {
    // Prompt the user for the file path
    char file_path[256];
    printf("Please enter the file path: ");
    scanf("%255s", file_path);

    // Open dispatch list file
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }


    // Read processes from file and execute
    Process process;
    while (fscanf(file, "%d, %d, %d, %d, %d, %d, %d, %d", &process.arrival_time, &process.priority, &process.processor_time, &process.memory_required, &process.printers, &process.scanners, &process.modems, &process.cds) != EOF) {
        process.pid++; // Assigning process ID
        displayProcessInfo(process);

        // Check priority and dispatch accordingly
        if (process.priority == 0) {
            runRealTime(process);
        } else {
            if (process.priority == 1) {
                runUserProcess(process);
            } else {
                runRoundRobinUser(process);
            }
        }
    }

    fclose(file);
    return 0;
}

// Function to execute a real-time process with highest priority
void runRealTime(Process process) {
    printf("Executing Real-Time Process\n");
    while (process.processor_time > 0) {
        printf("Process %d is running\n", process.pid);
        process.processor_time--;
    }
    printf("Process %d has finished execution\n", process.pid);
}

// Function to execute a user process with feedback scheduler
void runUserProcess(Process process) {
    printf("Executing User Process with Feedback Scheduler\n");
    while (process.processor_time > 0) {
        printf("Process %d is running\n", process.pid);
        process.processor_time--;
        if (process.processor_time == 0) {
            printf("Process %d has finished execution\n", process.pid);
        }
    }

    // Check if process completed within current priority level
    if (process.processor_time > 0) {
        lowerPriority(&process);
    }
}

// Function to execute a user process with round robin scheduler
void runRoundRobinUser(Process process) {
    printf("Executing User Process with Round Robin Scheduler\n");
    while (process.processor_time > 0) {
        printf("Process %d is running\n", process.pid);
        process.processor_time--;
        if (process.processor_time == 0) {
            printf("Process %d has finished execution\n", process.pid);
        }
    }

    // Check if process completed within current priority level
    if (process.processor_time > 0) {
        lowerPriority(&process);
    }
}

// Function to lower priority of a process
void lowerPriority(Process *process) {
    // Lower priority if possible
    if (process->priority < 3) {
        process->priority++;
        printf("Lowering priority of Process %d\n", process->pid);
    }
}

// Function to display process information
void displayProcessInfo(Process process) {
    printf("Process ID: %d, Priority: %d, Processor Time Remaining: %d, Memory Location: %d, Memory Block Size: %d\n", process.pid, process.priority, process.processor_time, 0, process.memory_required);
}

