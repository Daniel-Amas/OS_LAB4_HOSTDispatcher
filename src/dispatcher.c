#include <stdio.h>
#include "process.h"
#include "queue.h"
#include "resource.h"
#include "memory.h"

int main() {
    struct Process processes[MAX_PROCESSES];
    int num_processes;
    struct Resource resources;
    struct Memory memory;

    // Initialize data structures
    Queue real_time_queue, user_queue;
    init_queue(&real_time_queue);
    init_queue(&user_queue);
    init_resources(&resources);
    init_memory(&memory);

    // Read dispatch list
    read_dispatch_list("dispatch_list.csv", processes, &num_processes);

    // Process each task from dispatch list
    for (int i = 0; i < num_processes; i++) {
        struct Process process = processes[i];

        // Resource allocation
        if (process.priority == 0) {
            if (!allocate_memory(&memory, process.memory_size)) {
                printf("Real-time process cannot be executed due to insufficient memory.\n");
                continue;
            }
        } else {
            if (!request_resources(&resources, process)) {
                printf("User process %d cannot be executed due to insufficient resources.\n", i);
                continue;
            }
            if (!allocate_memory(&memory, process.memory_size)) {
                printf("User process %d cannot be executed due to insufficient memory.\n", i);
                continue;
            }
        }

        // Execute process
        printf("Executing Process %d:\n", i);
        printf("Arrival Time: %d\n", process.arrival_time);
        printf("Priority: %d\n", process.priority);
        printf("Processor Time: %d\n", process.processor_time);
        printf("Memory Size: %d\n", process.memory_size);
        printf("Printers: %d\n", process.printers);
        printf("Scanners: %d\n", process.scanners);
        printf("Modems: %d\n", process.modems);
        printf("CDs: %d\n", process.cds);
        printf("\n");

        // Free resources
        if (process.priority == 0) {
            deallocate_memory(&memory, process.memory_size);
        } else {
            release_resources(&resources, process);
            deallocate_memory(&memory, process.memory_size);
        }
    }

    return 0;
}
