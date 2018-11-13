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

#include "int_roots.h"

unsigned int int_sqrt(unsigned int squared) {
	static const unsigned int D[5] = {0, 268435456, 1073741824, 2415919104U, 4294967295U};
	static const unsigned int d[5] = {0, 16384, 32768, 49152, 65536};
	unsigned int P = 8192;
	unsigned int R = 67108864;
	unsigned int A = 0, a = 0, C = 0, c = 0, B = 0, b = 0, K = 0;

	B = squared;
	if( B >= D[4] ) {
		b = d[4];
		goto finish;
	}
	else if( B >= D[3] ) {
		if( B == D[3] ) {
			b = d[3];
			goto finish;
		}
		A = D[3];
		a = d[3];
		C = D[4];
		c = d[4];
	}
        else if( B >= D[2] ) {
                if( B == D[2] ) {
                        b = d[2];
                        goto finish;
                }
                A = D[2];
                a = d[2];
                C = D[3];
                c = d[3];
        }
        else if( B >= D[1] ) {
                if( B == D[1] ) {
                        b = d[1];
                        goto finish;
                }
                A = D[1];
                a = d[1];
                C = D[2];
                c = d[2];
        }
        else if( B >= D[0] ) {
                if( B == D[0] ) {
                        b = d[0];
                        goto finish;
                }
                A = D[0];
                a = d[0];
                C = D[1];
                c = d[1];
        }
	else {
		// psh_err2(PSH_ITSELF, "Number given error! Number: %d\n", squared);
		return -1;
	}

	while(1) {
		b = a + P;
		B = C - (C - A) / 2 - R;

		if(B == squared) {
			goto finish;
		}
		else if(B < squared) {
			A = B;
			a = b;
		}
		else {
			C = B;
			c = b;
		}

		if(c-a == 2) {
			/* Now c = a + 2.
			 * If squared > (a+1)*(a+2) , b = a+2 ;
			 * If squared <= a*(a+1), b = a ;
			 * Else b = a+1.
			 */
			K=(C - A)/4;

			if(squared >= C - K) {
				b = c;
			}
			else if(squared < A + K) {
				b = a;
			}
			else {
				b = a + 1;
			}
			goto finish;
		}
		P /= 2;
		R /= 4;
	}

finish:
	return b;
}

uint32_t int_cbrt(uint64_t cubic)
{
        uint64_t left = cubic;
        uint64_t root = 1;
        int i, digits = 0;

        if (left == 0)
                return 0;

        while (left != 0) {
                digits++;
                left >>= 3;
        }

        /* Original algorithm is from "Nine Chapters on Arithmetic".
         * The improved algorithm is modify Decimal to Binary.
         */
        for (i = 1; i < digits; i++) {
                left = cubic >> ((digits - 1 - i) * 3);
                left -= (root << 1) * (root << 1) * (root << 1);
                if (left > (12 * root * root + 6 * root))
                        root = (root << 1) + 1;
                else
                        root <<= 1;
        }

        return root;
}
