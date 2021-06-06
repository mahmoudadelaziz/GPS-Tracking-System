#include "tm4c123gh6pm.h"
#ifndef __uint32_t_defined
typedef unsigned int                uint32_t;
# define __uint32_t_defined
#endif

#define PI 3.1415926
float power (float,float);
int fact(int);
float sine(float);
float cosine(float);
float arctan(float);
float distant(float,float,float,float);
float squarroot(float);
void delay(int);
void PortF_Output(unsigned int);
void PortF_Init(void);
unsigned int PortF_Input(void);
void PortA_Init(void);
void PortB_Init(void);
void LCD_Init(void);
void LCD_data(char);
void LCD_Command( char);


int main(void)
{
	PortA_Init();
	PortB_Init();
	PortF_Init();
	LCD_Init();
	PortF_Output(0x04);
	delay(1000);

	PortF_Output(0x02);
	//delay(1000);
	char x[11]="666";
	int i =0;
	while(i<3){

		LCD_data(x[i]);
		delay(1000);
		i++;
	}
	while(1){}

	return 0;
}

void delay(int x)
{
	for(int i = 0; i<x*886;i++)
	{
		GPIO_PORTF_DATA_R |= 0;
	}

}






void PortF_Init(void)
{
	SYSCTL_RCGCGPIO_R |= 0x20;
	while((SYSCTL_PRGPIO_R&0x20) == 0){}
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R = 0x1F;
	GPIO_PORTF_DIR_R = 0x0E;
	GPIO_PORTF_PUR_R = 0x11;
	GPIO_PORTF_DEN_R = 0x1F;
}
void PortA_Init(void)
{
	SYSCTL_RCGCGPIO_R |= 0x01;
	while((SYSCTL_PRGPIO_R&0x01) == 0){}
	GPIO_PORTA_LOCK_R = 0x4C4F434B;
	GPIO_PORTA_CR_R |= 0xE3;
	GPIO_PORTA_DIR_R |= 0xE3;
	GPIO_PORTA_PUR_R = 0x00;
	GPIO_PORTA_DEN_R |= 0xE3;
	GPIO_PORTA_AFSEL_R |=0x03;
	GPIO_PORTA_PCTL_R |= 0x11;

}


void PortB_Init(void)
{
	SYSCTL_RCGCGPIO_R |= 0x02;
	while((SYSCTL_PRGPIO_R&0x02) == 0){}
	GPIO_PORTB_LOCK_R = 0x4C4F434B;
	GPIO_PORTB_CR_R |= 0xFF;
	GPIO_PORTB_DIR_R |= 0xFF;
	GPIO_PORTB_PUR_R = 0x00;
	GPIO_PORTB_DEN_R |= 0xFF;


}


unsigned int PortF_Input(void)
{
	return(GPIO_PORTF_DATA_R&0x11);
}
void PortF_Output(unsigned int data)
{
	GPIO_PORTF_DATA_R = data;
}


void LCD_Init(void)
{
	GPIO_PORTA_DATA_R &= ~(0xE0);
	LCD_Command(0x1);
	LCD_Command(0x2);
	LCD_Command(0x0f);
	LCD_Command(0x05);
	LCD_Command(0x06);
	LCD_Command(0x10);
	LCD_Command(0x38);
	LCD_Command(0x80);

}

void LCD_Command(char cmd)
{
	delay(10);
	GPIO_PORTA_DATA_R &= ~(0x80);
		delay(10);
	GPIO_PORTA_DATA_R |= 0x20;
	GPIO_PORTB_DATA_R = cmd;
	//delay(4);

	GPIO_PORTA_DATA_R &= ~(0x20);
		delay(10);

}

void LCD_data(char data)
{
	GPIO_PORTA_DATA_R |= 0x80;
	GPIO_PORTA_DATA_R |= 0x20;
	GPIO_PORTB_DATA_R = data;


	GPIO_PORTA_DATA_R &= ~(0x20);
	LCD_Command(0x6);
}


void PortD_Init(void)
{
	SYSCTL_RCGCGPIO_R |= 0x08;
	while((SYSCTL_PRGPIO_R&0x08) == 0){}
	GPIO_PORTD_LOCK_R = 0x4C4F434B;
	GPIO_PORTD_CR_R |= 0xC0;
	GPIO_PORTD_DEN_R |= 0xC0;
	GPIO_PORTD_AFSEL_R |=0xC0;
	GPIO_PORTD_AMSEL_R = 0x00;
	GPIO_PORTD_PCTL_R |= 0x11000000;

}
