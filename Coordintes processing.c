#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char data[] = "$GPGLL,4916.45,N,12311.12,W,225444,A";
char lng[];
char lat[];
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

void longitude(){

    for(cnt = 7; data[cnt] != ','; cnt++)
        lat[cnt - 7] += data[cnt];
}

int main()
{
    //printf("Hello world!\n");
    for(int i = 0; i < 8; i++){
        printf("%c", data[i]);
    }
    printf("%c", data[i]);
    while(true){
        if(gpgll()){
            printf("Hello world!\n");
            longitude();
            printf("%s", lng);
            system("pause");
        }
    }


    return 0;
}
