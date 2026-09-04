# Decisiones de diseño — Entrega 1

> Curar desde la Bitácora de decisiones antes de empaquetar. Esto es lo que se sube a
> Classroom junto con el ejecutable y los fuentes (la guía general lo pide como
> "descripción puntual de las decisiones que ha tomado para abordar la etapa").

# Capa 0 · Contrato

## T1

Implementación del procedimiento `test(set c1, set c2, int ne)` para la estrategia de recuperación antipánico (Consigna 5).

- **Ubicación del procedimiento:** Se implementó en `src/util.c` y se declaró su firma en `src/util.h`. Se ubicó allí por ser una función de utilidad general del parser independiente de las producciones gramaticales específicas.
- **Claridad semántica y no mutación:** Se adaptó el pseudocódigo clásico de la teoría (`c1 = c1 | c2`) utilizando una variable local explícita `set conjunto_sincronizacion = c1 | c2;`. Esto evita mutar los parámetros de entrada por valor y mejora la legibilidad del código.
- **Estrategia antipánico:** Si el símbolo actual (`lookahead`) no pertenece al conjunto esperado $c_1$, se emite el error sintáctico $ne$ mediante `error_handler(ne)` y se descartan tokens con `scanner()` en un bucle `while` hasta que aparezca un símbolo perteneciente a `conjunto_sincronizacion` para reanudar el análisis.
- **Detección de `CEOF` y Error 36:** Se decidió no incluir `CEOF` ciegamente en `conjunto_sincronizacion` para obligar a una rigurosa propagación del `folset` desde la raíz. Sin embargo, para evitar bucles infinitos en caso de que una función intermedia omita el `folset`, el bucle `while` chequea `if(lookahead_in(CEOF))` y aborta inmediatamente con `error_handler(36)` (`"folset mal formado"`) y `exit(1)`. Esto cumple con el principio *Fail-Fast* y utiliza el rango de errores personalizados (36-39) asignado por la cátedra.

## T2

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

## T3

## T4

## T5

### La pregunta de fondo

**¿Cuánto confía un procedimiento en su llamador?**

Todas las reglas de abajo son consecuencias de esa única decisión. Lo importante no es que el
criterio sea el óptimo, sino que sea **uniforme** y justificado.

---

### Reglas

#### 1. El guardián no reemplaza al test

Entendemos por guardian una condición en la que se chequea un lookahead, fuera de untest. Un `if(lookahead_in(F_X)) X();` en el llamador **no reporta ni resincroniza**: solo saltea. No
es recuperación, es omisión.

Se usa **únicamente** donde la BNFE dice `[ ]` o `{ }` — es decir, donde la ausencia del
elemento es legal. Poner un guardián sobre un elemento obligatorio se traga el error: sobre
`α * ) β`, con `if(lookahead_in(F_FACTOR)) factor();` en `termino()`, el compilador acepta
`(a * )` como programa válido.

Los `switch` con `default` son otra cosa: la BNFE ahí describe alternancia sin λ, así que el
`default` es un caso de error legítimo. Misma forma en C, semántica opuesta.

Y hay una tercera forma: el `switch` **sin** `default` (`declarador_init`). Es un guardián
disfrazado — codifica una alternancia **con** λ, donde caer fuera de todos los `case` es la
derivación vacía, no un error. No se le agrega un `default` que reporte.

#### 2. Test inicial: dónde va y qué lleva `c1`

Criterio de la teoría: un procedimiento lleva test inicial cuando **se lo invoca al menos una vez
en forma incondicional** y **la primera sentencia de su cuerpo no es una invocación a
procedimiento**. Basta un solo call site sin garantía; la segunda condición es la delegación de
la regla 3.

- `proposicion_e_s` se invoca solo desde el `switch` de `proposicion()`, que ya garantizó
  `CIN | COUT` → **no lleva** test inicial.
- `variable` se invoca sin guardián desde `proposicion_e_s` → **lleva**.
- `factor` se invoca sin guardián desde `termino` → **lleva**.

