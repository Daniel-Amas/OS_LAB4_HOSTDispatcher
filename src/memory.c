#include "memory.h"

void init_memory(struct Memory *memory) {
    memory->total = 1024;
    memory->available = 960; // Leave 64 MB for real-time processes
}

int allocate_memory(struct Memory *memory, int size) {
    if (memory->available < size) {
        return 0; // Insufficient memory
    }

    memory->available -= size;
    return 1; // Memory allocated successfully
}

void deallocate_memory(struct Memory *memory, int size) {
    memory->available += size;
}
