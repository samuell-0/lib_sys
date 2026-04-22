#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include <threads.h>
#include <stdbool.h>
#include <stdio.h>

struct log_data//user owns it
{
    bool signal;
    struct timespec time;
    struct cpu_info* cpu_info_ptr;
    void* usr_data_ptr;

};
struct cpu_stat
{
    long long user, nice, system, idle, iowait, irq, softirq, steal;
};
struct cpu_info
{
    uint8_t usage;
    struct cpu_stat stat_curr;
    struct cpu_stat stat_prev;
};

thrd_t lib_sys_log(struct log_data* log_data_ptr);

// CPU
struct cpu_info* lib_sys_log_cpu(struct log_data* log_data);

uint8_t lib_sys_log_stop_cpu(struct log_data* log_data);

#ifdef __cplusplus
}
#endif