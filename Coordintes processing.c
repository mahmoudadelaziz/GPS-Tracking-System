#include "tm4c123gh6pm.h"
#ifndef __uint32_t_defined
typedef unsigned int                uint32_t;
# define __uint32_t_defined
#endif
#include "tm4c123.h"
#define pi 3.1415926
#define earthRadiusKm 6371
void delay(int);
void PortF_Output(unsigned int);
void PortF_Init(void);
unsigned int PortF_Input(void);
void PortA_Init(void);
void PortB_Init(void);
void LCD_Init(void);
void LCD_data(char);
void LCD_Command( char);
void UART2_Init(void);
char UART2_READ(void);
void mynum2str(double);
double ExtractLatitude(void);
double mystrtod(char[]);
double ExtractLongitude(void);
void mynum2char(double);
double degrees(double);



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

//GPGLL Message Format:
//$GPGLL,DDMM.MMMMM,S,DDDMM.MMMMM,S,HHMMSS.SS,SCC<CR><LF>
//EXAMPLE = $GPGLL,4916.45,N,12311.12,W,225444,A

char data[60];
char longitude[12];
char latitude[10];
int commas = 0;
int cnt;
char ending2[]="         m";
bool gpgll(){
	while(1){
 		int commas2=0;
	  data[0] = UART2_READ();	
    if(data[0] == '$'){
			data[1] = UART2_READ();
        if(data[1] == 'G'){
					data[2] = UART2_READ();
            if(data[2] == 'P'){
							data[3] = UART2_READ();
                if(data[3] == 'G'){
									data[4] = UART2_READ();
                    if(data[4] == 'L'){
											data[5] = UART2_READ();
                        if(data[5] == 'L'){
                            int j;
							for ( j = 6; j < 60; j++)
                            {
                                if (data[j] == ',') commas2++;
															  data[j]= UART2_READ();
                                if (commas2 == 6){
                                if( UART2_READ()=='A'){
																//	LCD_data('s');
																	commas2=0;
																	return true;																	
																}
																}
                            }
                        }
                    }
                }
            }
        }
    }

	}

}


double ExtractLatitude(void){
	char lat[10];
	int cnt2;
	//LCD_Command(0x80);
    for(cnt2 = 7; data[cnt2] != ','; cnt2++){
        lat[cnt2 - 7] = data[cnt2];
        //LCD_data(data[cnt2]);
		}
 		
	return degrees(strtod(lat,NULL));
}

double ExtractLongitude(void){
	char lng[20];
	int commas2 = 0;
    //LCD_Command(0xC0);
	int i;
	for (i = 5; i < 60; i++)
	{
		if (data[i] ==  ',') commas2++;
		if (commas2 == 3)
		{
		    int j;
			for (j = i+1; data[j] != ','; j++)
			{
				lng[j-i-1] = data[j];
				
               // LCD_data(data[j]);
			}
			break;
		}
	}
	return degrees(strtod(lng,NULL));
}

double degreesToRadians(double degrees) {
  return degrees * pi / 180;
}


double distance(double lat1, double lon1, double lat2, double lon2) {
	double dLat = degreesToRadians(lat2-lat1);
	double dLon = degreesToRadians(lon2-lon1);

	  lat1 = degreesToRadians(lat1);
	  lat2 = degreesToRadians(lat2);

	  double a = sin(dLat/2) * sin(dLat/2) +
			  sin(dLon/2) * sin(dLon/2) * cos(lat1) * cos(lat2); 
	  double c = 2 * atan2(sqrt(a), sqrt(1-a)); 
	 // LCD_data('x');
	  return (earthRadiusKm * c*1000);
}




int main(void)
{
	SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2) );
	PortA_Init();
	PortB_Init();
	PortF_Init();
	LCD_Init();
	PortF_Output(0x04);
	delay(1000);
  

	//delay(1000);
UART2_Init();
double d=0;
		double lat1 =0;
	double long1 = 0;
	double lat2 = 0;
	double long2 = 0;
	while(1){
	if(gpgll()){
	lat1 =ExtractLatitude();
	long1 =ExtractLongitude();
	break;
	}	
}
	while(1){
	

if(gpgll()){
	lat2 =ExtractLatitude();
	long2 =ExtractLongitude();
   d += distance(lat1,long1,lat2,long2);
 if (	d > 100){	PortF_Output(0x04);}
  mynum2str(d);
  int i;
  LCD_Command(0x80);
	for(i =0; i<10; i++){
	LCD_data(ending2[i]);}
	lat1 =lat2;
	long1 = long2;
	delay(5000);
	
	
	
		
}



}



	return 0;
}

