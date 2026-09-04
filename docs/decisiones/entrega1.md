# Decisiones de diseño — Entrega 1

> Curar desde la Bitácora de decisiones antes de empaquetar. Esto es lo que se sube a
> Classroom junto con el ejecutable y los fuentes (la guía general lo pide como
> "descripción puntual de las decisiones que ha tomado para abordar la etapa").

## Decisiones tomadas

Un `###` por ticket para que cada PR toque sólo su bloque y no genere conflictos de
merge con otro ticket en curso.

### Capa 0 · Contrato

#### T1

Implementación del procedimiento `test(set c1, set c2, int ne)` para la estrategia de recuperación antipánico (Consigna 5).

- **Ubicación del procedimiento:** Se implementó en `src/util.c` y se declaró su firma en `src/util.h`. Se ubicó allí por ser una función de utilidad general del parser independiente de las producciones gramaticales específicas.
- **Claridad semántica y no mutación:** Se adaptó el pseudocódigo clásico de la teoría (`c1 = c1 | c2`) utilizando una variable local explícita `set conjunto_sincronizacion = c1 | c2;`. Esto evita mutar los parámetros de entrada por valor y mejora la legibilidad del código.
- **Estrategia antipánico:** Si el símbolo actual (`lookahead`) no pertenece al conjunto esperado $c_1$, se emite el error sintáctico $ne$ mediante `error_handler(ne)` y se descartan tokens con `scanner()` en un bucle `while` hasta que aparezca un símbolo perteneciente a `conjunto_sincronizacion` para reanudar el análisis.
- **Detección de `CEOF` y Error 36:** Se decidió no incluir `CEOF` ciegamente en `conjunto_sincronizacion` para obligar a una rigurosa propagación del `folset` desde la raíz. Sin embargo, para evitar bucles infinitos en caso de que una función intermedia omita el `folset`, el bucle `while` chequea `if(lookahead_in(CEOF))` y aborta inmediatamente con `error_handler(36)` (`"folset mal formado"`) y `exit(1)`. Esto cumple con el principio *Fail-Fast* y utiliza el rango de errores personalizados (36-39) asignado por la cátedra.

#### T2

Header `parser.h` pre-poblado con los 30 `#define F_*` (no terminales BNFE, incluido
`F_RELACION`) y con los conjuntos de continuación que sólo la BNF nombra (los `<resto
X>` y los `<... opcional>` de las notas de `F2`/`F3`/`F4`), todos apuntando al mismo
placeholder.

- **Valor del placeholder.** `PLACEHOLDER` se define como `LLONG_MAX` (todos los bits
  salvo el de signo), no `0`. Si un placeholder queda sin reemplazar y llega a usarse
  en `test()`, `LLONG_MAX` fuerza una resincronización casi inmediata; `0` dejaría el
  conjunto de sincronización vacío, sin condición de corte para el loop de recuperación
  antipánico. El propio README ya documenta el riesgo (por eso el CI corre con
  timeout). Se prefiere fallo visible a cuelgue silencioso.
- **Convención de nombres.** Un único prefijo `F_*` para todo: tanto el FIRST de los 30
  no terminales de la BNFE como los conjuntos de continuación que sólo nombra la BNF.
  No se usa `C_*` (reservado a los terminales del scanner) ni un prefijo distinto para
  continuaciones.
- **Sin excepciones por cardinalidad.** Aun cuando el FIRST de una producción termina
  siendo un único terminal (ej. `<opref opcional>` → `&`), se mantiene el macro `F_*`
  en vez de referenciar el código `C_*` crudo desde `parser.c`. El F-ticket que calcule
  el valor real decide si lo expresa como unión o como alias directo a un `C_*`; lo que
  no cambia es que el macro exista siempre. Motivo: los 11 grupos `N` de Capa 2 no se
  coordinan entre sí (R2/R4) — una interfaz uniforme evita que cada uno deba verificar
  caso por caso si existe macro para la producción que necesita.

#### T3

#### T4

#### T5

#### T6

### Capa 1 · FIRST1

#### F1

#### F2

#### F3

Cálculo y definición en `src/conjuntos.h` de los conjuntos FIRST para la región de proposiciones y sus continuaciones (Consigna 3):

- **No terminales de proposiciones:**
  - `F_PROPOSICION_COMPUESTA`: `{` (`CLLA_ABR`).
  - `F_PROPOSICION_ITERACION`: `while` (`CWHILE`).
  - `F_PROPOSICION_SELECCION`: `if` (`CIF`).
  - `F_PROPOSICION_E_S`: `cin`, `cout` (`CIN | COUT`).
  - `F_PROPOSICION_RETORNO`: `return` (`CRETURN`).
  - `F_PROPOSICION_EXPRESION`: `(F_EXPRESION | CPYCOMA)`.
  - `F_PROPOSICION`: Unión de las 6 alternativas de proposición (`F_PROPOSICION_COMPUESTA | F_PROPOSICION_ITERACION | F_PROPOSICION_SELECCION | F_PROPOSICION_E_S | F_PROPOSICION_RETORNO | F_PROPOSICION_EXPRESION`).
  - `F_LISTA_PROPOSICIONES`: `(F_PROPOSICION)`.
