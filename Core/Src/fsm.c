/*
 * fsm.c
 *
 *  Created on: Apr 14, 2024
 *      Author: paloma
 */
#include "main.h"
#include <stdio.h>
#include "ads1115.h"
#include "fsm.h"
#include "string.h"

char menu[] = "\nIngresar: \na para leer la configuracion\nb para modificar la configuracion\nc para adquirir un dato\n";

UART_HandleTypeDef *huart;

void fsm_init(estados_e *estado, eventos_e *evento, UART_HandleTypeDef *huart1){
	*estado = main_menu;
	*evento = N;
	huart = huart1;
	imprimir_cad(menu);
}

void fsm_switch(estados_e *estado, eventos_e evento, ads1115_adc_t *adc){

	switch(*estado){
	case main_menu:
		switch(evento){
		case A:
			*estado = read_config;
			fun_e1_c1(adc);
			break;
		case B:
			*estado = write;
			fun_e1_c2(adc);
			break;
		case C:
			*estado = data;
			fun_e1_c3(adc);
			break;
		default:
			*estado = main_menu;
			imprimir_cad("\nNo se reconoce el caracter ingresado, ingrese uno valido\n");
			break;
		}
	break;

	case read_config:
		switch(evento){
		case R:
			*estado = main_menu;
			imprimir_cad(menu);
			break;
		default:
			*estado = read_config;
			imprimir_cad("\nNo se reconoce el caracter ingresado, ingrese uno valido\n");
			break;
		}
	break;

	case write:
		switch(evento){
		case R:
			*estado = main_menu;
			imprimir_cad(menu);
			break;
		case A:
			fun_e2_c1(adc);
			break;
		case B:
			fun_e2_c2(adc);
			break;
		case C:
			fun_e2_c3(adc);
			break;
		case D:
			fun_e2_c4(adc);
			break;
		case E:
			fun_e2_c5(adc);
			break;
		case F:
			fun_e2_c6(adc);
			break;
		case G:
			fun_e2_c7(adc);
		case H:
			fun_e2_c8(adc);
			break;
		default:
			*estado = write;
			imprimir_cad("\nNo se reconoce el caracter ingresado, ingrese uno valido\n");
			break;
		}
	break;

	case data:
		switch(evento){
		case R:
			*estado = main_menu;
			imprimir_cad(menu);
		    break;
		case A:
			fun_e1_c3(adc);
			break;
		default:
			*estado = data;
			imprimir_cad("\nNo se reconoce el caracter ingresado, ingrese uno valido\n");
			break;
		}
		break;
	}
}

