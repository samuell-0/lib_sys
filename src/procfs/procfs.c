#include "procfs.h"
#include "lib_sys.h"
#include <string.h>
#include <unistd.h>

// This helper parses the first line of /proc/stat
void _parse_cpu_stat(struct cpu_stat* cpu_stat_ptr)
{
    if (cpu_stat_ptr == NULL) return;
    
    FILE* file = fopen("/proc/stat", "r");
    if (!file)
        return;

    fscanf(file, "cpu %lld %lld %lld %lld %lld %lld %lld %lld",
            &cpu_stat_ptr->user, &cpu_stat_ptr->nice, &cpu_stat_ptr->system, &cpu_stat_ptr->idle,
            &cpu_stat_ptr->iowait, &cpu_stat_ptr->irq, &cpu_stat_ptr->softirq, &cpu_stat_ptr->steal);
    fclose(file);

}

void _parse_cpu_details(struct cpu_info* cpu_info_ptr)
{
    FILE* file = fopen("/proc/cpuinfo", "r");
    if (!file) {
        perror("fopen");
        return;
    }

    char line[512];

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "vendor_id", 9) == 0) {
            sscanf(line, "vendor_id : %[^\n]", cpu_info_ptr->vendor_id);
        }
        else if (strncmp(line, "model name", 10) == 0) {
            sscanf(line, "model name : %[^\n]", cpu_info_ptr->model_name);
        }
        else if (strncmp(line, "cpu cores", 9) == 0) {
            sscanf(line, "cpu cores : %d", &cpu_info_ptr->cpu_cores);
        }
        else if (strncmp(line, "siblings", 8) == 0) {
            sscanf(line, "siblings : %d", &cpu_info_ptr->siblings);
        }
        else if (strncmp(line, "cpu MHz", 7) == 0) {
            sscanf(line, "cpu MHz : %f", &cpu_info_ptr->cpu_mhz);
        }
        else if (strncmp(line, "cache size", 10) == 0) {
            sscanf(line, "cache size : %d", &cpu_info_ptr->cache_size_kb);
        }
    }

    fclose(file);
}

void _parse_mem_stat(struct mem_stat* mem_stat_ptr)
{
    if (mem_stat_ptr == NULL) return;

    // memset(mem_stat_ptr, 0, sizeof(struct mem_stat));

    FILE *file = fopen("/proc/meminfo", "r");
    if (!file)
        return;

    char key[64];
    uint64_t value;
    char unit[16];

    while (fscanf(file, "%63[^:]: %lu %15s\n", key, &value, unit) == 3)
    {
        if (strcmp(key, "MemFree") == 0)
            mem_stat_ptr->mem_free_kb = value;

        else if (strcmp(key, "MemAvailable") == 0)
            mem_stat_ptr->mem_available_kb = value;

        else if (strcmp(key, "Buffers") == 0)
            mem_stat_ptr->buffers_kb = value;

        else if (strcmp(key, "Cached") == 0)
            mem_stat_ptr->cached_kb = value;

        else if (strcmp(key, "SwapFree") == 0)
            mem_stat_ptr->swap_free_kb = value;
    }

    fclose(file);
}

void _parse_mem_details(struct mem_info* mem_info_ptr)
{
    if (mem_info_ptr == NULL)
        return;

    memset(mem_info_ptr, 0, sizeof(struct mem_info));

    FILE *file = fopen("/proc/meminfo", "r");
    if (!file)
        return;

    char key[64];
    uint64_t value;
    char unit[16];

    while (fscanf(file, "%63[^:]: %lu %15s\n", key, &value, unit) == 3)
    {
        if (strcmp(key, "MemTotal") == 0)
            mem_info_ptr->mem_total_kb = value;

        else if (strcmp(key, "SwapTotal") == 0)
            mem_info_ptr->swap_total_kb = value;
    }

    fclose(file);
}