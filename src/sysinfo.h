#ifndef SYSINFO_H
#define SYSINFO_H

typedef struct {
    char model[32];
    char firmware[16];
    char motherboard[32];
    unsigned int cpu_cores;
    unsigned int cpu_freq;
    unsigned int total_ram;
    unsigned int free_ram;
    unsigned int used_ram;
    unsigned int total_vram;
    unsigned int free_vram;
    char mac_address[18];
    char ip_address[16];
} SystemInfo;

int get_system_info(SystemInfo* info);
int get_cpu_frequency(void);
int get_memory_info(unsigned int* total, unsigned int* used, unsigned int* free);

#endif
