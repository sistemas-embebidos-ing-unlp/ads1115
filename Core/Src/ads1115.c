/*
 * ads1115.c
 *
 *  Created on: Apr 13, 2024
 *      Author: paloma
 */
#include "main.h"
#include "ads1115.h"
uint8_t ADS1115_POINTER_CONFIGURATION = 0x01;
uint8_t ADS1115_POINTER_CONVERSION = 0x00;

void ads1115_init(uint8_t i2c_addr, I2C_HandleTypeDef *hi2c, ads1115_adc_t *adc){
	adc->hi2c = hi2c;
    adc->i2c_addr = i2c_addr;
    ads1115_read_config(adc);
}

void ads1115_read_config(ads1115_adc_t *adc){
    uint8_t dst[2];
    HAL_I2C_Master_Transmit(adc->hi2c, adc->i2c_addr << 1, &ADS1115_POINTER_CONFIGURATION, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(adc->hi2c, adc->i2c_addr << 1, dst, 2, HAL_MAX_DELAY);
    adc->config = (dst[0] << 8) | dst[1];
}

void ads1115_write_config(ads1115_adc_t *adc) {
    uint8_t src[3];
    src[0] = ADS1115_POINTER_CONFIGURATION;
    src[1] = (uint8_t)(adc->config >> 8);
    src[2] = (uint8_t)(adc->config & 0xff);
    HAL_I2C_Master_Transmit(adc->hi2c, adc->i2c_addr << 1, src, 3, HAL_MAX_DELAY);
}

void ads1115_read_adc(int16_t *adc_value, ads1115_adc_t *adc){
    // If mode is single-shot, set bit 15 to start the conversion.
	ads1115_read_config(adc);
    if ((adc->config & ADS1115_MODE_MASK) == ADS1115_MODE_SINGLE_SHOT) {
        adc->config |= 0x8000;//ADS1115_STATUS_START;
        ads1115_write_config(adc);


        // Wait until the conversion finishes before reading the value
        ads1115_read_config(adc);
        while ((adc->config & ADS1115_STATUS_MASK) == ADS1115_STATUS_BUSY){
            ads1115_read_config(adc);
        }
    }
    HAL_Delay(100);

    // Now read the value from last conversion
    uint8_t dst[2];

    HAL_I2C_Master_Transmit(adc->hi2c, adc->i2c_addr << 1, &ADS1115_POINTER_CONVERSION, 1, HAL_MAX_DELAY);

    HAL_I2C_Master_Receive(adc->hi2c, adc->i2c_addr << 1, dst, 2, HAL_MAX_DELAY);

    *adc_value = (dst[0] << 8) | dst[1];
}

float ads1115_conv_volts(int16_t valor_adc, ads1115_adc_t *adc){
    float fsr;
    uint16_t pga = adc->config & ADS1115_PGA_MASK;
    switch (pga) {
        case ADS1115_PGA_6_144:
            fsr = 6.144;
            break;
        case ADS1115_PGA_4_096:
            fsr = 4.096;
            break;
        case ADS1115_PGA_2_048:
            fsr = 2.048;
            break;
        case ADS1115_PGA_1_024:
            fsr = 1.024;
            break;
        case ADS1115_PGA_0_512:
            fsr = 0.512;
            break;
        case ADS1115_PGA_0_256:
            fsr = 0.256;
            break;
    }

    float voltaje;
    voltaje = (float)valor_adc* fsr /32767;

    return voltaje;
}

void ads1115_set_mux(enum ads1115_mux_t mux, ads1115_adc_t *adc){
	adc->config &= ~ADS1115_MUX_MASK;
	adc->config |= mux;

	ads1115_write_config(adc);
}

void ads1115_set_pga(enum ads1115_pga_t pga, ads1115_adc_t *adc){
	adc->config &= ~ADS1115_PGA_MASK;
	adc->config |= pga;

	ads1115_write_config(adc);
}

void ads1115_set_mode(enum ads1115_mode_t mode, ads1115_adc_t *adc){
	adc->config &= ~ADS1115_MODE_MASK;
	adc->config |= mode;

	ads1115_write_config(adc);
}

void ads1115_set_rate(enum ads1115_rate_t rate, ads1115_adc_t *adc){
	adc->config &= ~ADS1115_RATE_MASK;
	adc->config |= rate;

	ads1115_write_config(adc);
}

void ads1115_set_comp_mode(enum ads1115_comp_mode_t comp, ads1115_adc_t *adc){
	adc->config &= ~ADS1115_COMP_MODE_MASK;
	adc->config |= comp;

	ads1115_write_config(adc);
}

void ads1115_set_comp_pol(enum ads1115_comp_pol_t pol, ads1115_adc_t *adc){
	adc->config &= ~ADS1115_COMP_POL_MASK;
	adc->config |= pol;

	ads1115_write_config(adc);
}

void ads1115_set_comp_lat(enum ads1115_comp_lat_t lat, ads1115_adc_t *adc){
	adc->config &= ~ADS1115_COMP_LAT_MASK;
	adc->config |= lat;

	ads1115_write_config(adc);
}

void ads1115_set_comp_que(enum ads1115_comp_que_t queue, ads1115_adc_t *adc){
	adc->config &= ~ADS1115_COMP_QUE_MASK;
	adc->config |= queue;

	ads1115_write_config(adc);
}


