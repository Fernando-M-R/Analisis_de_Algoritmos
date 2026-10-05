#include<stdio.h>

void Permutacion(char Letras[15], int inicio, int fin){
    
    if(inicio == fin)
        printf("%s\n", Letras);
    else{
        for(int i = inicio; i <= fin; i++){
            char temp = Letras[inicio];
            Letras[inicio] = Letras[i];
            Letras[i] = temp;

            Permutacion(Letras, inicio + 1, fin);

            temp = Letras[inicio];
            Letras[inicio] = Letras[i];
            Letras[i] = temp;
        }
    }

    
}

int main(){

    char Letras[15];
    int n;

    printf("Ingrese cuantas letras quiere ingresar: \n");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++)
        scanf("%c", &Letras[i]);
    getchar();
    Letras[n] = '\0';
    Permutacion(Letras, 0, n - 1);
    printf("\n");

    


    
    




    return 0;
}