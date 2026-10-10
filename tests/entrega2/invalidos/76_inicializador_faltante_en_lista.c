# Expectativa: Error 62 y Error 77 en cada declaracion; ademas Error 76 en arr13, arr15 y arr17 #
# Prueba: lista de inicializadores con una constante faltante al principio, en el medio o al final: #
# la posicion vacia tiene tipo error, asi que siempre se reporta 77 (devolucion 2da entrega, punto 5) #

int arr12[3] = {,1,2};
int arr13[3] = {,1,2,3};
int arr14[3] = {1, ,2};
int arr15[3] = {1, ,2,3};
int arr16[3] = {1,2,};
int arr17[3] = {1,2,3,};

void main() { }
