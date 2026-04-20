#include <lib_sys.h>
#include "procfs/procfs.h"
#include <stdlib.h>
#include <stdio.h>
// PUBLIC
struct cpu_struct* lib_sys_log_cpu(struct log_data* log_data_ptr)
{
    // allocate cpu_struct
    struct cpu_struct* cpu_struct_ptr = malloc(sizeof *cpu_struct_ptr);
    log_data_ptr->cpu_struct_ptr = cpu_struct_ptr;

    _parse_cpu_details(cpu_struct_ptr);

    return cpu_struct_ptr;
}

uint8_t lib_sys_log_stop_cpu(struct log_data* log_data_ptr)
{
    // deallocate cpu_struct
    // 
}

// PRIVATE
uint8_t _calculate_usage(struct cpu_stat* prev, struct cpu_stat* curr) {

    long long prev_total = prev->user + prev->nice + prev->system + prev->idle + 
                           prev->iowait + prev->irq + prev->softirq + prev->steal;
    long long curr_total = curr->user + curr->nice + curr->system + curr->idle + 
                           curr->iowait + curr->irq + curr->softirq + curr->steal;

    long long prev_idle = prev->idle + prev->iowait;
    long long curr_idle = curr->idle + curr->iowait;

    long long total_diff = curr_total - prev_total;
    long long idle_diff = curr_idle - prev_idle;

    if (total_diff == 0) return 0;
    
    return (uint8_t)((total_diff - idle_diff) * 100 / total_diff);
}

uint8_t _log_cpu(struct cpu_struct* cpu_struct_ptr)
{
    struct cpu_stat stat_prev = cpu_struct_ptr->stat_curr;
    _parse_cpu_stat(&cpu_struct_ptr->stat_curr);
    cpu_struct_ptr->usage = _calculate_usage(&stat_prev, &cpu_struct_ptr->stat_curr);
    return 0;
}

