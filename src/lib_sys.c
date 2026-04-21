#include "lib_sys.h"
#include <threads.h>
#include <stdlib.h>
#include <stdio.h>

uint8_t _log_cpu(struct cpu_info* cpu_info_ptr);

static struct log_data* _lib_sys_log(struct log_data* log_data_ptr)
{
    while (log_data_ptr->signal == true)
    {
        thrd_sleep(&log_data_ptr->time, NULL);

        if (log_data_ptr->cpu_info_ptr != NULL)
            _log_cpu(log_data_ptr->cpu_info_ptr);
        
        log_data_ptr->update_func_ptr(log_data_ptr);
    }   
}

thrd_t lib_sys_log(struct log_data* log_data_ptr)
{
    // log_data_ptr->time.tv_nsec = (10000000000 / 60);
    log_data_ptr->time.tv_sec = 1;

    log_data_ptr->signal = 1;
    log_data_ptr->cpu_info_ptr = (void*)0;

    thrd_t thread;
    int result = thrd_create(&thread, (void*)(_lib_sys_log), log_data_ptr);
    if (result != thrd_success)
        return 0;
    return thread;
}


