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



#ifndef LCD_H_
#define LCD_H_

#include "ets_sys.h"
#include "gpio.h"

#define LCD_PIN_DB4 0
#define LCD_PIN_DB5 1
#define LCD_PIN_DB6 2
#define LCD_PIN_DB7 3


typedef struct {
	int data_pins[4];
	int en_pin;
	int rs_pin;
}tESPLCDData;


extern  tESPLCDData * ICACHE_FLASH_ATTR lcd_init(int en_pin, int rs_pin, int db4, int db5, int db6, int db7);

extern void ICACHE_FLASH_ATTR lcd_print(tESPLCDData *lcd, char *str);
extern void ICACHE_FLASH_ATTR lcd_clear(tESPLCDData *lcd);
extern void ICACHE_FLASH_ATTR lcd_home(tESPLCDData *lcd);
extern void ICACHE_FLASH_ATTR lcd_display_on(tESPLCDData *lcd);
extern void ICACHE_FLASH_ATTR lcd_display_off(tESPLCDData *lcd);
extern void ICACHE_FLASH_ATTR lcd_cursor_on(tESPLCDData *lcd);
extern void ICACHE_FLASH_ATTR lcd_cursor_off(tESPLCDData *lcd);
extern void ICACHE_FLASH_ATTR lcd_blink_on(tESPLCDData *lcd);
extern void ICACHE_FLASH_ATTR lcd_blink_off(tESPLCDData *lcd);
extern void ICACHE_FLASH_ATTR lcd_scroll_left(tESPLCDData *lcd);
extern void ICACHE_FLASH_ATTR lcd_scroll_right(tESPLCDData *lcd);
extern void ICACHE_FLASH_ATTR lcd_l2r(tESPLCDData *lcd);
extern void ICACHE_FLASH_ATTR lcd_r2l(tESPLCDData *lcd);
extern void ICACHE_FLASH_ATTR lcd_autoscroll_on(tESPLCDData *lcd);
extern void ICACHE_FLASH_ATTR lcd_autoscroll_off(tESPLCDData *lcd);
extern void ICACHE_FLASH_ATTR lcd_create_char(tESPLCDData *lcd,unsigned char loc, unsigned char *map);



#endif /* LCD_H_ */