**`c1` del test inicial.** Depende de si el no terminal es anulable:

- `X ↛ λ` → `c1 = FIRST(X)`.
- `X → λ` → `c1 = FIRST(X) ∪ folset`. El test deja de preguntar *"¿empieza X acá?"* y pasa a
  preguntar *"¿estoy parado en un lugar del que este procedimiento puede seguir?"*.

Los dos anulables de esta gramática se invocan **sin** guardián, así que ambos llevan test
inicial y ambos entran por la segunda cláusula:

- `unidad_traduccion ::= { <declaraciones> }`, invocado desde `main`. Es donde vive el error 40.
- `declarador_init`, invocado sin guardián desde `declaracion_variable` y desde
  `lista_declaraciones_init` (dos veces). Es donde vive el error 47.

Con `c1 = FIRST(X)` a secas, `int a;` marcaría error en `declarador_init` —el lookahead es `;`—
y un archivo vacío marcaría error en `unidad_traduccion`: violación directa de la consigna 11.
Es exactamente el caso que pregunta la guía práctica 8: `CPYCOMA` es alternativa válida antes de
`declaracion_variable()` **porque** `declarador_init` deriva λ.

#### 3. Delegación: solo si los FIRST son iguales

Un procedimiento que arranca llamando a otro puede delegarle su test inicial, pero **solo si
`FIRST(delegado) == FIRST(delegante)`**.

- `expresion` → `expresion_simple`: FIRST iguales → **delega**.
- `expresion_simple` → `termino`: `FIRST(expresión simple) ⊋ FIRST(término)` por el `[ + | - ]`
  → **no delega**, carga el test.
- Caso extremo de lo mismo: si el delegado es **anulable** no hay ningún símbolo obligatorio en
  su entrada, así que el delegante no puede descargar su test en él. `declaracion_variable` no
  puede delegar en `declarador_init`.

Que un no terminal sea anulable **no** significa que no lleve test: significa que su `c1` se
construye por la segunda cláusula de la regla 2. `declarador_init` lleva test inicial y es
anulable. Son cosas independientes.

Esta regla es más estricta que el criterio de la teoría, que solo mira si la primera sentencia es
una invocación a procedimiento. Coinciden en toda la gramática salvo en `declaracion_variable`,
donde la diferencia no llega a disparar porque se lo invoca condicionalmente.

#### 4. `c1` y `c2` son cosas distintas

- **`c1`** = qué debería haber acá. Es lo único que decide si se **reporta**.
- **`c2`** = dónde además es seguro frenar. Solo acota **cuánto se saltea**.

Nada de lo que esté en `c2` reporta ni suprime un error. Frenar en un símbolo no es aceptarlo:
el error ya se reportó, y `c2` solo evita tirar a la basura más entrada de la necesaria.

#### 5. `c2` del test inicial

`c2 = folset heredado ∪ puntos de recuperación internos del propio procedimiento`.

En un no terminal anulable `folset ⊆ c1` por la regla 2, así que `c2` se reduce a los puntos
internos. No es una decisión ni cambia la semántica: `test` hace `c1 := c1 + c2` antes de
saltear, la unión es la misma se escriba donde se escriba.

Un punto interno es una posición del cuerpo donde se puede retomar aceptando que se perdió un
prefijo. Es admisible **solo si al frenar ahí el prefijo perdido queda identificado sin
ambigüedad**. Restricción adicional de la teoría: *para un no terminal con más de una alternativa
los posibles puntos de reconfiguración de cada alternativa deben ser disjuntos*.

- **Sí**: la cola de la propia producción. En `declaracion_parametro ::= <especificador de tipo>
  [ & ] ident [ [ ] ]`, frenar en `&` o en `ident` significa inequívocamente que faltó el tipo:
  con `void f(& a)` se reporta un solo error y el parámetro se recupera entero. Ojo que este
  procedimiento **delega** (regla 3), así que esos símbolos no llegan como `c2` propio sino
  dentro del **folset** que recibe `especificador_tipo` — que por la regla 6 es el mismo
  conjunto. La categoría "punto interno" queda para los procedimientos que sí cargan el test.