void fun_e1_c1(ads1115_adc_t *adc){
	uint16_t mux, pga, operating_mode, rate, comparator, latching_comparator, comparator_queue;
	uint16_t comp_polarity;

	ads1115_read_config(adc);

	mux = adc->config & ADS1115_MUX_MASK;

	imprimir_cad("\nLa configuracion actual es: \n");
	if (mux == ADS1115_MUX_DIFF_0_1){
		imprimir_cad("mux diferencial entre 0 y 1\n");
	}
	if (mux == ADS1115_MUX_DIFF_0_3){
		imprimir_cad("mux diferencial entre 0 y 3\n");
	}
	if (mux == ADS1115_MUX_DIFF_1_3){
		imprimir_cad("mux diferencial entre 1 y 3\n");
	}
	if (mux == ADS1115_MUX_DIFF_2_3){
		imprimir_cad("mux diferencial entre 2 y 3\n");
	}
	if (mux == ADS1115_MUX_SINGLE_0){
		imprimir_cad("mux single channel 0\n");
	}
	if (mux == ADS1115_MUX_SINGLE_1){
		imprimir_cad("mux single channel 1\n");
	}
	if (mux == ADS1115_MUX_SINGLE_2){
		imprimir_cad("mux single channel 2\n");
	}
	if (mux == ADS1115_MUX_SINGLE_3){
		imprimir_cad("mux single channel 3\n");
	}

	pga = adc->config & ADS1115_PGA_MASK;

	if (pga == ADS1115_PGA_6_144){
		imprimir_cad("PGA = 6.144\n");
	}
	if (pga == ADS1115_PGA_4_096){
		imprimir_cad("PGA = 4.096\n");
	}
	if (pga == ADS1115_PGA_2_048){
		imprimir_cad("PGA = 2.048\n");
	}
	if (pga == ADS1115_PGA_1_024){
		imprimir_cad("PGA = 1.024\n");
	}
	if (pga == ADS1115_PGA_0_512){
		imprimir_cad("PGA = 0.512\n");
	}
	if (pga == ADS1115_PGA_0_256){
		imprimir_cad("PGA = 0.256\n");
	}

	operating_mode = adc->config & ADS1115_MODE_MASK;

	if (operating_mode == ADS1115_MODE_CONTINUOUS){
		imprimir_cad("El modo es de conversión continua\n");
	}
	if (operating_mode == ADS1115_MODE_SINGLE_SHOT){
		imprimir_cad("El modo es de disparo unico\n");
	}

	rate = adc->config & ADS1115_RATE_MASK;

	if (rate == ADS1115_RATE_8_SPS){
		imprimir_cad("Rate = 8 SPS\n");
	}
	if (rate == ADS1115_RATE_16_SPS){
		imprimir_cad("Rate = 16 SPS\n");
	}
	if (rate == ADS1115_RATE_32_SPS){
		imprimir_cad("Rate = 32 SPS\n");
	}
	if (rate == ADS1115_RATE_64_SPS){
		imprimir_cad("Rate = 64 SPS\n");
	}
	if (rate == ADS1115_RATE_128_SPS){
		imprimir_cad("Rate = 128 SPS\n");
	}
	if (rate == ADS1115_RATE_250_SPS){
		imprimir_cad("Rate = 250 SPS\n");
	}
	if (rate == ADS1115_RATE_475_SPS){
		imprimir_cad("Rate = 475 SPS\n");
	}
	if (rate == ADS1115_RATE_860_SPS){
		imprimir_cad("Rate = 860 SPS\n");
	}

	comparator = adc->config & ADS1115_COMP_MODE_MASK;

	if (comparator == ADS1115_COMPARATOR_TRADITIONAL){
		imprimir_cad("El comparador es tradicional\n");
	}
	if (comparator == ADS1115_COMPARATOR_WINDOW){
		imprimir_cad("Hay una ventana de comparacion\n");
	}

	 comp_polarity = adc->config & ADS1115_COMP_POL_MASK;

	 if (comp_polarity == ADS1115_COMPARATOR_POLARITY_LO){
		 imprimir_cad("Polaridad de comparacion baja\n");
	 }
	 if (comp_polarity == ADS1115_COMPARATOR_POLARITY_HI){
		 imprimir_cad("Polaridad de comparacion alta\n");
	 }

	 latching_comparator = adc->config & ADS1115_COMP_LAT_MASK;

	 if (latching_comparator == ADS1115_COMPARATOR_NONLATCHING){
		 imprimir_cad("Comparador sin latching\n");
	 }
	 if (latching_comparator == ADS1115_COMPARATOR_LATCHING){
		 imprimir_cad("Comparador con latching\n");
	 }

	 comparator_queue = adc->config & ADS1115_COMP_QUE_MASK;

	if (comparator_queue == ADS1115_COMPARATOR_QUE_1){
		imprimir_cad("La fila de comparador es 1\n");
	}
	if (comparator_queue == ADS1115_COMPARATOR_QUE_2){
		imprimir_cad("La fila de comparador es 2\n");
	}
	if (comparator_queue == ADS1115_COMPARATOR_QUE_4){
		imprimir_cad("La fila de comparador es 4\n");
	}
	if (comparator_queue == ADS1115_COMPARATOR_QUE_DISABLE){
		imprimir_cad("La fila de comparador esta deshabilitada\n");
	}

	imprimir_cad("\nIngrese r para volver\n");

}

void fun_e1_c2(ads1115_adc_t *adc){

	imprimir_cad("\nIngrese:\na Para configurar el mux\nb Para configurar PGA\nc Para cambiar el modo\nd Para modificar la tasa\ne Para el modo de comparacion\nf Para la polaridad de comparacion\ng Para el latchign de comparacion\nh Para establecer o deshabilitar la fila de comparacion\n");
	imprimir_cad("\nIngrese r para volver\n");
}

void fun_e1_c3(ads1115_adc_t *adc){
	int16_t valor;
	int conversion_parte_entera;
	int conversion_parte_decimal;
	float valor_volts;
	char valor_str[20];
	char valor_v[20];

	// valor de la conversion
	ads1115_read_adc(&valor, adc);
	valor_volts = ads1115_conv_volts(valor, adc);
	conversion_parte_entera = (int)valor_volts;
	conversion_parte_decimal = (valor_volts - conversion_parte_entera) * 1000000;


	sprintf(valor_str, "%d \n", valor);
	sprintf(valor_v, "%d.%06dV \n", conversion_parte_entera, conversion_parte_decimal);


	imprimir_cad("\n Se realiza y se muestra una conversion\n");
	imprimir_cad("Valor de la conversion: ");
	imprimir_cad(valor_str);
	imprimir_cad("Valor en volts: ");
	imprimir_cad(valor_v);
	imprimir_cad("Presione a para realizar otra conversion o r para volver\n");
}