- **Conjuntos de continuación:**
  - `F_ELSE_OPCIONAL`: `else` (`CELSE`).
  - `F_RESTO_PROP_IN`: `>>` (`CSHR`).
  - `F_RESTO_PROP_OUT`: `<<` (`CSHL`).
- **Decisión de diseño — Descarte de la regla R10 y adopción de composición de macros:**
  - Por acuerdo de equipo y revisión técnica, se descartó la regla R10 del roadmap (que exigía uniones literales crudas de terminales).
  - Se adoptó la **composición de macros**, reutilizando `F_EXPRESION` en `F_PROPOSICION_EXPRESION` y componiendo `F_PROPOSICION` a partir de los macros de sus producciones derivadas.
  - *Ventajas técnicas:*
    1. **Eliminación de duplicación (DRY):** Evita repetir manualmente la lista de terminales de expresión en múltiples definiciones.
    2. **Consistencia arquitectónica:** Alinea el diseño con `F2`, donde ya se había utilizado composición (`F_TERMINO (F_FACTOR)`, `F_EXPRESION_SIMPLE (CMAS | CMENOS | F_TERMINO)`).
    3. **Trazabilidad matemática:** Cada macro refleja directamente las ecuaciones de First de la teoría de compiladores ($\text{FIRST}(\langle\text{proposición expresión}\rangle) = \text{FIRST}(\langle\text{expresión}\rangle) \cup \{ ; \}$).
    4. **Mantenibilidad:** Cualquier ajuste futuro en las producciones elementales se propaga automáticamente a las capas superiores sin riesgo de desfasajes.

#### F4

### Capa 2 · Instrumentación

#### N1

#### N2

#### N3

#### N4

#### N5

#### N6

#### N7

#### N8

#### N9

#### N10

#### N11

### Capa 3 · Lotes

#### L1

#### L2

#### L3
Creación del lote de prueba válido `tests/entrega1/validos/l3_llamadas_funciones.txt`:
- **Cobertura de llamadas a funciones:** Valida definiciones y llamadas a funciones sin parámetros, con parámetros por valor y por referencia (`&`), arreglos (`[]`), invocaciones anidadas (`fdup(fdup(b))`), llamadas dentro de expresiones aritméticas y condicionales (`if`, `while`, `cout`).
- **Convención del prefijo `'f'`:** En la 1ª entrega (sin Tabla de Símbolos), el parser bifurca identificadores en `factor()` hacia `llamada_funcion()` si `sbol->lexema[0] == 'f'`. Todas las funciones invocadas respetan el prefijo `'f'` para validar la sintaxis de llamadas sin activar la bifurcación a variables.
- **Sintaxis estricta del scanner:** Se respetan los límites del scanner (identificadores $\le 8$ caracteres, solo letras y dígitos, indentación con espacios).

#### L4

#### L5

#### L6

#### L7

Creación del lote de prueba inválido `tests/entrega1/pendientes/invalidos/03_falta_parentesis_cierre.c` y su archivo `03_falta_parentesis_cierre.esperado`:
- **Cobertura integral de la BNFE:** El lote cubre exhaustivamente las 5 producciones de la gramática que utilizan paréntesis, omitiendo deliberadamente el paréntesis de cierre `)` en cada una:
  1. `<definicion_funcion>`: omisión de `)` tras la lista de parámetros (`void fdef(int x {`).
  2. `<factor>`: omisión de `)` en una expresión parentizada (`a = (b + 1;`).
  3. `<llamada_funcion>`: omisión de `)` tras la lista de expresiones (`fllam(a;`).
  4. `<proposicion_seleccion>`: omisión de `)` en la condición de `if` (`if(a > 0 {`).
  5. `<proposicion_iteracion>`: omisión de `)` en la condición de `while` (`while(a < 10 {`).
- **Convención de funciones e identificadores:** Se respeta el prefijo `'f'` en los nombres de funciones para satisfacer la bifurcación sintáctica en `factor()` de la 1ª entrega (`sbol->lexema[0] == 'f'`), y la longitud máxima de 8 caracteres en identificadores.
- **Comportamiento esperado:** Reporte secuencial de 5 instancias de `Error 21: Falta )` (una por cada producción afectada), garantizando una recuperación sintáctica limpia entre sentencias sin entrar en bucles infinitos ni desbordar la pila.
- **Ubicación en pendientes:** Permanece en `pendientes/invalidos/` hasta que los tickets de instrumentación `N2` (factor), `N3` (llamadas), `N5` (control de flujo: if/while), `N8` (definición de función) y la corrección `T4` (`error_handler`) estén completamente integrados en `develop`.

#### L8

#### L9

#### L10

#### L11

#### L12

#### L13

#### L14

### Capa 5 · Cierre

#### C1

#### C2

#### C3

#### C4

## Justificación

## Casos donde el esquema de recuperación antipánico no alcanzó y cómo se reconfiguró
