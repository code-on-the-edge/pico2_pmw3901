#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

// SPI Defines
#define SPI_PORT spi0

#define PIN_SCK  2
#define PIN_MOSI 3
#define PIN_MISO 4
#define PIN_CS   5

static inline void pmw3901_select() {
    gpio_put(PIN_CS, 0);
}

static inline void pmw3901_deselect() {
    gpio_put(PIN_CS, 1);
}

uint8_t pmw3901_read_reg(uint8_t reg)
{
    // Bitcraze driver uses MSB = 0 for read
    reg &= 0x7F;
    uint8_t rx = 0;

    pmw3901_select();
    sleep_us(50);

    spi_write_blocking(SPI_PORT, &reg, 1);

    sleep_us(50);

    spi_read_blocking(SPI_PORT, 0x00, &rx, 1);

    sleep_us(100);
    pmw3901_deselect();

    sleep_us(200);
    return rx;
}

void pmw3901_write_reg(uint8_t reg, uint8_t value)
{
    // Bitcraze driver uses MSB = 1 for write
    reg |= 0x80;
    uint8_t tx[2] = { reg, value };

    pmw3901_select();
    sleep_us(50);

    spi_write_blocking(SPI_PORT, tx, 2);

    sleep_us(50);
    pmw3901_deselect();

    sleep_us(200);
}

void pmw3901_init()
{
    // Power-on reset command
    pmw3901_write_reg(0x3A, 0x5A);
    sleep_ms(5);

    // Clear motion registers once
    (void)pmw3901_read_reg(0x02);
    (void)pmw3901_read_reg(0x03);
    (void)pmw3901_read_reg(0x04);
    (void)pmw3901_read_reg(0x05);
    (void)pmw3901_read_reg(0x06);
    sleep_ms(1);

    // Full Bitcraze init sequence
    pmw3901_write_reg(0x7F, 0x00);
    pmw3901_write_reg(0x61, 0xAD);
    pmw3901_write_reg(0x7F, 0x03);
    pmw3901_write_reg(0x40, 0x00);
    pmw3901_write_reg(0x7F, 0x05);
    pmw3901_write_reg(0x41, 0xB3);
    pmw3901_write_reg(0x43, 0xF1);
    pmw3901_write_reg(0x45, 0x14);
    pmw3901_write_reg(0x5B, 0x32);
    pmw3901_write_reg(0x5F, 0x34);
    pmw3901_write_reg(0x7B, 0x08);
    pmw3901_write_reg(0x7F, 0x06);
    pmw3901_write_reg(0x44, 0x1B);
    pmw3901_write_reg(0x40, 0xBF);
    pmw3901_write_reg(0x4E, 0x3F);
    pmw3901_write_reg(0x7F, 0x08);
    pmw3901_write_reg(0x65, 0x20);
    pmw3901_write_reg(0x6A, 0x18);
    pmw3901_write_reg(0x7F, 0x09);
    pmw3901_write_reg(0x4F, 0xAF);
    pmw3901_write_reg(0x5F, 0x40);
    pmw3901_write_reg(0x48, 0x80);
    pmw3901_write_reg(0x49, 0x80);
    pmw3901_write_reg(0x57, 0x77);
    pmw3901_write_reg(0x60, 0x78);
    pmw3901_write_reg(0x61, 0x78);
    pmw3901_write_reg(0x62, 0x08);
    pmw3901_write_reg(0x63, 0x50);
    pmw3901_write_reg(0x7F, 0x0A);
    pmw3901_write_reg(0x45, 0x60);
    pmw3901_write_reg(0x7F, 0x00);
    pmw3901_write_reg(0x4D, 0x11);
    pmw3901_write_reg(0x55, 0x80);
    pmw3901_write_reg(0x74, 0x1F);
    pmw3901_write_reg(0x75, 0x1F);
    pmw3901_write_reg(0x4A, 0x78);
    pmw3901_write_reg(0x4B, 0x78);
    pmw3901_write_reg(0x44, 0x08);
    pmw3901_write_reg(0x45, 0x50);
    pmw3901_write_reg(0x64, 0xFF);
    pmw3901_write_reg(0x65, 0x1F);
    pmw3901_write_reg(0x7F, 0x14);
    pmw3901_write_reg(0x65, 0x60);
    pmw3901_write_reg(0x66, 0x08);
    pmw3901_write_reg(0x63, 0x78);
    pmw3901_write_reg(0x7F, 0x15);
    pmw3901_write_reg(0x48, 0x58);
    pmw3901_write_reg(0x7F, 0x07);
    pmw3901_write_reg(0x41, 0x0D);
    pmw3901_write_reg(0x43, 0x14);
    pmw3901_write_reg(0x4B, 0x0E);
    pmw3901_write_reg(0x45, 0x0F);
    pmw3901_write_reg(0x44, 0x42);
    pmw3901_write_reg(0x4C, 0x80);
    pmw3901_write_reg(0x7F, 0x10);
    pmw3901_write_reg(0x5B, 0x02);
    pmw3901_write_reg(0x7F, 0x07);
    pmw3901_write_reg(0x40, 0x41);
    pmw3901_write_reg(0x70, 0x00);

    sleep_ms(100);

    pmw3901_write_reg(0x32, 0x44);
    pmw3901_write_reg(0x7F, 0x07);
    pmw3901_write_reg(0x40, 0x40);
    pmw3901_write_reg(0x7F, 0x06);
    pmw3901_write_reg(0x62, 0xF0);
    pmw3901_write_reg(0x63, 0x00);
    pmw3901_write_reg(0x7F, 0x0D);
    pmw3901_write_reg(0x48, 0xC0);
    pmw3901_write_reg(0x6F, 0xD5);
    pmw3901_write_reg(0x7F, 0x00);
    pmw3901_write_reg(0x5B, 0xA0);
    pmw3901_write_reg(0x4E, 0xA8);
    pmw3901_write_reg(0x5A, 0x50);
    pmw3901_write_reg(0x40, 0x80);
}

void pmw3901_read_delta(int16_t *dx, int16_t *dy)
{
    (void)pmw3901_read_reg(0x02);  // motion register first

    uint8_t xl = pmw3901_read_reg(0x03);
    uint8_t xh = pmw3901_read_reg(0x04);
    uint8_t yl = pmw3901_read_reg(0x05);
    uint8_t yh = pmw3901_read_reg(0x06);

    *dx = (int16_t)(((uint16_t)xh << 8) | xl);
    *dy = (int16_t)(((uint16_t)yh << 8) | yl);
}

int main()
{
    stdio_init_all();
    sleep_ms(2000);

    // 1 MHz SPI
    spi_init(SPI_PORT, 1000 * 1000);

    // PMW3901 working driver uses MODE3
    spi_set_format(SPI_PORT,
                   8,
                   SPI_CPOL_1,
                   SPI_CPHA_1,
                   SPI_MSB_FIRST);

    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);

    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);

    // Reset SPI bus like Bitcraze does
    pmw3901_deselect();
    sleep_ms(1);
    pmw3901_select();
    sleep_ms(1);
    pmw3901_deselect();
    sleep_ms(1);

    sleep_ms(50);

    pmw3901_init();

    while (true) {
        uint8_t pid = pmw3901_read_reg(0x00);
        uint8_t inv = pmw3901_read_reg(0x5F);

        int16_t dx = 0;
        int16_t dy = 0;
        pmw3901_read_delta(&dx, &dy);

        printf("Product ID: 0x%02X | Inverse ID: 0x%02X | dx: %d, dy: %d\n",
               pid, inv, dx, dy);

        sleep_ms(200);
    }
}