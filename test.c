#include <stdio.h>
#include "lib_sys.h"
void update(struct log_data* log_data_ptr)
{
    printf("%u%%\n", log_data_ptr->cpu_info_ptr->usage);
}
int main()
{
    struct log_data data;

    void (*update_func_ptr)(struct log_data* log_data_ptr) = update;
    data.update_func_ptr = update_func_ptr;

    thrd_t thread_ptr = lib_sys_log(&data);

    lib_sys_log_cpu(&data);

    struct timespec time;
    time.tv_nsec = 0;
    time.tv_sec = 1;

    lib_sys_log_stop_cpu(&data);
    thrd_join(thread_ptr, NULL);
    return 0;
}