void fun_e2_c1(ads1115_adc_t *adc){
	char opcion;
	imprimir_cad("\nSeleccione la opcion que desea\n");
	imprimir_cad("a Diferencial entre canales 0 y 1\nb Diferencial entre canales 0 y 3\nc Diferencial entre canales 1 y 3\n");
	imprimir_cad("d Diferencial entre canales 2 y 3\ne Canal single 0\nf Canal single 1\ng Canal single 2\nh Canal single 3\n");
	recibir_char(&opcion);

	ads1115_read_config(adc);

	if (opcion == 'a'){
		ads1115_set_mux(ADS1115_MUX_DIFF_0_1, adc);
	}
	if (opcion == 'b'){
		ads1115_set_mux(ADS1115_MUX_DIFF_0_3, adc);
	}
	if (opcion == 'c'){
		ads1115_set_mux(ADS1115_MUX_DIFF_1_3, adc);
	}
	if (opcion == 'd'){
		ads1115_set_mux(ADS1115_MUX_DIFF_2_3, adc);
	}
	if (opcion == 'e'){
		ads1115_set_mux(ADS1115_MUX_SINGLE_0, adc);
	}
	if (opcion == 'f'){
		ads1115_set_mux(ADS1115_MUX_SINGLE_1, adc);
	}
	if (opcion == 'g'){
		ads1115_set_mux(ADS1115_MUX_SINGLE_2, adc);
	}
	if (opcion == 'f'){
		ads1115_set_mux(ADS1115_MUX_SINGLE_3, adc);
	}

	imprimir_cad("\nEl cambio fue realizado\n");

	fun_e1_c2(adc);
}

void fun_e2_c2(ads1115_adc_t *adc){
	char opcion;

	ads1115_read_config(adc);

	imprimir_cad("\nSeleccione la opcion que desea\n");
	imprimir_cad("a PGA = 6.144\nb PGA = 4.096\nc PGA = 2.048\nd PGA = 1.024\ne PGA = 0.512\nf PGA = 0.256\n");
	recibir_char(&opcion);

	if (opcion == 'a'){
		ads1115_set_pga(ADS1115_PGA_6_144, adc);
	}
	if (opcion == 'b'){
		ads1115_set_pga(ADS1115_PGA_4_096, adc);
	}
	if (opcion == 'c'){
		ads1115_set_pga(ADS1115_PGA_2_048, adc);
	}
	if (opcion == 'd'){
		ads1115_set_pga(ADS1115_PGA_1_024, adc);
	}
	if (opcion == 'e'){
		ads1115_set_pga(ADS1115_PGA_0_512, adc);
	}
	if (opcion == 'f'){
		ads1115_set_pga(ADS1115_PGA_0_256, adc);
	}

	imprimir_cad("\nEl cambio fue realizado\n");

	fun_e1_c2(adc);
}

void fun_e2_c3(ads1115_adc_t *adc){
	char opcion;

	ads1115_read_config(adc);
	imprimir_cad("\nSeleccione el modo que desea\n");
	imprimir_cad("a Modo continuo\nb Modo de disparo unico\n");
	recibir_char(&opcion);

	if (opcion == 'a'){
		ads1115_set_mode(ADS1115_MODE_CONTINUOUS, adc);
	}
	if (opcion == 'b'){
		ads1115_set_mode(ADS1115_MODE_SINGLE_SHOT, adc);
	}

	imprimir_cad("\nEl cambio fue realizado\n");

	fun_e1_c2(adc);
}

void fun_e2_c4(ads1115_adc_t *adc){
	char opcion;
	ads1115_read_config(adc);

	imprimir_cad("\nSeleccione la tasa que desee\n");
	imprimir_cad("a 8 SPS\nb 16 SPS\nc 32 SPS\nd 64 SPS\ne 128 SPS\nf 250 SPS\ng 475 SPS \nh 860 SPS\n");
	recibir_char(&opcion);

	if (opcion == 'a'){
		ads1115_set_rate(ADS1115_RATE_8_SPS, adc);
	}
	if (opcion == 'b'){
		ads1115_set_rate(ADS1115_RATE_16_SPS, adc);
	}
	if (opcion == 'c'){
		ads1115_set_rate(ADS1115_RATE_32_SPS, adc);
	}
	if (opcion == 'd'){
		ads1115_set_rate(ADS1115_RATE_64_SPS, adc);
	}
	if (opcion == 'e'){
		ads1115_set_rate(ADS1115_RATE_128_SPS, adc);
	}
	if (opcion == 'f'){
		ads1115_set_rate(ADS1115_RATE_250_SPS, adc);
	}
	if (opcion == 'g'){
		ads1115_set_rate(ADS1115_RATE_475_SPS, adc);
	}
	if (opcion == 'h'){
		ads1115_set_rate(ADS1115_RATE_860_SPS, adc);
	}

	imprimir_cad("\nEl cambio fue realizado\n");

	fun_e1_c2(adc);
}

