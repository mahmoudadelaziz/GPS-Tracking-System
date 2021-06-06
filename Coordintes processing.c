#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

//GPGLL Message Format:
//$GPGLL,DDMM.MMMMM,S,DDDMM.MMMMM,S,HHMMSS.SS,S*CC<CR><LF>

// $GPGLL,4916.45,N,12311.12,W,225444,A
// $GPGLL,8989.05,N,64387.55,W,225444,A

double earthRadiusKm = 6371;
double pi = 3.142857143;

char data[60];
char data_destination[60];

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

double ExtractLatitude(char pt[]){
	char lat[10];
    for(int cnt = 7; pt[cnt] != ','; cnt++)
        lat[cnt - 7] = pt[cnt];
	return strtod(lat,NULL);
}

double ExtractLongitude(char pnt[]){
	char lng[20];
	int commas = 0;
	for (int k = 0; k < 21; k++)
	{
		lng[k] = '0';
	}
	
	for (int i = 5; i < 60; i++)
	{
		if (pnt[i] ==  ',') commas++;
		if (commas == 3)
		{
			for (int j = i+1; pnt[j] != ','; j++)
			{
				lng[j-i-1] = pnt[j];
			}
			break;
		}
	}
	return strtod(lng,NULL);
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
	  return earthRadiusKm * c;
}

int main()
{
	printf("Enter the starting point\n");
	fgets(data, sizeof(data), stdin);
	printf("Enter the destination point\n");
	fgets(data_destination, sizeof(data_destination), stdin);

    if(gpgll())
	{
        double lat1 = ExtractLatitude(data);
		//double LatValue = strtod(latitude, NULL);
		printf("Latitude: %lf\n", lat1);
		
		double lng1 = ExtractLongitude(data);
		//double LonValue = strtod(longitude, NULL);
		printf("Longitude: %lf\n", lng1);
		
		double lat2 = ExtractLatitude(data_destination);
		//double LatValue = strtod(latitude, NULL);
		printf("Latitude: %lf\n", lat2);
		
		double lng2 = ExtractLongitude(data_destination);
		//double LonValue = strtod(longitude, NULL);
		printf("Longitude: %lf\n", lng2);
		
		//Displaying Distance
		double d = distance(lat1, lng1, lat2, lng2);
		printf("The distance between the points is %lf\n", d);

        system("pause");
    }

    return 0;
}
