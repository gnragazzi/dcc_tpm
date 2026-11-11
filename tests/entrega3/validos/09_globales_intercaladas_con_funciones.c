# Expectativa: sin errores, Warning 36 y no se genera .o #
# Prueba: globales intercaladas con funciones antes y despues de main #

int g = 1;
void f() { g = g + 1; }
int h = 2;
void f2() { h = h + g; }
void main()
{
    cout << g << h;
}
void f3() { }
