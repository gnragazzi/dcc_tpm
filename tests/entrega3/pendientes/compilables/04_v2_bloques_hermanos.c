# Requiere V2 (cout) #
# Expectativa: las variables de bloques hermanos no pisan a las de main ni entre si #
# Prueba: dos bloques hermanos declaran variables y despues se lee una local de main #

void main()
{
    int m = 5;
    {
        int a = 1;
        cout << a << " ";
    }
    {
        int b = 2;
        int c = 3;
        cout << b << " " << c << " ";
    }
    cout << m;
}
