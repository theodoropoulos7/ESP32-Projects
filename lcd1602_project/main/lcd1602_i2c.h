// lcd1602_i2c.h
#pragma once

#include "driver/i2c.h"

void lcd1602_init(i2c_port_t i2c_num, uint8_t lcd_addr);
void lcd1602_clear();
void lcd1602_set_cursor(uint8_t col, uint8_t row);
void lcd1602_write_char(char c);
void lcd1602_write_string(const char *str);
