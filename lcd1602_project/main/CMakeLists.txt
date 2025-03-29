# Use this if you want to use the LCD1602 display with I2C
idf_component_register(SRCS "main.c" "lcd1602_i2c.c" INCLUDE_DIRS ".")

# Uncomment this and rebuild If you want to scan the I2C bus
# idf_component_register(SRCS "i2c_scanner.c" INCLUDE_DIRS ".")
