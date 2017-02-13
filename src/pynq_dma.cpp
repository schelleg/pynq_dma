/*
/*
 /* array_zero_copy.cpp
 *
 *  Created on: Jan 11, 2017
 *      Author: grahams
 */


/*
(c) Copyright 2013 - 2016 Xilinx, Inc. All rights reserved.

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

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#ifdef __SDSCC__
#include "sds_lib.h"
#else
#define sds_alloc(x)(malloc(x))
#define sds_free(x)(free(x))
#endif

#define N 1024*1024
#define NUM_ITERATIONS N

typedef short data_t;

#pragma SDS data zero_copy(a, b)
void array_zero_copy(data_t a[N], data_t b[N])
{
     for(int i = 0; i < N; i++) {
          b[i] = a[i];
     }
}

#include "cf_stub.h"
extern "C" void _p0_array_zero_copy_1_noasync(data_t a[1048576], data_t b[1048576]);
extern "C" void _p0_array_zero_copy_1_noasync(data_t a[1048576], data_t b[1048576])
{
  switch_to_next_partition(0);
  int start_seq[1];
  start_seq[0] = 0;
  cf_request_handle_t _p0_swinst_array_zero_copy_1_cmd;
  cf_send_i(&(_p0_swinst_array_zero_copy_1.cmd_array_zero_copy), start_seq, 1 * sizeof(int), &_p0_swinst_array_zero_copy_1_cmd);
  cf_wait(_p0_swinst_array_zero_copy_1_cmd);

  cf_send_ref_i(&(_p0_swinst_array_zero_copy_1.a), &a, 2097152, &_p0_request_0);
  cf_send_ref_i(&(_p0_swinst_array_zero_copy_1.b), &b, 2097152, &_p0_request_1);


  cf_wait(_p0_request_0);
  cf_wait(_p0_request_1);
}



void arraycopy_sw(data_t *a, data_t *b)
{
     for(int i = 0; i < N; i++) {
          b[i] = a[i];
     }
}

int print_results(data_t A[N], data_t swOut[N], data_t hwOut[N])
{
     int i;
     std::cout << "     A   : ";
     for (i = 0; i < N; i++)
          std::cout << A[i];
     std::cout << std::endl << "(sw) A_cpy: ";
     for (i = 0; i < N; i++)
          std::cout << swOut[i];
     std::cout << std::endl << "(hw) A_cpy: ";
     for (i = 0; i < N; i++)
          std::cout << hwOut[i];
     std::cout << std::endl;
     return 0;
}

int compare(data_t swOut[N], data_t hwOut[N])
{
     for (int i = 0; i < N; i++) {
          if (swOut[i] != hwOut[i]) {
               std::cout << "Values differ: swOut[" << i
                         << swOut[i] << "],  hwOut[" << i
                         << "] = " << hwOut[i] << std::endl;
               return -1;
          }
     }
     std::cout << "RESULTS MATCH" << std::endl << std::endl;
     return 0;
}

extern "C" void _p0_array_zero_copy_1_noasync(data_t a[1048576], data_t b[1048576]);
int main(int argc, char* argv[])
{
     data_t  Bs[N];
     data_t *A = (data_t*)sds_alloc(N * sizeof(data_t));
     data_t *B = (data_t*)sds_alloc(N * sizeof(data_t));
     int result = 0;
     for (int i = 1; !result && i < NUM_ITERATIONS; i++) {
          for (int j = 1; j < N; j++) {
               A[j]  = j;
               B[j] = 0;
               Bs[j] = 0;
          }
          arraycopy_sw(A, Bs);
          _p0_array_zero_copy_1_noasync(A, B);
          print_results(A, Bs, B);
          result = compare(Bs, B);
     }

     return result;
}




