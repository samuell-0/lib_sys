#include <stdio.h>
#include "lib_sys.h"
#include <threads.h>
int main()
{
    struct log_data data;
    thrd_t thread_ptr = lib_sys_log(&data);
    lib_sys_log_cpu(&data);

    struct timespec time;
    time.tv_nsec = 0;
    time.tv_sec = 1;

    while (true)
    {
        thrd_sleep(&time, NULL);
        printf("%u%%\n", data.cpu_info_ptr->usage);

    }
    lib_sys_log_stop_cpu(&data);
    thrd_join(thread_ptr, NULL);
    return 0;
}