void delay(int x)
{
    int i;
	for(i = 0; i<x*886;i++)
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
	GPIO_PORTA_CR_R |= 0xE0;
	GPIO_PORTA_DIR_R |= 0xE0;
	GPIO_PORTA_PUR_R = 0x00;
	GPIO_PORTA_DEN_R |= 0xE0;

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




void UART2_Init(void){
    SYSCTL_RCGCUART_R|= 0x00000004;
    SYSCTL_RCGCGPIO_R|= 0x00000008;
		while((SYSCTL_PRGPIO_R&0x08) == 0){}
	  GPIO_PORTD_LOCK_R = 0x4C4F434B;
			
		GPIO_PORTD_CR_R |= 0xC0;
    GPIO_PORTD_AFSEL_R |= 0xC0;
    GPIO_PORTD_DEN_R |=  0xC0;
	GPIO_PORTD_AMSEL_R = 0x00;
	GPIO_PORTD_PCTL_R |= 0x11000000;
    UART2_CTL_R = 0x00000000;
    UART2_IBRD_R=104;
    UART2_FBRD_R=11;
    UART2_LCRH_R = 0x00000060;
    UART2_CTL_R |= 0x00000301;
/*			GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0x00ffffff)+ 0x11000000;
    GPIO_PORTD_AMSEL_R &= ~0xC0;

			*/}






void mynum2str(double number)
{
	
	int iii = 0;
	for (;iii < 9;iii++) ending2[iii] = ' ';
	if(number !=0){
	double x = number - (int)number;
	char revstr[]="    ";
	char str[]="    ";
	char str2[]="   ";
	int length = 0;
	int length2 = 0;
	int length3 = 0;

	while ((int)number > 0)
	{
		int a = (int)number % 10;
		str[length++] = a + 48;
		number /= 10;
	}
	x *= 10;
	int i = 0;
	while (i < 3)
	{
		int a = (int)x % 10;
		str2[length2++] = a + 48;
		x *= 10;
		i++;
	}
	length--;
	int rev = 0;
	while (length >= 0)
	{
		revstr[rev++] = str[length--];
	}
	i = 0;
	while (revstr[i] >= 48 && revstr[i] <= 57)
	{
		ending2[length3++] = revstr[i++];
	}
	ending2[length3++] = '.';
	i = 0;
	while (str2[i] >= 48 && str2[i] <= 57)
	{
		ending2[length3++] = str2[i++];
	}
	}
	else {
	    ending2[0] = 'a';
	    ending2[1] = '7';
	    ending2[2] = 'a';
	}
}
void mynum2char(double dist)
{

    int ii = 0;
    int jj = 1;
		if (dist >=10000)
		{
			char Overflow[] = "OVER FLOW ";
			while(ii<sizeof(ending2)-1)
			{
				ending2[ii] = Overflow[ii];
			}
		}
		else
		{
			if ((int) dist / 1000)
			{
					ending2[ii] = (int) dist / 1000 + 48;  
					jj = 0;
			}
			else if(dist <1000 && jj)
			{
				ending2[ii] = ' ';//905
			}
			else
			{
				ending2[ii] = '0';
			}
			dist = dist - ((int) dist / 1000) * 1000;
			ii++;
			if ((int) dist / 100)
			{
					ending2[ii] = (int) dist / 100 + 48;
					jj = 0;
			}
			else if(dist <100 && jj)
			{
				ending2[ii] = ' ';
			}
			else
			{
				ending2[ii] = '0';
			}
			dist = dist - ((int) dist / 100) * 100;
			ii++;
			if ((int) dist / 10)
			{
					ending2[ii] = (int) dist / 10 + 48;
					jj = 0;
			}
			else if(dist <10 && jj)
			{
				ending2[ii] = ' ';
			}
			else
			{
				ending2[ii] = '0';
			}
			dist = dist - ((int) dist / 10) * 10;
			ii++;
			if ((int) dist)
			{
					ending2[ii] = (int) dist + 48;
			}
			else
			{
				ending2[ii] = '0';
			}
			dist = dist - (int) dist;
			ending2[++ii]='.';
			ii++;
			if ((int) (10 * dist))
			{
					ending2[ii] = (int) (10 * dist) + 48;
			}
			else
			{
				ending2[ii] = '0';
			}
			dist = dist - ((int) (10 * dist)) / (double) 10;
			ii++;
			if ((int) (100 * dist))
			{
					ending2[ii] = (int) (100 * dist) + 48;
			}
			else
			{
				ending2[ii] = '0';
			}
			dist = dist - ((int) (100 * dist)) / (double) 100;
			ii++;
			if ((int) (1000 * dist))
			{
					ending2[ii] = (int) (1000 * dist) + 48;	
			}
			else
			{
				ending2[ii] = '0';
			}
		}
		

}

double degrees(double x)
{
    double degs = 0;
    int temp = x / 100;
    degs = temp + (x - 100 * temp) / 60.0;

    return degs;
}


char UART2_READ(void)
{
    char data;
                  while((UART2_FR_R&0x10) !=0){} 
       data = (UART2_DR_R&0xFF) ;      
    return  data; 
}


void write_UART(char data)
{
    while((UART2_FR_R&0x20) !=0){}
    UART2_DR_R = data;
}

