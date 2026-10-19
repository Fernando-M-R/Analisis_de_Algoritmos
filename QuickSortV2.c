#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Particion(int Arr[], int p, int r){
    int pivote = Arr[r];
    int i=p-1;
    int aux;
    for(int j=p; j<r; j++){
        if(Arr[j]<=pivote){
            i++;
            aux=Arr[j];
            Arr[j]=Arr[i];
            Arr[i]=aux;
        }
    }
   i++;
   aux=Arr[r];
   Arr[r]=Arr[i];
   Arr[i]=aux;
   return i; 
}

int Random(int p, int r){
    int n; 
    n = rand() % (r-p+1) + p;
    return n;
}

int ParticionAleatoria(int Arr[], int p, int r){
    int pos_pivote = Random(p, r);
    int aux=Arr[r];
    Arr[r]=Arr[pos_pivote];
    Arr[pos_pivote]=aux;    
    return Particion(Arr, p, r); 
}

void QuickSortAleatorio(int Arr[], int p, int r){
    if(p<r){
        int q=ParticionAleatoria(Arr, p, r);
        QuickSortAleatorio(Arr, p,  q-1);
        QuickSortAleatorio(Arr, q+1, r);
    }
}

void Aleatorios (int Arr[], int n){
srand(time(NULL)); 
    for (int i = 0; i < n; i++) {
        Arr[i] = rand() % 200000 - 100001;
    }   
}

void Ordenados (int Arr[], int n){
    for (int i = 0; i < n; i++) {
        Arr[i] = i-(n/2);
    }   
}

int main() {
    int n, opc;
    printf("Algoritmo QuickSort con pivote aleatorio\n");
    printf("Ingrese el numero de elementos: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    printf("\nDatos Ordenados o Aleatorios?:\n");
    printf("1 : Ordenados");
    printf("\n2 : Aleatorios\nOpcion: ");
    scanf("%d", &opc);
    if(opc==1)
        Ordenados(arr, n);
    else if(opc==2)
        Aleatorios(arr, n);
    else {
        printf("\nOpcion no valida");
        return 0;
    }
    if(n < 50) {
        printf("Arreglo original: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    
    clock_t inicio = clock();
    QuickSortAleatorio(arr, 0, n - 1);
    clock_t fin = clock();
    double tiempo = ((double)(fin - inicio) / CLOCKS_PER_SEC) * 1000.0;

    if(n < 50) {
        printf("Arreglo ordenado: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    printf("Milisegundos \n");
    printf("Tiempo de ejecucion: %.40f ms\n", tiempo);
    printf("Segundos \n");
    printf("Tiempo de ejecucion: %.40f s\n", tiempo / 1000.0);
    free(arr);

    return 0;
}