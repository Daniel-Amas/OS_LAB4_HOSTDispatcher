#include "resource.h"

void init_resources(struct Resource *resources) {
    resources->printers = 2;
    resources->scanners = 1;
    resources->modems = 1;
    resources->cds = 2;
}

int request_resources(struct Resource *resources, struct Process process) {
    if (resources->printers < process.printers ||
        resources->scanners < process.scanners ||
        resources->modems < process.modems ||
        resources->cds < process.cds) {
        return 0; // Insufficient resources
    }

    resources->printers -= process.printers;
    resources->scanners -= process.scanners;
    resources->modems -= process.modems;
    resources->cds -= process.cds;

    return 1; // Resources allocated successfully
}

void release_resources(struct Resource *resources, struct Process process) {
    resources->printers += process.printers;
    resources->scanners += process.scanners;
    resources->modems += process.modems;
    resources->cds += process.cds;
}
