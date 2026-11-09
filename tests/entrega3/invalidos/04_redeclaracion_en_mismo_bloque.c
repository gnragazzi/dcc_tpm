# Expectativa: Error 72: Identificador ya declarado y no se genera .o #
# Prueba: dos declaraciones con el mismo nombre dentro del mismo bloque anidado #

void main()
{
    {
        int c;
        char c;
    }
}
