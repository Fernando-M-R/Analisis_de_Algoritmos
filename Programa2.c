#include<stdio.h>

int main() {

    int numeros[10];

    while(1) {
        for(int i = 0; i < 3; i++)  
            scanf("%d", &numeros[i]);
        getchar();
        
        if((numeros[0] == 0 && numeros[1] == 0) || (numeros[1] == 0 && numeros[2] == 0))
            break;

        if((numeros[1] - numeros[0]) == (numeros[2] - numeros[1])) 
            printf("AP: %d\n", numeros[2]+(numeros[2] - numeros[1]));
        
        else {
            if((numeros[1] / numeros[0]) == (numeros[2] / numeros[1]))
                printf("GP: %d\n", numeros[2]*(numeros[2] / numeros[1]));
            else 
                printf("No es ninguna\n");
        }
    }
    return 0;
}