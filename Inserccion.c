#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insercion(int a[], int n) {
    int i, j, key;
    
    for (j = 1; j < n; j++) {
        key = a[j];
        i = j - 1;
        
        while (i >= 0 && a[i] > key) {
            a[i + 1] = a[i];
            i = i - 1;
        }
        a[i + 1] = key;
    }
}


int main() {
    int n;
    printf("Ingrese el numero de elementos: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));

    srand(time(NULL)); 
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000 + 1;
    }

    if(n < 50) {
        printf("Arreglo original: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    
    clock_t inicio = clock();
    insercion(arr, n);
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
