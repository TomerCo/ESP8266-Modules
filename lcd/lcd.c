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
#include "string.h"
#include "stdlib.h"
#include "osapi.h"
#include "mem.h"

#include "lcd.h"

#define LCD_LOW(p) (LOW(lcd->data_pins[p]))
#define LCD_HIGH(p) (HIGH(lcd->data_pins[p]))


void ICACHE_FLASH_ATTR lcd_write(tESPLCDData * lcd,int d) {
	int i;

	for(i =0; i < 4; i++) {
		if(((d >> i) & 0x1) != 0) {
			LCD_HIGH(i);
		} else {
			LCD_LOW(i);
		}
	}
	LOW(lcd->en_pin);
	delay_ms(1);
	HIGH(lcd->en_pin);
	delay_ms(1);
	LOW(lcd->en_pin);
	delay_ms(1);
}

void ICACHE_FLASH_ATTR lcd_out(tESPLCDData *lcd, int d, int rs_val) {
	if(rs_val == 0) {
		LOW(lcd->rs_pin);
	} else {
		HIGH(lcd->rs_pin);
	}
	delay_ms(10);
	lcd_write(lcd,(d >> 4) & 0x0f);
	lcd_write(lcd,d & 0x0f);
}

#define lcd_command(d) (lcd_out(lcd,d,0))

tESPLCDData * ICACHE_FLASH_ATTR lcd_init(int en_pin, int rs_pin, int db4, int db5, int db6, int db7) {

	char hello[]="hello";
	int i;
	tESPLCDData *lcd = (tESPLCDData*)os_malloc(sizeof(tESPLCDData));
	lcd->en_pin = en_pin;
	lcd->rs_pin = rs_pin;
	lcd->data_pins[LCD_PIN_DB4] = db4;
	lcd->data_pins[LCD_PIN_DB5] = db5;
	lcd->data_pins[LCD_PIN_DB6] = db6;
	lcd->data_pins[LCD_PIN_DB7] = db7;


	config_pins((1<<2) | (1<<4) | (1<<5) | (1<<12) | (1<<13) | (1<<14));
	delay_ms(50);
	LOW(rs_pin);
	LOW(en_pin);
	lcd_write(lcd,0x3);
	delay_ms(5);
	lcd_write(lcd,3);
	delay_ms(5);
	lcd_write(lcd,0x3);
	delay_ms(1); //101ms
	lcd_write(lcd,0x2);
//	delay_ms(101);
	lcd_command(0x28);
	lcd_command(0xC);
	lcd_command(0x1);
	delay_ms(2);
	lcd_command(0x6);
	return lcd;

}

void ICACHE_FLASH_ATTR lcd_print(tESPLCDData *lcd, char *str) {
	int i;
	for(i=0; i < strlen(str);i++) {
		lcd_out(lcd,str[i],1);
		delay_ms(10);

	}
}
