# Expectativa: 5 errores del tipo "Error 21: Falta )" #
# Prueba: Omision de parentesis de cierre en las 5 producciones de la BNFE: #
# 1. Definicion de funcion: void fdef(int x ... #
# 2. Factor (expresion parentizada): a = (b + 1; #
# 3. Llamada a funcion: fllam(a; #
# 4. Proposicion de seleccion: if(a > 0 ... #
# 5. Proposicion de iteracion: while(a < 10 ... #

void fdef(int x
{
}

void fllam(int x)
{
}

void main()
{
    int a;
    int b;

    a = (b + 1;

    fllam(a;

    if(a > 0
    {
        a = 10;
    }

    while(a < 10
    {
        a = a + 1;
    }
}
