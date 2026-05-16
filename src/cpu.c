#include <lib_sys.h>
#include "procfs/procfs.h"
#include <stdlib.h>
#include <stdio.h>

// PUBLIC
struct cpu_info* lib_sys_log_cpu(struct log_data* log_data_ptr)
{
    // allocate cpu_info
    struct cpu_info* cpu_info_ptr = (struct cpu_info*)malloc(sizeof(struct cpu_info));
    cpu_info_ptr->arr_percentages = (uint8_t*)calloc(100, sizeof(uint8_t));
    log_data_ptr->cpu_info_ptr = cpu_info_ptr;

    _parse_cpu_details(cpu_info_ptr);
    printf("Vendor ID   : %s\n", cpu_info_ptr->vendor_id);
    printf("Model Name  : %s\n", cpu_info_ptr->model_name);
    printf("CPU Cores   : %d\n", cpu_info_ptr->cpu_cores);
    printf("Siblings    : %d\n", cpu_info_ptr->siblings);
    printf("CPU MHz     : %.2f\n", cpu_info_ptr->cpu_mhz);
    printf("Cache Size  : %d KB\n", cpu_info_ptr->cache_size_kb);
    return cpu_info_ptr;
}

void lib_sys_log_stop_cpu(struct log_data* log_data_ptr)
{
    // deallocate cpu_info
    // 
}

// PRIVATE
void _cpu_calculate_usage(struct cpu_info* cpu_info_ptr) {

    if (cpu_info_ptr->arr_percentages == NULL) return;

    long long prev_total = cpu_info_ptr->stat_prev.user + cpu_info_ptr->stat_prev.nice + cpu_info_ptr->stat_prev.system + cpu_info_ptr->stat_prev.idle + 
                           cpu_info_ptr->stat_prev.iowait + cpu_info_ptr->stat_prev.irq + cpu_info_ptr->stat_prev.softirq + cpu_info_ptr->stat_prev.steal;
    long long curr_total = cpu_info_ptr->stat_curr.user + cpu_info_ptr->stat_curr.nice + cpu_info_ptr->stat_curr.system + cpu_info_ptr->stat_curr.idle + 
                           cpu_info_ptr->stat_curr.iowait + cpu_info_ptr->stat_curr.irq + cpu_info_ptr->stat_curr.softirq + cpu_info_ptr->stat_curr.steal;

    long long prev_idle = cpu_info_ptr->stat_prev.idle + cpu_info_ptr->stat_prev.iowait;
    long long curr_idle = cpu_info_ptr->stat_curr.idle + cpu_info_ptr->stat_curr.iowait;

    long long total_diff = curr_total - prev_total;
    long long idle_diff = curr_idle - prev_idle;

    if (total_diff == 0) 
    {
        append(cpu_info_ptr->arr_percentages, 100, 0);
        return;
    }
    
    append(cpu_info_ptr->arr_percentages, 100, (uint8_t)((total_diff - idle_diff) * 100 / total_diff));
}

void _log_cpu(struct cpu_info* cpu_info_ptr)
{
    cpu_info_ptr->stat_prev = cpu_info_ptr->stat_curr;
    _parse_cpu_stat(&cpu_info_ptr->stat_curr);
    _cpu_calculate_usage(cpu_info_ptr);
}

