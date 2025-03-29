// lcd1602_i2c.c
#include "lcd1602_i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LCD_BACKLIGHT  0x08
#define ENABLE         0x04
#define CMD_MODE       0x00
#define DATA_MODE      0x01

static i2c_port_t g_i2c_port;
static uint8_t g_lcd_addr;

static void i2c_write_byte(uint8_t data) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (g_lcd_addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, data | LCD_BACKLIGHT, true);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(g_i2c_port, cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(cmd);
}

static void lcd_send_nibble(uint8_t nibble, uint8_t mode) {
    uint8_t data = (nibble & 0xF0) | LCD_BACKLIGHT | mode;
    i2c_write_byte(data);
    i2c_write_byte(data | ENABLE);
    vTaskDelay(pdMS_TO_TICKS(1));
    i2c_write_byte(data & ~ENABLE);
}

static void lcd_send_byte(uint8_t byte, uint8_t mode) {
    lcd_send_nibble(byte & 0xF0, mode);
    lcd_send_nibble((byte << 4) & 0xF0, mode);
}

void lcd1602_init(i2c_port_t i2c_num, uint8_t lcd_addr) {
    g_i2c_port = i2c_num;
    g_lcd_addr = lcd_addr;

    vTaskDelay(pdMS_TO_TICKS(50));

    lcd_send_nibble(0x30, CMD_MODE);
    vTaskDelay(pdMS_TO_TICKS(5));
    lcd_send_nibble(0x30, CMD_MODE);
    vTaskDelay(pdMS_TO_TICKS(1));
    lcd_send_nibble(0x30, CMD_MODE);
    vTaskDelay(pdMS_TO_TICKS(1));
    lcd_send_nibble(0x20, CMD_MODE); // 4-bit mode

    lcd_send_byte(0x28, CMD_MODE); // 2 line, 5x8 dots
    lcd_send_byte(0x08, CMD_MODE); // display off
    lcd_send_byte(0x01, CMD_MODE); // clear display
    vTaskDelay(pdMS_TO_TICKS(2));
    lcd_send_byte(0x06, CMD_MODE); // entry mode
    lcd_send_byte(0x0C, CMD_MODE); // display on, cursor off
}

void lcd1602_clear() {
    lcd_send_byte(0x01, CMD_MODE);
    vTaskDelay(pdMS_TO_TICKS(2));
}

void lcd1602_set_cursor(uint8_t col, uint8_t row) {
    static const uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    lcd_send_byte(0x80 | (col + row_offsets[row]), CMD_MODE);
}

void lcd1602_write_char(char c) {
    lcd_send_byte((uint8_t)c, DATA_MODE);
}

void lcd1602_write_string(const char *str) {
    while (*str) {
        lcd1602_write_char(*str++);
    }
}
