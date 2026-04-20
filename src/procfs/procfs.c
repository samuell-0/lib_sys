#include "procfs.h"
#include "lib_sys.h"
#include <string.h>
#include <unistd.h>

// This helper parses the first line of /proc/stat
void _parse_cpu_stat(struct cpu_stat* cpu_stat_ptr)
{
    FILE* file = fopen("/proc/stat", "r");

    fscanf(file, "cpu %lld %lld %lld %lld %lld %lld %lld %lld",
            &cpu_stat_ptr->user, &cpu_stat_ptr->nice, &cpu_stat_ptr->system, &cpu_stat_ptr->idle,
            &cpu_stat_ptr->iowait, &cpu_stat_ptr->irq, &cpu_stat_ptr->softirq, &cpu_stat_ptr->steal);
    fclose(file);

}

void _parse_cpu_details(struct cpu_struct* cpu_struct_ptr)
{
    FILE* file = fopen("/proc/cpuinfo", "r");
    // fscanf(file, "model name");
    fclose(file);
}

void _parse_mem_stat(struct cpu_stat* cpu_stat_ptr)
{

}