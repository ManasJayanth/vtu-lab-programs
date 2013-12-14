#include <stdio.h>
#include <string.h>
#define max 100

char r[max], temp[max], g[max], m[max], q[max];

void calrem() {
    int i;
    for(i = 1; i <= 16; ++i){
        r[i - 1] = ((int)temp[i] - 48) ^ ((int)g[i] - 48) + 48;
    }
}

void shiftl(){
    int i;
    for(i = 1; i <= 16; ++i){
        r[i - 1] = r[i];
    }
}

void crc(int n) {
    int i,j;
    for(i = 0; i <= 16; ++i){
        r[i] = m[i];
    }
    for(i = 0; i < n; ++i){
        temp[i] = m[i];
    }
    
    printf("Intermediate reminders: \n");
    for(i = 0; i < n-16; ++i){
        if(r[0] == '1'){
            q[i] = '1';
            calrem();
        }
        else {
            q[i] = '0';
            shiftl();
        }
        r[16] = m[17 + i]; //replace m[] with temp
        r[17] = '\0';
        printf("%s\n", r);
        for(j = 0; j <= 17; ++j) {
            temp[j] = r[j];
        }
    }
    q[i] = '\0';
}

void caltrans(n){
    int i, k = 0; 
    for(i = n-16; i < n; ++i){
        m[i] = r[k++];
    }
    m[i] = '\0';
}

int main(){
    int  n, i;
    //Input
    strcpy(m, "1011");

    //Generator
    for(i = 0; i < 17; ++i)
        g[i] = '0';
    g[0] = g[4] = g[11] = g[16] = '1';

    //Padding zero bits
    n = strlen(m);
    for(i = 0; i < 16; ++i){
        m[n++] = '0';
    }
    
    crc(n);
    printf("Remainder: %s", r);
    caltrans(n);
    printf("Transmitted bits: %s\n", m);
    crc(n);
    printf("Remainder now: %s", r);
    return 0;
}
