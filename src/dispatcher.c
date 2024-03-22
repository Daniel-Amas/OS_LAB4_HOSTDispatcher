#include <stdio.h>
#include <stdlib.h>
#include "dispatch.h"

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

        // Allocate resources for the process
        allocateResources(&process);

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

        // Free resources after process completion
        freeResources(&process);
    }

    fclose(file);
    return 0;
}
