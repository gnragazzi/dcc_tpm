# Expectativa: imprime ok #
# Prueba: un while infinito en una rama no ejecutada nunca corre #

void main()
{
    if (0) while (1) cout << "x";
    cout << "ok";
}
