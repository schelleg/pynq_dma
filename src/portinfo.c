/* File: /group/xrlabs2/grahams/SDSoC/pynq_sdx20163/sdsoc_workspace/pynq_dma/Debug/_sds/p0/.cf_work/portinfo.c */
#include "cf_lib.h"
#include "cf_request.h"
#include "sds_lib.h"
#include "sds_trace.h"
#include "portinfo.h"
#include "stdio.h"  // for printf
#include "xlnk_core_cf.h"
#include "accel_info.h"
#include "axi_lite_dm.h"
#include "zero_copy_dm.h"

accel_info_t _sds__p0_array_zero_copy_1 = {
  .device_id = 0,
  .phys_base_addr = 0x83c00000,
  .addr_range = 0x10000,
  .func_name = "array_zero_copy_1",
  .ip_type = "axis_acc_adapter",
  .irq = 0,
};

int _p0_swinst_array_zero_copy_1_cmd_array_zero_copy_sg_list[] = {0x8};

axi_lite_info_t _p0_swinst_array_zero_copy_1_cmd_array_zero_copy_info = {
  .phys_base_addr = 0x83c00000,
  .data_reg_offset = _p0_swinst_array_zero_copy_1_cmd_array_zero_copy_sg_list,
  .data_reg_sg_size = 1,
  .write_status_reg_offset = 0x0,
  .read_status_reg_offset = 0x0,
  .config = XLNK_AXI_LITE_SG |
    XLNK_AXI_LITE_STAT_REG_READ(XLNK_AXI_LITE_STAT_REG_NOCHECK) |
    XLNK_AXI_LITE_STAT_REG_WRITE(XLNK_AXI_LITE_STAT_REG_NOCHECK),
  .acc_info = &_sds__p0_array_zero_copy_1,
};

zero_copy_info_t _p0_swinst_array_zero_copy_1_a_info = {
  .phys_base_addr = 0x83c00000,
  .data_reg_offset = 0xc,
  .status_reg_offset = 0x40c,
  .config = XLNK_AXI_LITE_KEYHOLE |
    XLNK_ZERO_COPY_STAT_REG_WRITE(XLNK_ZERO_COPY_STAT_REG_QUEUING),
  .is_coherent = 1,
  .dir = XLNK_BI_DIRECTIONAL,
  .acc_info = &_sds__p0_array_zero_copy_1,
};

zero_copy_info_t _p0_swinst_array_zero_copy_1_b_info = {
  .phys_base_addr = 0x83c00000,
  .data_reg_offset = 0x10,
  .status_reg_offset = 0x410,
  .config = XLNK_AXI_LITE_KEYHOLE |
    XLNK_ZERO_COPY_STAT_REG_WRITE(XLNK_ZERO_COPY_STAT_REG_QUEUING),
  .is_coherent = 1,
  .dir = XLNK_BI_DIRECTIONAL,
  .acc_info = &_sds__p0_array_zero_copy_1,
};

struct _p0_swblk_array_zero_copy _p0_swinst_array_zero_copy_1 = {
  .cmd_array_zero_copy = { .base = { .channel_info = &_p0_swinst_array_zero_copy_1_cmd_array_zero_copy_info}, 
    .send_i = &axi_lite_send },
  .a = { .base = { .channel_info = &_p0_swinst_array_zero_copy_1_a_info}, 
    .send_ref_i = &zero_copy_send_ref_i },
  .b = { .base = { .channel_info = &_p0_swinst_array_zero_copy_1_b_info}, 
    .send_ref_i = &zero_copy_send_ref_i },
};

void __attribute__((weak)) pfm_hook_init() {}
void __attribute__((weak)) pfm_hook_shutdown() {}
extern void pfm_hook_anchor();
void _p0_cf_framework_open(int first)
{
  int xlnk_init_done;
  cf_context_init();
  xlnkCounterMap();
  xlnk_init_done = cf_xlnk_open(first);
  if (!xlnk_init_done) {
    pfm_hook_init();
    cf_xlnk_init(first);
  } else if (xlnk_init_done < 0) {
    fprintf(stderr, "ERROR: unable to open xlnk\n");
    exit(-1);
  }
  cf_get_current_context();
  axi_lite_open(&_p0_swinst_array_zero_copy_1_cmd_array_zero_copy_info);
  _sds__p0_array_zero_copy_1.arg_dm_id[0] = _p0_swinst_array_zero_copy_1_cmd_array_zero_copy_info.dm_id;
  _sds__p0_array_zero_copy_1.arg_dm_id[1] = _p0_swinst_array_zero_copy_1_a_info.dm_id;
  _sds__p0_array_zero_copy_1.arg_dm_id[2] = _p0_swinst_array_zero_copy_1_b_info.dm_id;
  _sds__p0_array_zero_copy_1.arg_dm_id_count = 3;
  accel_open(&_sds__p0_array_zero_copy_1);
}

void _p0_cf_framework_close(int last)
{
  accel_close(&_sds__p0_array_zero_copy_1);
  axi_lite_close(&_p0_swinst_array_zero_copy_1_cmd_array_zero_copy_info);
  pfm_hook_shutdown();
  xlnkClose(last, NULL);
}

#define TOTAL_PARTITIONS 1
int current_partition_num = 0;
struct {
  void (*open)(int);
  void (*close)(int);
}

_ptable[TOTAL_PARTITIONS]  = {
    {.open = &_p0_cf_framework_open, .close= &_p0_cf_framework_close}, 
};

void switch_to_next_partition(int partition_num)
{
#ifdef __linux__
  if (current_partition_num != partition_num) {
    _ptable[current_partition_num].close(0);
    char buf[128];
    sprintf(buf, "cat /mnt/_sds/_p%d_.bin > /dev/xdevcfg", partition_num);
    system(buf);
    _ptable[partition_num].open(0);
    current_partition_num = partition_num;
  }
#endif
}

void init_first_partition() __attribute__ ((constructor));
void close_last_partition() __attribute__ ((destructor));
void init_first_partition()
{
    current_partition_num = 0;
    _ptable[current_partition_num].open(1);

    sds_trace_setup();
}


void close_last_partition()
{
#ifdef PERF_EST
    apf_perf_estimation_exit();
#endif
    sds_trace_cleanup();
    _ptable[current_partition_num].close(1);
    current_partition_num = 0;
}

