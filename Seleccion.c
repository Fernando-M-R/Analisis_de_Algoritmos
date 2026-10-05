#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void seleccion(int a[], int n) {
    int i, j, min_idx, aux;
    
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (a[j] < a[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            aux = a[min_idx];
            a[min_idx] = a[i];
            a[i] = aux;
        }
    }
} 

int main() {
    int n;
    printf("Ingrese el numero de elementos: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));

    srand(time(NULL)); 
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 20001 - 10000;
    }

    if(n < 50) {
        printf("Arreglo original: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    
    clock_t inicio = clock();
    seleccion(arr, n);
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


    return 0;
}
