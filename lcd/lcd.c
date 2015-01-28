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

#define LCD_COMMAND_CLEAR 0x1
#define LCD_COMMAND_HOME 0x2
#define LCD_MODESET 0x04
#define LCD_COMMAND_DISPLAY 0x8

#define LCD_COMMAND_CURSORSHIFT 0x10

#define LCD_AUTOSCROLL 0x01
#define LCD_L2R 0x2


#define LCD_BLINK_ON 0x1
#define LCD_CURSOR_ON 0x2
#define LCD_DISPLAY_ON 0x4


#define LCD_DISPLAYMOVE 0x08
#define LCD_MOVERIGHT 0x04

#define LCD_CREATE_CHAR 0x40

int cur_lcd_display = 0;
int cur_lcd_mode = 0;

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



#define LCD_CMD(NAME,CMD) \
	void ICACHE_FLASH_ATTR lcd_##NAME(tESPLCDData *lcd) {\
		lcd_command(CMD); \
	}

#define LCD_DISPLAY_TOGGLE(NAME,NOB) \
		void ICACHE_FLASH_ATTR lcd_##NAME##_on(tESPLCDData *lcd) {\
				cur_lcd_display |= NOB; \
				lcd_command(LCD_COMMAND_DISPLAY | cur_lcd_display); \
			} \
		void ICACHE_FLASH_ATTR lcd_##NAME##_off(tESPLCDData *lcd) {\
				cur_lcd_display &= ~NOB; \
				lcd_command(LCD_COMMAND_DISPLAY | cur_lcd_display); \
		}

LCD_CMD(clear,LCD_COMMAND_CLEAR);
LCD_CMD(home,LCD_COMMAND_HOME);

LCD_DISPLAY_TOGGLE(display,LCD_DISPLAY_ON);
LCD_DISPLAY_TOGGLE(cursor,LCD_CURSOR_ON);
LCD_DISPLAY_TOGGLE(blink,LCD_BLINK_ON);



void ICACHE_FLASH_ATTR lcd_scroll_left(tESPLCDData *lcd) {
	lcd_command(LCD_COMMAND_CURSORSHIFT | LCD_DISPLAYMOVE);
}
void ICACHE_FLASH_ATTR lcd_scroll_right(tESPLCDData *lcd) {
	lcd_command(LCD_COMMAND_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

#define LCD_MODE_TOGGLE(NAMEON,NAMEOFF,NOB) \
		void ICACHE_FLASH_ATTR lcd_##NAMEON(tESPLCDData *lcd) {\
				cur_lcd_mode |= NOB; \
				lcd_command(LCD_MODESET | cur_lcd_mode); \
			} \
		void ICACHE_FLASH_ATTR lcd_##NAMEOFF(tESPLCDData *lcd) {\
				cur_lcd_mode &= ~NOB; \
				lcd_command(LCD_MODESET | cur_lcd_mode); \
		}

LCD_MODE_TOGGLE(l2r,r2l,LCD_L2R);
LCD_MODE_TOGGLE(autoscroll_on,autoscroll_off,LCD_AUTOSCROLL);


void ICACHE_FLASH_ATTR lcd_create_char(tESPLCDData *lcd, uint8_t location, uint8_t charmap[]) {
  location %= 8;
  int i;
  lcd_command(LCD_CREATE_CHAR | (location << 3));
  for (i=0; i<8; i++) {
    lcd_write(lcd,charmap[i]);
  }
}
