/*-------------------------------------------------------------------------
 * INTEL CONFIDENTIAL
 *
 * Copyright 2012 Intel Corporation All Rights Reserved.
 *
 * This source code and all documentation related to the source code
 * ("Material") contains trade secrets and proprietary and confidential
 * information of Intel and its suppliers and licensors. The Material is
 * deemed highly confidential, and is protected by worldwide copyright and
 * trade secret laws and treaty provisions. No part of the Material may be
 * used, copied, reproduced, modified, published, uploaded, posted,
 * transmitted, distributed, or disclosed in any way without Intel's prior
 * express written permission.
 *
 * No license under any patent, copyright, trade secret or other
 * intellectual property right is granted to or conferred upon you by
 * disclosure or delivery of the Materials, either expressly, by
 * implication, inducement, estoppel or otherwise. Any license under such
 * intellectual property rights must be express and approved by Intel in
 * writing.
 *-------------------------------------------------------------------------
 */
/*
 * Version: 1.1
 * Author: Han, He <he.han@intel.com>
 * Date: Jun 11th, 2012
 * Update: Nov 27th, 2013 : Add cubic root function
 */

#ifndef _INT_ROOTS_H_
#define _INT_ROOTS_H_

#include "sfloat_common.h"

unsigned int int_sqrt(unsigned int squared);
uint32_t int_cbrt(uint64_t cubic);

#endif
