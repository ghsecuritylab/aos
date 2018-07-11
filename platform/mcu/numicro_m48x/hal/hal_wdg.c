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
 * This function will initialize the on board CPU hardware watch dog
 *
 * @param[in]  wdg  the watch dog device
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_wdg_init(wdg_dev_t *wdg)
{
	return HAL_OK;
}

/**
 * Reload watchdog counter.
 *
 * @param[in]  wdg  the watch dog device
 */
void hal_wdg_reload(wdg_dev_t *wdg)
{
	return HAL_OK;
}

/**
 * This function performs any platform-specific cleanup needed for hardware watch dog.
 *
 * @param[in]  wdg  the watch dog device
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t hal_wdg_finalize(wdg_dev_t *wdg)
{
	return HAL_OK;
}
