#include "lib_sys.h"
#include <threads.h>
#include <stdlib.h>
#include <stdio.h>

uint8_t _log_cpu(struct cpu_struct* cpu_struct_ptr);

static struct log_data* _lib_sys_log(struct log_data* log_data_ptr)
{
    // loop through, such so that the thread lies down
    int i = 0;
    while (log_data_ptr->signal == 1)
    {
        // sleep for 1/signal seconds
        thrd_sleep(&log_data_ptr->time, NULL);

        if (log_data_ptr->cpu_struct_ptr)
        {
            _log_cpu(log_data_ptr->cpu_struct_ptr);
        }
    }   
}
thrd_t lib_sys_log(struct log_data* log_data_ptr)
{
    // log_data_ptr->time.tv_nsec = (10000000000 / 60);
    log_data_ptr->time.tv_sec = 1;
    log_data_ptr->signal = 1;
    log_data_ptr->cpu_struct_ptr = (void*)0;
    // make a thread
    thrd_t thread;
    int result = thrd_create(&thread, (void*)(_lib_sys_log), log_data_ptr);
    if (result != thrd_success)
        return 0;
    return thread;
}


