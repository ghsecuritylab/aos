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
 * Initialises a sd interface
 *
 * @param[in]  sd  the interface which should be initialised
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_sd_init(sd_dev_t *sd)
{
	return HAL_OK;
}

/**
 * Read sd blocks
 *
 * @param[in]   sd        the interface which should be initialised
 * @param[out]  data      pointer to the buffer which will store incoming data
 * @param[in]   blk_addr  sd blk addr
 * @param[in]   blks      sd blks
 * @param[in]   timeout   timeout in milisecond
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_sd_blks_read(sd_dev_t *sd, uint8_t *data, uint32_t blk_addr,
                         uint32_t blks, uint32_t timeout)
{
	return HAL_OK;
}


/**
 * Write sd blocks
 *
 * @param[in]  sd        the interface which should be initialised
 * @param[in]  data      pointer to the buffer which will store incoming data
 * @param[in]  blk_addr  sd blk addr
 * @param[in]  blks      sd blks
 * @param[in]  timeout   timeout in milisecond
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_sd_blks_write(sd_dev_t *sd, uint8_t *data, uint32_t blk_addr,
                          uint32_t blks, uint32_t timeout)
{
	return HAL_OK;
}

/**
 * Erase sd blocks
 *
 * @param[in]  sd              the interface which should be initialised
 * @param[in]  blk_start_addr  sd blocks start addr
 * @param[in]  blk_end_addr    sd blocks end addr
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_sd_erase(sd_dev_t *sd, uint32_t blk_start_addr, uint32_t blk_end_addr)
{
	return HAL_OK;
}

/**
 * Get sd state
 *
 * @param[in]   sd    the interface which should be initialised
 * @param[out]  stat  pointer to the buffer which will store incoming data
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_sd_stat_get(sd_dev_t *sd, hal_sd_stat *stat)
{
	return HAL_OK;
}

/**
 * Get sd info
 *
 * @param[in]   sd    the interface which should be initialised
 * @param[out]  stat  pointer to the buffer which will store incoming data
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_sd_info_get(sd_dev_t *sd, hal_sd_info_t *info)
{
	return HAL_OK;
}

/**
 * Deinitialises a sd interface
 *
 * @param[in]  sd  the interface which should be initialised
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_sd_finalize(sd_dev_t *sd)
{
	return HAL_OK;
}

