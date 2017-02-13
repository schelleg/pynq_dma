#ifndef _SDS_PORTINFO_H
#define _SDS_PORTINFO_H
/* File: /group/xrlabs2/grahams/SDSoC/pynq_sdx20163/sdsoc_workspace/pynq_dma/Debug/_sds/p0/.cf_work/portinfo.h */
#ifdef __cplusplus
extern "C" {
#endif

struct _p0_swblk_array_zero_copy {
  cf_port_send_t cmd_array_zero_copy;
  cf_port_send_t a;
  cf_port_send_t b;
};

extern struct _p0_swblk_array_zero_copy _p0_swinst_array_zero_copy_1;
void _p0_cf_framework_open(int);
void _p0_cf_framework_close(int);

#ifdef __cplusplus
};
#endif
#ifdef __cplusplus
extern "C" {
#endif
void switch_to_next_partition(int);
void init_first_partition();
void close_last_partition();
#ifdef __cplusplus
};
#endif /* extern "C" */
#endif /* _SDS_PORTINFO_H_ */