void fun_e2_c5(ads1115_adc_t *adc){
	char opcion;

	ads1115_read_config(adc);
	imprimir_cad("\nAca se modifica el modo de comparacion\n");
	imprimir_cad("a Para comparador tradicional\nb Para ventana de comparacion\n");
	recibir_char(&opcion);

	if (opcion == 'a'){
		ads1115_set_comp_mode(ADS1115_COMPARATOR_TRADITIONAL, adc);
	}
	if (opcion == 'b'){
		ads1115_set_comp_mode(ADS1115_COMPARATOR_WINDOW, adc);
	}

	imprimir_cad("\nEl cambio fue realizado\n");

	fun_e1_c2(adc);
}

void fun_e2_c6(ads1115_adc_t *adc){
	char opcion;
	ads1115_read_config(adc);
	imprimir_cad("\nSeleccione la opcion que desea\n");
	imprimir_cad("a Para comparador con polaridad baja\nb Para comparador con polaridad alta\n");
	recibir_char(&opcion);

	if (opcion == 'a'){
		ads1115_set_comp_pol(ADS1115_COMPARATOR_POLARITY_LO, adc);
	}
	if (opcion == 'b'){
		ads1115_set_comp_pol(ADS1115_COMPARATOR_POLARITY_HI, adc);
	}

	imprimir_cad("\nEl cambio fue realizado\n");

	fun_e1_c2(adc);
}

void fun_e2_c7(ads1115_adc_t *adc){
	char opcion;
	imprimir_cad("\nSeleccione la opcion que desee\n");
	imprimir_cad("a Para comparador sin latching\nb Para comparador con latching");
	recibir_char(&opcion);

	if (opcion == 'a'){
		ads1115_set_comp_lat(ADS1115_COMPARATOR_NONLATCHING, adc);
	}
	if (opcion == 'b'){
		ads1115_set_comp_lat(ADS1115_COMPARATOR_LATCHING, adc);
	}
	imprimir_cad("\nEl cambio fue realizado\n");

	fun_e1_c2(adc);
}

void fun_e2_c8(ads1115_adc_t *adc){
	char opcion;
	ads1115_read_config(adc);

	imprimir_cad("Seleccione las opciones de la fila del comparador\n");
	imprimir_cad("a Para 1 valor\nb Para 2 valores\nc Para 4 valores\nd Para deshabilitar la fila\n");
	recibir_char(&opcion);

	if (opcion == 'a'){
		ads1115_set_comp_que(ADS1115_COMPARATOR_QUE_1, adc);
	}
	if (opcion == 'b'){
		ads1115_set_comp_que(ADS1115_COMPARATOR_QUE_2, adc);
	}
	if (opcion == 'c'){
		ads1115_set_comp_que(ADS1115_COMPARATOR_QUE_4, adc);
	}
	if (opcion == 'd'){
		ads1115_set_comp_que(ADS1115_COMPARATOR_QUE_DISABLE, adc);
	}

	imprimir_cad("\nEl cambio fue realizado\n");

	fun_e1_c2(adc);

}

void imprimir_cad(char cadena[]){
	HAL_UART_Transmit(huart, (uint8_t *)cadena, strlen(cadena), HAL_MAX_DELAY);
}
void recibir_char(char *caracter){
	uint8_t aux;
	HAL_UART_Receive(huart, (uint8_t *)caracter, 1, HAL_MAX_DELAY);

	while (HAL_UART_Receive(huart, &aux, 1, 10) != HAL_TIMEOUT){

	}
}

void char_to_evento(eventos_e *evento, char letra){

	switch(letra){
	case 'a':
		*evento = A;
		break;
	case 'b':
		*evento = B;
		break;
	case 'c':
		*evento = C;
		break;
	case 'd':
		*evento = D;
		break;
	case 'e':
		*evento = E;
		break;
	case 'f':
		*evento = F;
		break;
	case 'g':
		*evento = G;
		break;
	case 'h':
		*evento = H;
		break;
	case 'r':
		*evento = R;
		break;
	default:
		*evento = N;
		break;
	}
}


