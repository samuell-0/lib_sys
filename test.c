#include <stdio.h>
#include "lib_sys.h"
struct user_data
{
    void* ptr_to_func;
    void* arg_arr;
    uint8_t n_arr;
};
void update(struct log_data* log_data_ptr)
{
    printf("%u%%\n", log_data_ptr->cpu_info_ptr->usage);
}
int main()
{
    struct log_data data;

    struct user_data _user_data;
    data.user_data_ptr = &_user_data;

    thrd_t thread_ptr = lib_sys_log(&data);

    lib_sys_log_cpu(&data);

    lib_sys_log_stop_cpu(&data);
    thrd_join(thread_ptr, NULL);
    return 0;
}