/*
 * fsm.h
 *
 *  Created on: Apr 14, 2024
 *      Author: paloma
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_
typedef enum {main_menu, read_config, data, write}estados_e;

typedef enum {A, B, C, D, E, F, G, H, R, N}eventos_e;

void fsm_init(estados_e *estado, eventos_e *evento, UART_HandleTypeDef *huart);
void fsm_switch(estados_e *estado, eventos_e evento, ads1115_adc_t *adc);
void fun_e1_c1(ads1115_adc_t *adc);
void fun_e1_c2(ads1115_adc_t *adc);
void fun_e1_c3(ads1115_adc_t *adc);
void fun_e2_c1(ads1115_adc_t *adc);
void fun_e2_c2(ads1115_adc_t *adc);
void fun_e2_c3(ads1115_adc_t *adc);
void fun_e2_c4(ads1115_adc_t *adc);
void fun_e2_c5(ads1115_adc_t *adc);
void fun_e2_c6(ads1115_adc_t *adc);
void fun_e2_c7(ads1115_adc_t *adc);
void fun_e2_c8(ads1115_adc_t *adc);
void imprimir_cad(char cadena[]);
void recibir_char(char *caracter);
void char_to_evento(eventos_e *evento, char caracter);


#endif /* INC_FSM_H_ */
