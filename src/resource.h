#ifndef RESOURCE_H
#define RESOURCE_H

struct Resource {
    int printers;
    int scanners;
    int modems;
    int cds;
};

void init_resources(struct Resource *resources);
int request_resources(struct Resource *resources, struct Process process);
void release_resources(struct Resource *resources, struct Process process);

#endif /* RESOURCE_H */
