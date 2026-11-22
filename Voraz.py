import random

def Arreglo_numerios_aleatorios(n):
    arreglo = []
    for i in range(n):
        arreglo.append(random.randint(0, 20))
    return arreglo

def Ordenar_arreglo(arreglo):
    return sorted(arreglo, reverse=True)

def Encontrar_conjunto(arreglo_ordenado):
    suma_total = sum(arreglo_ordenado)
    suma_optima = 0
    
    for i in range(len(arreglo_ordenado)):
        suma_optima += arreglo_ordenado[i]
        suma_restante = suma_total - suma_optima
        
        if suma_optima > suma_restante:
            return arreglo_ordenado[:i+1], arreglo_ordenado[i+1:]

    return arreglo_ordenado, []
            

print(f"Ingresa el tamaño del arreglo:\n")
n = int(input())
arreglo = Arreglo_numerios_aleatorios(n)
print(f"Arreglo generado: {arreglo}\n")
arreglo_ordenado = Ordenar_arreglo(arreglo)
print(f"Arreglo ordenado descendente: {arreglo_ordenado}\n")
conjunto1, conjunto2 = Encontrar_conjunto(arreglo_ordenado)
print(f"Conjunto encontrado: {conjunto1} | Total: {len(conjunto1)} elementos | Suma: {sum(conjunto1)}\n")
print(f"Conjunto restante: {conjunto2} | Total: {len(conjunto2)} elementos | Suma: {sum(conjunto2)}\n")