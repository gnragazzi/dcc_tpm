# Expectativa: imprime ab #
# Prueba: un if como ultima proposicion de bloques anidados #

void main()
{
    {
        {
            if (1) cout << "a";
        }
        if (0) cout << "x"; else cout << "b";
    }
}
