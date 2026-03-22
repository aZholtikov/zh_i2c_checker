#include "driver/i2c_master.h"
#include "freertos/FreeRTOS.h"

#define I2C_PORT (I2C_NUM_MAX - 1)

void app_main(void)
{
    i2c_master_bus_config_t i2c_bus_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_PORT,
        .scl_io_num = GPIO_NUM_22,
        .sda_io_num = GPIO_NUM_21,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    i2c_master_bus_handle_t i2c_bus_handle;
    i2c_new_master_bus(&i2c_bus_config, &i2c_bus_handle);
    for (uint8_t i = 0; i <= 127; ++i)
    {
        if (i2c_master_probe(i2c_bus_handle, i, 1000 / portTICK_PERIOD_MS) == ESP_OK)
        {
            printf("Address 0x%02X\n", i);
        }
    }
}