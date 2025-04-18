#ifndef __SERIAL_H
#define __SERIAL_H
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define RX_BUFFER_SIZE 256  // »º³åÇø´óÐ¡
extern char rx_buffer[RX_BUFFER_SIZE]; 
extern int Rec_Flag;
extern int Index;

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_Printf(char *format, ...);



#endif