- **No**: los símbolos de cierre (`)`, `]`, `}`). Pueden pertenecer a una construcción
  envolvente, y cuando efectivamente pertenecen ya llegan por el folset heredado. Agregarlos
  fabrica estructura: con `cout << * ) ;`, meter `CPAR_CIE` en el `c2` de `factor` hace que el
  parser consuma un paréntesis que nunca se abrió.
- **No**: en alternancias puras (`factor`), donde el test corre antes de elegir rama y por lo
  tanto no se puede atribuir el punto interno a ninguna. Ahí `c2 = folset`.

#### 6. Test final y construcción del folset

Test final = **`test(folset, ∅, ne)`**. Sin `FIRST(X)` en `c2`.

La formulación clásica `test(folset, FIRST(X), ne)` es de Wirth, donde los follower sets se
calculan groseramente y `FIRST(X)` es una red de seguridad contra saltear de más. La consigna 8
pide folsets **precisos por call site**; con folsets precisos la red sobra y estorba.

El **folset acumula**, y "lo que sigue en ese call site" se lee **amplio**: no el símbolo
inmediatamente siguiente, sino el FIRST de **toda la cola** de la producción a partir de ese
punto, más lo heredado del llamador. Es la forma de la teoría:

```
X ::= if E then S else S fi

    E(folset + {then, else, fi} + FIRST₁(S));
    S(folset + {else, fi} + FIRST₁(S));
    S(folset + {fi});
```

`E` recibe `then`, pero también `else`, `fi` y `FIRST(S)`: todo lo que puede aparecer después de
`E` si lo que hay en el medio falta.

Por qué importa: `proposicion_iteracion ::= while ( <expresión> ) <proposición>`. Con la lectura
estrecha `folset(expresion) = CPAR_CIE | heredado`, y sobre `while (a < b { ... }` el test final
de `expresion` saltea el bloque entero buscando un `)` que no está. Con la amplia
`folset(expresion) = CPAR_CIE | F_PROPOSICION | heredado`: frena en `{`, el test final pasa en
silencio y el error lo reporta `match(CPAR_CIE, 21)` con el mensaje correcto. Cuanto más preciso
el folset, más sobreviven los mensajes específicos y menos aparecen los genéricos.

Ejemplo, la primera llamada a `expresion()` dentro de `proposicion_e_s`:

```
folset = CSHL | CPYCOMA | F_EXPRESION | folset(proposicion_e_s)
```

`F_EXPRESION` está ahí por la regla 7.

#### 7. Iteraciones: test antes del bucle y al final del cuerpo (consigna 12)

La BNFE viene colapsada: donde la BNF tiene `X ::= A <Xtail>` / `<Xtail> ::= λ | A <Xtail>`, el
parser tiene `A { A }`. La teoría dice qué hace falta para que las dos formas se comporten igual:

> Se debe colocar un test antes de la repetición y como última sentencia del cuerpo de la
> iteración.

Vale para **todo** `{ }`, tenga separador o no. Sin el test al final del cuerpo, un error dentro
de una iteración no resincroniza a la iteración siguiente: sale del bucle y lo agarra el test
final, que ya está afuera. Sobre `int a; xyz int b;` el test final de `unidad_traduccion`
(`c1 = CEOF`) saltea hasta fin de archivo y se come `int b;`: un error reportado, medio archivo
descartado en silencio. Aplica igual a `lista_proposiciones` y a `lista_declaraciones`, que
tampoco tienen separador.

**Caso particular: separador olvidable.** Cuando la condición del `{ }` es un separador fácil de
olvidar, además se ensancha el guardián:

```c
while(lookahead_in(SEPARADOR | F_CUERPO))
{
	if(lookahead_in(SEPARADOR))
		scanner();
	else
		error_handler(ne_falta_separador);

	cuerpo(folset);
}
```

