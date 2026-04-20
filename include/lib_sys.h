#include <stddef.h>
#include <stdint.h>
#include <threads.h>
#include <stdbool.h>
#include <stdio.h>

struct log_data
{
    uint8_t signal;
    struct timespec time;
    struct cpu_struct* cpu_struct_ptr;
};
struct cpu_stat
{
    long long user, nice, system, idle, iowait, irq, softirq, steal;
};
struct cpu_struct
{
    char* name;
    struct cpu_stat stat_curr;
    uint8_t usage;
};

thrd_t lib_sys_log(struct log_data* log_data_ptr);

// CPU
struct cpu_struct* lib_sys_log_cpu(struct log_data* log_data);

uint8_t lib_sys_log_stop_cpu(struct log_data* log_data);
