# Expectativa: 5 errores del tipo "Error 64: Falta , " #
# Prueba: Omisión de coma en las 5 producciones de la BNFE: #
# 1. Declaración de variable (global): int a = 1 b = 2; #
# 2. Lista de declaraciones de parámetros: void f(int a int b) #
# 3. Lista de declaraciones init (local): int x y; #
# 4. Lista de inicializadores: int arr[2] = {1 2}; #
# 5. Lista de expresiones (llamada): f(x y); #

int a = 1 b = 2;

void f(int p int q)
{
    p = q;
}

void main()
{
    int x y;
    int arr[2] = {1 2};

    f(x y);
}
