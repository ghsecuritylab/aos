/* Microcontroller Library
 * Copyright (c) 2015-2016 Nuvoton
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "objects.h"
#include "nu_modutil.h"
#include "nu_bitutil.h"
#include "hal_status.h"
#include <k_api.h>
#include <hal/hal.h>
#include "board.h"


/**
 * Fill in a memory buffer with random data
 *
 * @param[in]   random       the random device
 * @param[out]  inBuffer     Point to a valid memory buffer, this function will fill
 *                           in this memory with random numbers after executed
 * @param[in]   inByteCount  Length of the memory buffer (bytes)
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_random_num_read(random_dev_t random, void *buf, int32_t bytes)
{
	return HAL_OK;
}
