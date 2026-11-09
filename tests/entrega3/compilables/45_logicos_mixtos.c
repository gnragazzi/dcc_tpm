# Expectativa: imprime 1 0 1 0 1 1 0 #
# Prueba: &&, || y ! con operandos de los tres tipos #

void main()
{
    cout << (0.5 && 1) << " " << (0.0 || 0) << " " << !0.0 << " " << !'a' << " " << (1 && 2 && 3) << " " << (0 || 0 || 7) << " " << ('a' && 0.0);
}