**Consecuencia sobre la regla 6:** `F_CUERPO` pasa a ser parte de lo que legítimamente sigue al
cuerpo en ese call site, así que entra en **el folset** que se le pasa — no en `c2`.

Sin esto, sobre `void f(int a int b)` el test final de `declaracion_parametro` se come `int b`
entero antes de que el bucle pueda verlo. Con esto: un error ("falta coma") y recuperación
completa.

Cuentan como olvidables los **separadores de puntuación**: la `,` en
`lista_declaraciones_param`, `lista_declaraciones_init`, `lista_inicializadores` y
`lista_expresiones`; `>>` y `<<` en `proposicion_e_s`. **Los operadores no** — no se olvida un
`*` como se olvida una coma.

#### 8. Forzar entrada (consigna 10)

Cuando un test inicial ya verificó el primer símbolo, el cuerpo **no lo vuelve a verificar**:

```c
test(CIDENT, c2, ne);
if(lookahead_in(CIDENT))       /* en vez de match(CIDENT, ne2) */
	scanner();
```

El `test` se queda con la responsabilidad de reportar; el cuerpo consume **condicional y
silenciosamente**. Un `scanner()` incondicional se comería el símbolo cuando el test frenó en
`c2`; un `match` reportaría dos veces lo mismo.

**Corolario — los `default:` de los `switch` no reportan**, *en los procedimientos que llevan
test inicial*. Después del test, el lookahead está en `c1 ∪ c2`. Si está en `c1`, alguna rama
matchea. Llegar al `default` significa que está en `c2 \ c1`, o sea que **el test ya reportó**.
Queda `default: break;`.

Dos excepciones, por lo mismo leído al revés:

- `proposicion_e_s` **no** lleva test inicial (regla 2), así que su `default` conserva el
  `error_handler(29)`.
- `declarador_init` no tiene `default` y no se le agrega (regla 1): caer fuera de los `case` es
  la derivación λ, no un error.

La otra mitad de la consigna 10 —reemplazar `scanner()` por `match()`— aplica al caso opuesto:
los `scanner()` a ciegas que consumen un símbolo que el llamador garantizó (`case CIN: scanner();`
en `proposicion_e_s`, los cuatro `case` de `especificador_tipo`).

#### 9. Salida temprana cuando el test frenó en el folset

Al salir de un test inicial el lookahead puede estar en cuatro estados. Tres piden la misma
acción; el cuarto no:

| Estado al salir del test | Acción |
|---|---|
| no hubo error → lookahead ∈ `FIRST(X)` | correr el cuerpo |
| hubo error y resincronizó a algo de `FIRST(X)` | correr el cuerpo: se perdió un prefijo, se retoma `X` entero |
| hubo error y resincronizó a un punto interno | correr el cuerpo: lo previo al punto se saltea solo (regla 8) |
| hubo error y resincronizó al folset heredado | **retornar**: nada del cuerpo aplica |

Como los tres primeros coinciden, el procedimiento **no necesita saber si el test reportó**. Le
alcanza con mirar el lookahead contra dos conjuntos que él mismo armó:

```c
void X(set folset)
{
	test(F_X, folset | INTERNOS_X, ne);

	if(!lookahead_in(F_X | INTERNOS_X))
		return;

	/* cuerpo */
}
```

`test` no cambia de firma ni devuelve nada. La guarda va **solo** en los procedimientos que
llevan test inicial.

**Esto no es pánico: no descarta un solo token.** Por el requisito A de la teoría —todo
procedimiento subordinado hereda el folset del subordinante— cualquier procedimiento anidado en
el cuerpo de `X` recibe un folset que contiene a `folset(X)` y por lo tanto contiene al
lookahead: su test lo encuentra en `c1 ∪ c2` en la primera comparación y saltea cero tokens, y
todo `match` obligatorio falla sin avanzar. Correr el cuerpo y no correrlo dejan **el mismo
estado del parser y el mismo lookahead**; lo único que cambia es la cantidad de mensajes. Se
saltea código, no entrada.

