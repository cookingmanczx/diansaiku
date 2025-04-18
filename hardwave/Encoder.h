#ifndef __ENCODER_H
#define __ENCODER_H
extern volatile int16_t Encoder_Count;
extern volatile int16_t Encoder_Count1;
void Encoder_Init();
int16_t Get_Encoder_Count(void);
int16_t Get_Encoder_Count1(void);
#endif
