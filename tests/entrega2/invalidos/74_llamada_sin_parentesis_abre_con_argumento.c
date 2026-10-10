# Expectativa: Error 20: Falta ( #
# Prueba: llamada sin ( pero con argumento y ) : el argumento y el ) se consumen como parte de #
# la llamada, sin errores en cascada ni chequeo de parametros #

int g(int a) { return a; }

void main() {
    int x;
    x = g x) + 1;
}
