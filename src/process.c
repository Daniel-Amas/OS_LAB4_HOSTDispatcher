#include "dispatch.h"
#include <stdio.h>

// Function to allocate resources to a process
void allocateResources(Process *process) {
    // Ensure requested resources do not exceed available resources
    if (process->printers > MAX_PRINTERS || process->scanners > MAX_SCANNERS ||
        process->modems > MAX_MODEMS || process->cds > MAX_CDS ||
        process->memory_required > TOTAL_MEMORY) {
        printf("Insufficient resources for Process %d\n", process->pid);
    } else {
        // Update resource availability
        MAX_PRINTERS -= process->printers;
        MAX_SCANNERS -= process->scanners;
        MAX_MODEMS -= process->modems;
        MAX_CDS -= process->cds;
        TOTAL_MEMORY -= process->memory_required;
        printf("Resources allocated for Process %d\n", process->pid);
    }
}

// Function to free resources allocated to a process
void freeResources(Process *process) {
    // Update resource availability
    MAX_PRINTERS += process->printers;
    MAX_SCANNERS += process->scanners;
    MAX_MODEMS += process->modems;
    MAX_CDS += process->cds;
    TOTAL_MEMORY += process->memory_required;
    printf("Resources freed for Process %d\n", process->pid);
}
