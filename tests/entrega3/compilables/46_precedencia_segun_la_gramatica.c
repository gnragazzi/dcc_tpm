# Expectativa: imprime 0 1 0 11 1 0 -5 1 9 1 1 #
# Prueba: && tiene la precedencia de *, || la de +, los relacionales encadenan de izquierda a derecha y ! toma una expresion completa #

void main()
{
    cout << (1 + 2 * 3 < 2 * 5 && 4 > 3 || 0) << " ";
    cout << (1 < 2 < 3) << " " << (3 > 2 > 1) << " " << 2 + 3 * 4 - 6 / 2 << " ";
    cout << (1 || 0 && 0) << " " << !0 + 5 << " " << -2 * 3 + 1 << " " << -2 + 3 << " ";
    cout << 10 / 3 * 3 << " " << (2 * 3 && 0 + 1) << " " << (1 + 1 == 2);
}
