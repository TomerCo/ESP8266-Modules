/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Tomer Cohen
 */

#ifndef ESP_HELPER_H_
#define ESP_HELPER_H_

#include "ets_sys.h"

#define LOW(p) (GPIO_OUTPUT_SET(p,0))
#define HIGH(p) (GPIO_OUTPUT_SET(p,1))

#define delay_ms(x)(os_delay_us(x*1000))

extern void ICACHE_FLASH_ATTR config_pins(int pin_mask);

#endif /* ESP_HELPER_H_ */