Bajo los placeholders de `T2` la guarda es inerte: con `F_X = LLONG_MAX` el `lookahead_in` da
siempre verdadero y el cuerpo corre siempre, igual que hoy.

---

### Decisión sobre la cascada de errores

Las reglas 1 a 8 no evitan por sí solas que un símbolo inválido dispare tests en varios niveles
mientras se desarma la pila. Sobre `cout << ) ;`: el test de `expresion_simple` reporta parado en
`)` y resincroniza hasta el `;`, el cuerpo sigue corriendo, y el test de `factor` reporta un
segundo error sobre ese mismo `;`.

El problema real no es *"dos errores sobre el mismo token"*: es que **el cuerpo del procedimiento
sigue ejecutándose después de que el test resincronizó**. La regla 9 lo corta en el origen —
`expresion_simple` retorna y `factor` nunca llega a correr.

Verificación:

| Entrada | Errores | Por qué |
|---|---|---|
| `cout << ) ;` | 1 | `expresion_simple` retorna parado en el `;`; `factor` no corre |
| `cout << ;` | 1 | falta una expresión obligatoria, y **se reporta** |
| `cout << ) << ) ;` | 2 | dos errores en posiciones distintas; el bucle de `<<` reentra |
| `void f(& a)` | 1 | `especificador_tipo` reporta y retorna; `declaracion_parametro` recupera el parámetro entero |

Lo que la regla 9 **no** garantiza es exactamente un error por token: cuando `X` abandona, un
`match` obligatorio posterior en el llamador puede reportar. Ese suele ser un error real y
distinto (falta un `;`, falta un `)`). Si en los lotes resulta ser ruido, se trata como consigna
14 en un ticket `fix/*` propio.

#### Alternativas descartadas

- **Regla de un error por posición**: contador global de tokens en `scanner()` y descarte en
  `error_handler` cuando dos reportes caen en el mismo token. Filtra el síntoma en vez de la
  causa, y el filtro tiene que vivir en `error_handler`, que es también el flush por línea
  (`COD_IMP_ERRORES`, invocado desde el `.lex` en cada `\n`) y el canal de los errores léxicos
  1 a 5. Además, como el test genérico reporta antes que el `match` específico, el mensaje que
  sobrevive es el genérico: sobre `while (a < b {` se pierde el 21 ("Falta )") a favor de un 69.
  Amplía el alcance de `T1` y de `T4`.
- **Flag de pánico global** (silenciar errores hasta consumir con éxito). Hace que el reporte de
  un error dependa de estado global que atraviesa todo el parseo: dos lotes con el mismo
  fragmento local pueden dar salidas distintas, y los `.esperado` del CI dejan de ser estables.
  Además pierde errores reales: con `cout << ) << ) ;` reporta uno solo.
- **`test` devuelve dónde frenó.** Innecesario: el procedimiento tiene los conjuntos y decide
  solo. Cambiar la firma tocaría `T1` y los 29 call sites de `T3`.
- **No hacer nada.** Correcto y determinista, pero 2 o 3 líneas por error en cada `.esperado`.

**Alcance.** La regla 9 es una línea por procedimiento, dentro del bloque que cada ticket `N` ya
reescribe. No toca `test` (`T1`), ni `util.c` ni `error.c` (`T4`), ni la migración mecánica
(`T3`). La teoría no trae ningún mecanismo anticascada: esto es una decisión de diseño propia y
se justifica como tal en la entrega.

---

### Fuera del alcance de esta decisión

- **Numeración de errores** (consigna 2): se resuelve por procedimiento, en cada ticket de
  instrumentación.
- **Cálculo de los conjuntos** (consignas 3 y 4): tickets `F1`–`F4`.
- **Casos donde el esquema no alcanza** (consignas 14 y 15): emergen de los lotes de prueba y se
  tratan como tickets `fix/*` propios, cada uno con su justificación.

## T6

# Capa 1 · FIRST1

## F1

## F2

## F3

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

## F4

