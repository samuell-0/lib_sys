#include "lib_sys.h"
#include <threads.h>
#include <stdlib.h>
#include <stdio.h>

uint8_t _log_cpu(struct cpu_info* cpu_info_ptr);
struct user_data
{
    void* ptr_to_func;
    void** arg_arr;
    uint8_t n_arr;
};
static struct log_data* _lib_sys_log(struct log_data* log_data_ptr)
{
    while (log_data_ptr->signal == true)
    {
        thrd_sleep(&log_data_ptr->time, NULL);

        if (log_data_ptr->cpu_info_ptr != NULL)
            _log_cpu(log_data_ptr->cpu_info_ptr);

        // this callback might be scrapped, since most slint APIs must be called on the main thread instead
        if(log_data_ptr->user_data_ptr != NULL)
            ((void* (*)(void* [], uint8_t))((struct user_data*)(log_data_ptr->user_data_ptr))->ptr_to_func)
                (((struct user_data*)(log_data_ptr->user_data_ptr))->arg_arr, ((struct user_data*)(log_data_ptr->user_data_ptr))->n_arr);
    }   
}

thrd_t lib_sys_log(struct log_data* log_data_ptr)
{
    // log_data_ptr->time.tv_nsec = (10000000000 / 60);
    log_data_ptr->time.tv_sec = 1;

    log_data_ptr->signal = true;

    thrd_t thread;
    int result = thrd_create(&thread, (void*)(_lib_sys_log), log_data_ptr);
    if (result != thrd_success)
        return 0;
    return thread;
}


