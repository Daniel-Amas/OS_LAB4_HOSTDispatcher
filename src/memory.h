#ifndef MEMORY_H
#define MEMORY_H

struct Memory {
    int total;
    int available;
};

void init_memory(struct Memory *memory);
int allocate_memory(struct Memory *memory, int size);
void deallocate_memory(struct Memory *memory, int size);

#endif /* MEMORY_H */