# Capa 2 · Instrumentación

## N1

## N2

## N3

## N4

## N5

## N6

## N7

## N8

## N9

## N10

## N11

# Capa 3 · Lotes

## L1

## L2

## L3
Creación del lote de prueba válido `tests/entrega1/validos/l3_llamadas_funciones.txt`:
- **Cobertura de llamadas a funciones:** Valida definiciones y llamadas a funciones sin parámetros, con parámetros por valor y por referencia (`&`), arreglos (`[]`), invocaciones anidadas (`fdup(fdup(b))`), llamadas dentro de expresiones aritméticas y condicionales (`if`, `while`, `cout`).
- **Convención del prefijo `'f'`:** En la 1ª entrega (sin Tabla de Símbolos), el parser bifurca identificadores en `factor()` hacia `llamada_funcion()` si `sbol->lexema[0] == 'f'`. Todas las funciones invocadas respetan el prefijo `'f'` para validar la sintaxis de llamadas sin activar la bifurcación a variables.
- **Sintaxis estricta del scanner:** Se respetan los límites del scanner (identificadores $\le 8$ caracteres, solo letras y dígitos, indentación con espacios).

## L4

## L5

## L6

## L7

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

Creación de los lotes de prueba inválidos para omisión de llave de cierre `}` (`tests/entrega1/pendientes/invalidos/04_falta_llave_cierre*.c`) y sus archivos `.esperado`:
- **Cobertura sistemática de producciones BNFE que utilizan `}`:**
  - *Proposición compuesta (`<proposición compuesta>`):* `04_falta_llave_cierre.c` (omisión de `}` al final de bloque / función). Es un caso crítico de recuperación antipánico que debe sincronizar contra el folset heredado (`CEOF`) sin entrar en bucle infinito.
  - *Lista de inicializadores de arreglo (`<declarador init>`):* `04_falta_llave_cierre_init.c` (`int a[] = {1, 2, 3;` omitiendo `}`). Valida la sincronización al cierre de la lista de constantes inicializadoras.
- **Comportamiento esperado:** Reporte del `Error 25: Falta }` (definido en `error.c:37`) en cada archivo de forma aislada.
- **Ubicación en pendientes:** Permanecen en `pendientes/invalidos/` hasta que la instrumentación de `proposicion_compuesta()` (`N4`), `declarador_init()` (`N10`), `lista_inicializadores()` (`N11`) y el fix `T4` estén integrados en `develop`.

## L9

Creación de los lotes de prueba inválidos para especificador de tipo no soportado (`tests/entrega1/pendientes/invalidos/05_tipo_invalido*.c`) y sus archivos `.esperado`:
- **Cobertura sistemática de producciones BNFE que utilizan `<especificador de tipo>`:**
  - *Declaración global (`<declaraciones>`):* `05_tipo_invalido_global.c` (`double glob;`). Valida el rechazo de tipo no permitido en la raíz del programa antes del identificador global.
  - *Declaración de parámetros (`<declaración de parámetro>`):* `05_tipo_invalido_param.c` (`void fshow(double dato)`). Valida el rechazo de tipo no soportado en la lista de parámetros formales.
  - *Declaración local en proposición compuesta (`<declaración>`):* `05_tipo_invalido.c` (`double x;` dentro de `main()`). Valida el rechazo en variables locales.
- **Comportamiento esperado:** Reporte del `Error 18: Tipo no definido` (definido en `error.c:30`) en cada contexto, aislando las pruebas en archivos independientes.
- **Ubicación en pendientes:** Permanecen en `pendientes/invalidos/` hasta que la instrumentación de `especificador_tipo()` (`N7`), `declaracion_parametro()` (`N9`), declaraciones locales (`N11`) y el fix `T4` estén integrados en `develop`.

## L10

## L11

## L12

## L13

## L14

# Capa 5 · Cierre

## C1

## C2

## C3

## C4

# Justificación

## Casos donde el esquema de recuperación antipánico no alcanzó y cómo se reconfiguró
