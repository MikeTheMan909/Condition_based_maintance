#include <main.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#define DEBUG_C_

#include "debug.h"

char debug_level = DBL_DEFAULT;

#ifdef ENABLE_DEBUG

void print_debug(const char *module, const char *text){
	char tmp_debug[1000]="";
	strcat(tmp_debug, module);
	strcat(tmp_debug,":\t");
	strcat(tmp_debug,text);
	strcat(tmp_debug,"\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t*) tmp_debug, strlen(tmp_debug), 100);
	HAL_Delay(100);
}

void printf_debug(const char *module, const char *text, ...){
	char tmp_debug[1000]="";
	strcat(tmp_debug, module);
	strcat(tmp_debug,":\t");
	size_t len = strlen(tmp_debug);
	va_list arglist;
	va_start(arglist, text);
	snprintf(tmp_debug + len, 1000 - len, text, arglist);
	va_end(arglist);
	strcat(tmp_debug,"\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t*) tmp_debug, strlen(tmp_debug), 100);
	HAL_Delay(100);
}

#endif
