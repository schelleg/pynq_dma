/*
© Copyright 2013 - 2016 Xilinx, Inc. All rights reserved. 

This file contains confidential and proprietary information of Xilinx, Inc. and
is protected under U.S. and international copyright and other intellectual
property laws.

DISCLAIMER 
This disclaimer is not a license and does not grant any rights to the materials
distributed herewith. Except as otherwise provided in a valid license issued to
you by Xilinx, and to the maximum extent permitted by applicable law: (1) THESE
MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL FAULTS, AND XILINX HEREBY
DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY,
INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT, OR
FITNESS FOR ANY PARTICULAR PURPOSE; and (2) Xilinx shall not be liable (whether
in contract or tort, including negligence, or under any other theory of
liability) for any loss or damage of any kind or nature related to, arising
under or in connection with these materials, including for any direct, or any
indirect, special, incidental, or consequential loss or damage (including loss
of data, profits, goodwill, or any type of loss or damage suffered as a result
of any action brought by a third party) even if such damage or loss was
reasonably foreseeable or Xilinx had been advised of the possibility of the
same.

CRITICAL APPLICATIONS
Xilinx products are not designed or intended to be fail-safe, or for use in any
application requiring fail-safe performance, such as life-support or safety
devices or systems, Class III medical devices, nuclear facilities, applications
related to the deployment of airbags, or any other applications that could lead
to death, personal injury, or severe property or environmental damage
(individually and collectively, "Critical Applications"). Customer assumes the
sole risk and liability of any use of Xilinx products in Critical Applications,
subject only to applicable laws and regulations governing limitations on product
liability.

THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE AT
ALL TIMES. 
*/

#ifndef APF_PERF_INSTRUMENTATION_H
#define APF_PERF_INSTRUMENTATION_H

#ifdef __cplusplus
extern "C" {
#endif

struct sw_function_perf_info_struct {
	unsigned long long cycleCount;
	unsigned int entryCount;
	int isRoot;
	char *function_name;
};

typedef struct sw_function_perf_info_struct sw_function_perf_info_t;

struct hw_cluster_perf_info_struct {
	unsigned int latency;
	unsigned int dsp;
	unsigned int bram;
	unsigned int lut;
	unsigned int num_functions;
	unsigned int sw_latency;
	char *function_names[];
};

typedef struct hw_cluster_perf_info_struct hw_cluster_perf_info_t;

struct resources_struct {
	unsigned int dsp;
	unsigned int bram;
	unsigned int lut;
};

typedef struct resources_struct resources_t;

void add_sw_perf_function(sw_function_perf_info_t *sw_function);
void add_hw_perf_cluster(hw_cluster_perf_info_t *hw_cluster);
void apf_perf_estimation_exit(void);
void add_sw_estimates(void);//implementation generated by tools and linked in later
void add_hw_estimates(void);//implementation generated by tools and linked in later
void apf_perf_gen_report(void);

#ifdef __cplusplus
};
#endif

#endif

// XSIP watermark, do not delete 67d7842dbbe25473c3c32b93c0da8047785f30d78e8a024de1b57352245f9689