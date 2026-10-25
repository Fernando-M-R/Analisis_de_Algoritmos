#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//El arrglo lo hacemos de tamano n+1 siempre
int* SumaArr(int *num1, int *num2, int n){
    int *Resul = (int*)malloc((n+1)*sizeof(int));
    int acarreo=0, suma=0;
    for (int i = n - 1; i >= 0; i--) {
        suma = num1[i] + num2[i] + acarreo;
        Resul[i + 1] = suma % 10;
        acarreo = suma / 10;
    }
    Resul[0] = acarreo;
    return Resul;
}

// Suponemos que num1 es mayor que nun2 siempre
int* RestaArr(int *num1, int *num2, int n){
    int *Resul = (int*)malloc(n*sizeof(int));
    int prestamo = 0;
    for (int i = n - 1; i >= 0; i--) {
        int resta = num1[i] - num2[i] - prestamo;
        if (resta < 0) {
            resta += 10;
            prestamo = 1;
        } else {
            prestamo = 0;
        }
        Resul[i] = resta;
    }
    return Resul;
}

int* RecorrerIz(int *num, int n, int recorrer){
    int *Resul = calloc((n+recorrer), sizeof(int));
    for(int i=0; i<n; i++)
        Resul[i] = num[i];
    return Resul;
}

int* Extender(int *num, int n, int nuevo){
    int *Resul = calloc(nuevo, sizeof(int));
    for(int i=0; i<n; i++)
        Resul[nuevo - n + i] = num[i];
    return Resul;
}

int* Multiplicacion(int *num1, int *num2, int n) {
    //Caso base unitario, la multiplicacion de esos dos numeros es de tamano 2
    if (n == 1) {
        int *res = (int*)malloc(2*sizeof(int));  
        res[0] = (num1[0] * num2[0]) / 10;
        res[1] = (num1[0] * num2[0]) % 10;
        return res;
    }

    //Caso base entre 1 a 4 por problemas de recursividad
    if (n <= 4) {
        int *res = (int*)calloc(2*n, sizeof(int));
        //Multiplicamos y guardamos en crudo en cada celda
        for (int i=n-1; i>=0; i--)
            for (int j=n-1; j>=0; j--)
                res[i+j+1] += num1[i]*num2[j];
        //Ahora si sumamos los acarreos que se fueron acumulando
        for (int k=2*n-1; k>0; k--) {
            res[k-1] += res[k]/10;
            res[k] %= 10;
        }
        return res;
    }

    // Si n es impar se rellena con un 0
    if (n % 2 != 0) {
        int *a = Extender(num1, n, n+1);
        int *b = Extender(num2, n, n+1);
        int *r = Multiplicacion(a, b, n+1);
        int *Resul = (int*)malloc(2*n*sizeof(int));
        for (int i = 0; i < 2*n; i++)
            Resul[i] = r[i+2];                     // se descartan los 2 ceros sobrantes
        free(a); free(b); free(r);
        return Resul;
    }

    int mitad = n/2;
    int *P1 = Multiplicacion(num1, num2, mitad);               // P1=num1_iz * num2*iz : n digitos 
    int *P2 = Multiplicacion(num1+mitad, num2+mitad, mitad);   // P2=num1_de * num2_de : n digitos 
    int *SA = SumaArr(num1, num1+mitad, mitad);                // SA=num1_de + num1_iz : mitad+1 digitos 
    int *SB = SumaArr(num2, num2+mitad, mitad);                // SB=num2_de + num2_iz : mitad+1 digitos
    int *P3 = Multiplicacion(SA, SB, mitad+1);                 // P3= SB * SA          : n+2 digitos 

    // Alineamos todo a n+2 digitos y restamos
    int *P1e = Extender(P1, n, n+2);
    int *P2e = Extender(P2, n, n+2);
    int *R1  = RestaArr(P3, P1e, n+2);                         // P3 - P1
    int *R2  = RestaArr(R1, P2e, n+2);                         // P3 - P1 - P2 : n+1 digitos

    int *B1 = RecorrerIz(P1, n, n);                            // P1 * 10^n               : 2n digitos 
    int *B2s = RecorrerIz(R2+1, n+1, n/2);                     // (P3 - P1 - P2)*10^mitad : n+1+mitad digitos
    int *B2  = Extender(B2s, n+1+mitad, 2*n);                  //          lo de arriba   : 2n digitos 
    int *P2f = Extender(P2, n, 2*n);                           // P2                      : 2n digitos

    int *S1 = SumaArr(B1, B2, 2*n);                            // 2n+1 digitos
    int *S2 = SumaArr(S1+1, P2f, 2*n);                         // 2n+1 digitos

    int *Resul = (int*)malloc(2*n*sizeof(int));
    for (int i=0; i<2*n; i++)
        Resul[i] = S2[i+1]; 

    free(P1); free(P2); free(SA); free(SB); free(P3);
    free(P1e); free(P2e); free(R1); free(R2);
    free(B1); free(B2s); free(B2); free(P2f); free(S1); free(S2);
    return Resul;
}

int SiguientePotenciaDe2(int n1, int n2) {
    int max = n1 > n2 ? n1 : n2;
    int pot = 1;
    while (pot < max) {
        pot *= 2;
    }
    return pot;
}

void ImprimirSinCeros(int *arr, int n){
    for(int i=0; i<n; i++){
        
    }
}

int* RellenarCeros(const char *num, int n, int nPotencia) {
    int *numFinal = malloc(nPotencia * sizeof(int));
    if (numFinal == NULL) {
        return NULL;
    }
    int j = nPotencia - n;

    for (int i = 0; i < j; i++) {
        numFinal[i] = 0;
    }

    for (int i = j, m = 0; i < nPotencia; i++, m++) {
        numFinal[i] = num[m] - '0';
    }
    return numFinal;
}

int main() {
    char text1[1000], text2[1000]; //Numeros de 1k digitos
    int n1, n2;

    printf("Algoritmo de multiplicacion de enteros largos\n");
    printf("Ingrese el primer numero a multiplicar: ");
    scanf("%s", text1);
    printf("Ingrese el segundo numero a multiplicar: ");
    scanf("%s", text2);

    n1 = (int)strlen(text1);
    n2 = (int)strlen(text2);

    int nPotencia = SiguientePotenciaDe2(n1, n2);
    int *num1 = RellenarCeros(text1, n1, nPotencia);
    int *num2 = RellenarCeros(text2, n2, nPotencia);

    printf("\nNumero 1: ");
    for (int i = 0; i < nPotencia; i++) {
        printf("%d", num1[i]);
    }

    printf("\nNumero 2: ");
    for (int i = 0; i < nPotencia; i++) {
        printf("%d", num2[i]);
    }

    clock_t inicio = clock();
    int *resultadoFinal = Multiplicacion(num1, num2, nPotencia);
    clock_t fin = clock();
    double tiempo = ((double)(fin - inicio) / CLOCKS_PER_SEC) * 1000.0;

    printf("\nResultado:");
    for (int i = 0; i < nPotencia*2; i++) {
        printf("%d", resultadoFinal[i]);
    }

    printf("\nTiempo de ejecucion: %.15f ms\n", tiempo);

    free(num1); free(num2); free(resultadoFinal);

    return 0;
}
