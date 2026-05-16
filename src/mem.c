#include "lib_sys.h"
#include <stdlib.h>
#include "procfs/procfs.h"


struct mem_info* lib_sys_log_mem(struct log_data* log_data_ptr)
{
    struct mem_info* mem_info_ptr = (struct mem_info*)malloc(sizeof(struct mem_info));
    mem_info_ptr->arr_percentages = (uint8_t*)malloc(100 * sizeof(uint8_t));
    log_data_ptr->mem_info_ptr = mem_info_ptr;

    _parse_mem_details(mem_info_ptr);

    return mem_info_ptr;
}

void lib_sys_log_stop_mem(struct log_data* log_data)
{

}

void _mem_calculate_usage(struct mem_stat* mem_stat_ptr, struct mem_info* mem_info_ptr)
{
    if (mem_info_ptr->arr_percentages == NULL) return;

    if (mem_stat_ptr->mem_available_kb > 0)
        mem_stat_ptr->used_kb =
            mem_info_ptr->mem_total_kb - mem_stat_ptr->mem_available_kb;
    else
        mem_stat_ptr->used_kb =
            mem_info_ptr->mem_total_kb - mem_stat_ptr->mem_free_kb;

    if (mem_info_ptr->mem_total_kb > 0)
        append(mem_info_ptr->arr_percentages, 100, (uint8_t)((mem_stat_ptr->used_kb * 100) / mem_info_ptr->mem_total_kb));
}
// NOTE: should be reducted if this is all it does
void _log_mem(struct mem_info* mem_info_ptr)
{
    _parse_mem_stat(&mem_info_ptr->mem_stat_);
    _mem_calculate_usage(&mem_info_ptr->mem_stat_, mem_info_ptr);
}