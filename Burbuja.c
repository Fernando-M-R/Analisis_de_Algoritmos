#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Burbuja(int a[], int len) {
    int i, aux;
    int ordenado = 0;
    int pasadas = 1;
    
    while (pasadas < len && ordenado == 0) {
        ordenado = 1;
        for (i = 0; i < len - pasadas; i++) {
            if (a[i] > a[i+1]) {
                // Intercambio
                aux = a[i];
                a[i] = a[i+1];
                a[i+1] = aux;
                ordenado = 0;
            }
        }
        pasadas++;
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
    Burbuja(arr, n);
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
