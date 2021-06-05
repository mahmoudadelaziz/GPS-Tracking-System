#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//GPGLL Message Format:
//$GPGLL,DDMM.MMMMM,S,DDDMM.MMMMM,S,HHMMSS.SS,S*CC<CR><LF>
//EXAMPLE = $GPGLL,4916.45,N,12311.12,W,225444,A

char data[60];
char longitude[12];
char latitude[10];
int commas = 0;
int cnt;

bool gpgll(){
    if(data[0] == '$'){
        if(data[1] == 'G'){
            if(data[2] == 'P'){
                if(data[3] == 'G'){
                    if(data[4] == 'L'){
                        if(data[5] == 'L'){
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

void ExtractLatitude(){

    for(cnt = 7; data[cnt] != ','; cnt++)
        latitude[cnt - 7] += data[cnt];
} //Supposedly accurate

void ExtractLongitude(){
	
	for (int i = 5; i < sizeof(data); i++)
	{
		if (data[i] ==  ',') commas++;
		if (commas == 3)
		{
			for (int j = i+1; data[j] != ','; j++)
			{
				longitude[j-i-1] = data[j];
			}
			break;
		}
	}
}

int main()
{
	fgets(data, sizeof(data), stdin);
	
/*     for(int i = 0; i < strlen(data)-1; i++){
        printf("%c", data[i]);
    } //Debugging step, printing the array taken from the GPS module, as it is.
	printf("\n"); */

    if(gpgll())
	{
        ExtractLatitude();
		double LatValue = strtod(latitude, NULL);
		printf("Latitude: %lf\n", LatValue);
		
		ExtractLongitude();
		double LonValue = strtod(longitude, NULL);
		printf("Longitude: %lf\n", LonValue);
		
        system("pause");
    }

    return 0;
}