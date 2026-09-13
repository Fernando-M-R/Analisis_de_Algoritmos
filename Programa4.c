#include<stdio.h>

int DigitosNoIguales(int n1){

    while(n1 > 0){
        int numero = n1%10, resto = n1/10;
        while(resto > 0){

            if(numero == resto%10){
                return 0;
            }
            resto /= 10;
        }
        n1 /= 10;
    }
    return 1;
}

int main(){

    int numeros[2], contador = 0;

    printf("Ingrese dos numeros: \n");
    for(int i = 0; i < 2; i++)
        scanf("%d", &numeros[i]);
    for(int i = numeros[0]; i <= numeros[1]; i++)
        contador = contador + DigitosNoIguales(i);
        
    printf("Cantidad de numeros con digitos no iguales: %d\n", contador);


    return 0;
}