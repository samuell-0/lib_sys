#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include <threads.h>
#include <stdbool.h>
#include <stdio.h>
#include "string.h"


struct log_data//user owns it
{
    bool signal;
    struct timespec time;
    struct cpu_info* cpu_info_ptr;
    struct mem_info* mem_info_ptr;
    void* usr_data_ptr;
};
struct cpu_stat
{
    long long user, nice, system, idle, iowait, irq, softirq, steal;
};
struct cpu_info
{
    char vendor_id[60];
    char model_name[20];
    int cpu_cores;
    int siblings;
    float cpu_mhz;
    int cache_size_kb;

    uint8_t size_of_arr;
    uint8_t* arr_percentages;

    struct cpu_stat stat_curr;
    struct cpu_stat stat_prev;
};
struct mem_stat {
    uint64_t mem_free_kb;
    uint64_t mem_available_kb;
    uint64_t buffers_kb;
    uint64_t cached_kb;
    uint64_t swap_free_kb;

    uint64_t used_kb;
};
struct mem_info {
    uint64_t mem_total_kb;
    uint64_t swap_total_kb;

    struct mem_stat mem_stat_;

    uint8_t size_of_arr;
    uint8_t* arr_percentages;
};


thrd_t lib_sys_log(struct log_data* log_data_ptr);

thrd_t lib_sys_log_stop(struct log_data* log_data_ptr);

// CPU
struct cpu_info* lib_sys_log_cpu(struct log_data* log_data_ptr);

void lib_sys_log_stop_cpu(struct log_data* log_data_ptr);

// MEMORY
struct mem_info* lib_sys_log_mem(struct log_data* log_data_ptr);

void lib_sys_log_stop_mem(struct log_data* log_data_ptr);


static inline void append(uint8_t* arr, uint16_t n, uint8_t v)
{
    memmove(arr, arr + 1, n - 1);
    arr[n - 1] = v;
}   
#ifdef __cplusplus
}
#endif