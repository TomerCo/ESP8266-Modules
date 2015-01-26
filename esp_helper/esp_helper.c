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

#include "esp_helper.h"


int gpio_to_func[] = {FUNC_GPIO0,FUNC_GPIO1,FUNC_GPIO2,FUNC_GPIO3,FUNC_GPIO4,FUNC_GPIO5,0,
		0,0,FUNC_GPIO9,FUNC_GPIO10,0,FUNC_GPIO12,FUNC_GPIO13,FUNC_GPIO14,FUNC_GPIO15};

int gpio_to_name[] = {PERIPHS_IO_MUX_GPIO0_U,-1,PERIPHS_IO_MUX_GPIO2_U,-1,PERIPHS_IO_MUX_GPIO4_U,
		PERIPHS_IO_MUX_GPIO5_U,-1,-1,-1,-1,-1,-1,PERIPHS_IO_MUX_MTDI_U,PERIPHS_IO_MUX_MTCK_U,PERIPHS_IO_MUX_MTMS_U,
		PERIPHS_IO_MUX_MTDO_U};


void ICACHE_FLASH_ATTR config_pins(int pin_mask) {

	int i;
	for(i = 0; i <16;i++) {
		if(pin_mask & ( 1 << i)) {
			if(gpio_to_name[i] != -1) {
				PIN_FUNC_SELECT(gpio_to_name[i],gpio_to_func[i]);
			}
		}
	}

}
