#include<stdio.h>

int ParesPalos(int Numeros[], int n){
    int par1=0, par2=0, j = 0;

    while(j < n-1){
        if(Numeros[j] == Numeros[j+1]){
            if(par1 == 0){
                par1 = Numeros[j];
            }
            else{
                par2 = Numeros[j];
                break;
            }
            j = j+2;
        }
        else
            j++;
    }

    if(par1 && par2 != 0){
        return par1 * par2;
    }

    return -1;
}

void BubbleSort(int Numeros[], int n){
    int i, j, temp;
    for(i = 0; i < n-1; i++){
        for(j = 0; j < n-i-1; j++){
            if(Numeros[j] < Numeros[j+1]){
                temp = Numeros[j];
                Numeros[j] = Numeros[j+1];
                Numeros[j+1] = temp;
            }
        }
    }
}

int main(){

    int Numeros[1000];
    int n;
    printf("Ingrese cuantos palos desea ingresar:\n");
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        scanf("%d", &Numeros[i]);
    }
    
    BubbleSort(Numeros, n);
    int resultado = ParesPalos(Numeros, n);
    printf("El resultado es: %d\n", resultado);
    return 0;
}