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
 * Initialises an dac interface
 *
 * @param[in]  dac  the interface which should be initialised
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_dac_init(dac_dev_t *dac)
{
	return HAL_OK;
}

/**
 * Start output dac
 *
 * @param[in]   dac      the interface which should be started
 * @param[out]  channel  the channel to output dac
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_dac_start(dac_dev_t *dac, uint32_t channel)
{
	return HAL_OK;
}

/**
 * Stop output dac
 *
 * @param[in]   dac      the interface which should be stopped
 * @param[out]  channel  the channel to output dac
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_dac_stop(dac_dev_t *dac, uint32_t channel)
{
	return HAL_OK;
}

/**
 * Output a value to an dac interface
 *
 * @param[in]   dac      the interface to set value
 * @param[out]  channel  the channel to output dac
 * @param[in]   data     the value to output
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_dac_set_value(dac_dev_t *dac, uint32_t channel, uint32_t data)
{
	return HAL_OK;
}

/**
 * Returns the last data output value of the selected dac channel
 *
 * @param[in]   dac      the interface to get value
 * @param[out]  channel  channel  the channel to output dac
 *
 * @return  dac output value
 */
int32_t hal_dac_get_value(dac_dev_t *dac, uint32_t channel)
{
	return HAL_OK;
}

/**
 * De-initialises an dac interface, Turns off an dac hardware interface
 *
 * @param[in]  dac  the interface which should be de-initialised
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_dac_finalize(dac_dev_t *dac)
{
	return HAL_OK;
}
