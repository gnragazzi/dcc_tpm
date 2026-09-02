# ucc — Práctico de Máquina, Diseño y Construcción de Compiladores (UNSL)

Compilador para un subconjunto de C++ (`ucc`), desarrollado en equipo a lo largo de 3 entregas.

## Estructura

- `src/` — fuentes del compilador, en un solo nivel (así lo espera el Makefile de
  cátedra: sin subcarpetas por módulo). La separación por módulo es por *naming*:
  `parser.*`, `error.*`, `util.*`, y lo que se sume en etapas siguientes (`ts.*`,
  `sistejec.*`).
- `tests/entregaN/{validos,invalidos}/` — lotes de prueba por etapa, activos en CI.
  `validos/` = programas sin errores sintácticos. `invalidos/` = programas con
  errores, para probar el esquema de recuperación antipánico.
- `tests/entregaN/pendientes/{validos,invalidos}/` — casos ya escritos para la
  etapa pero cuya feature todavía no está resuelta. CI no los escanea. Un PR de
  `feat/fix/*` que resuelve un caso lo promueve (`git mv`) a `validos/` o
  `invalidos/` como parte del mismo PR, para no depender de un mega-PR que
  resuelva toda la entrega junta.
- `tests/unit/` — tests unitarios de lógica pura (conjuntos FIRST/FOLLOW,
  `test(c1,c2,ne)`). No testear funciones del PDR acá: dependen de estado global
  compartido con el scanner y se validan mejor con los lotes de `tests/entregaN/`.
- `docs/decisiones/entregaN.md` — descripción de las decisiones tomadas en cada
  entrega (lo que pide Classroom junto al ejecutable y los fuentes). Se cura desde
  la Bitácora de decisiones, no se escribe de cero.
- `docs/informe_final.md` — informe a entregar tras la aprobación de la entrega 2.
- `docs/roadmap_entrega1.md` — plan de la 1ª entrega: cola de tickets, dependencias y
  reglas de operación. Se regenera junto con la planilla de seguimiento.
- `docs/roadmap_entrega1.md` — plan de la 1ª entrega: cola de tickets, dependencias y
  reglas de operación. Se regenera junto con la planilla de seguimiento.
- `scripts/empaquetar.sh` — arma el .zip de entrega.
- `scripts/crear_issues.py` — crea los labels y los issues del roadmap en GitHub.
- `scripts/crear_issues.py` — crea los labels y los issues del roadmap en GitHub.

## Compilar

    cd src
    make        # genera ./ucc
    make clean  # limpia objetos y el ejecutable

Nota: el Makefile de cátedra usa `-fcommon` en `CFLAGS`. Sin ese flag, `make` falla
con "multiple definition" al linkear (`var_globales.h` y `error.h` definen variables
globales sin `extern`, e incluirlos desde varios .c da error con GCC ≥ 10, que ya no
trata esas variables como "common symbols" por defecto). Si alguien reescribe el
Makefile desde cero, no se olviden de este flag.

## Usar

    ./src/ucc -c lote_de_prueba.c
    ./src/ucc -o lote_de_prueba.o

## Empaquetar una entrega

    ./scripts/empaquetar.sh 1   # compila, valida que exista docs/decisiones/entrega1.md, arma ucc_entrega1.zip

## Roadmap y cola de tickets

El plan de la etapa en curso vive en `docs/roadmap_entrega1.md`, y el seguimiento diario en
la planilla de Google Sheets enlazada ahí.

El trabajo **no se reparte por módulo ni por persona**: es una cola de tickets chicos que
cualquiera toma. Reglas:

- **Un ticket = un issue = una rama `feat/<id>` = un PR.** Nunca dos tickets en un PR.
- **Nadie asigna: cada uno se auto-asigna** de la cola. Máximo 1 ticket tomado a la vez.
- **Claim con vencimiento:** 72 h sin PR abierto y el issue vuelve a la cola, sin avisar.
- **Definition of done = CI verde.** No existe "ya lo hice, falta que revisen".
- **Las decisiones de contrato se proponen como PR con ventana de 48 h.**
- **Si estás bloqueado, tomás un ticket de lotes de prueba.** No dependen de ninguna línea
  de código y siempre hay disponibles.
- **`git rebase` sobre `develop` antes de pedir review. Nunca merge commit. Nunca
  reformatear ni reordenar funciones de `parser.c`**: los tickets de instrumentación tocan
  ese archivo en bloques disjuntos, y el formateo es el único riesgo real de conflicto.
- **Separación de propiedad por archivo:** los tickets de conjuntos FIRST1 son los únicos
  que tocan el header de conjuntos; los de instrumentación, los únicos que tocan `parser.c`.

La planilla marca en verde los tickets cuyos bloqueantes ya están en Hecho. **Ese es el
menú: no elijas fuera de ahí.**

Los issues se crean con:

    python3 scripts/crear_issues.py --dry-run   # muestra qué haría
    python3 scripts/crear_issues.py             # crea labels e issues (idempotente)

## Gramática de referencia

**La BNFE es la fuente de verdad**, no la BNF. Tiene 30 no terminales y `parser.c` tiene 29
funciones: la diferencia es exactamente `<relación>` (ítem 6 de la guía práctica). La BNF
impresa tiene al menos un error —en `<declarador init>` ubica el `[` después del `=`, cuando
el código lo trata como alternativa hermana— y un `=` de más en `<op relacional>`.

La BNF se usa como **andamio de cálculo**: sus no terminales `<resto X>` son los nombres de
los conjuntos de continuación que los `{ }` de la BNFE dejan anónimos, y que hacen falta
para el `test` al final de cada cuerpo de bucle. Verificar cada producción contra la BNFE
antes de confiar en ella. Ver el ticket `T6`.

## Roadmap y cola de tickets

El plan de la etapa en curso vive en `docs/roadmap_entrega1.md`, y el seguimiento diario en
la planilla de Google Sheets enlazada ahí.

El trabajo **no se reparte por módulo ni por persona**: es una cola de tickets chicos que
cualquiera toma. Reglas:

- **Un ticket = un issue = una rama `feat/<id>` = un PR.** Nunca dos tickets en un PR.
- **Nadie asigna: cada uno se auto-asigna** de la cola. Máximo 1 ticket tomado a la vez.
- **Claim con vencimiento:** 72 h sin PR abierto y el issue vuelve a la cola, sin avisar.
- **Definition of done = CI verde.** No existe "ya lo hice, falta que revisen".
- **Las decisiones de contrato se proponen como PR con ventana de 48 h.**
- **Si estás bloqueado, tomás un ticket de lotes de prueba.** No dependen de ninguna línea
  de código y siempre hay disponibles.
- **`git rebase` sobre `develop` antes de pedir review. Nunca merge commit. Nunca
  reformatear ni reordenar funciones de `parser.c`**: los tickets de instrumentación tocan
  ese archivo en bloques disjuntos, y el formateo es el único riesgo real de conflicto.
- **Separación de propiedad por archivo:** los tickets de conjuntos FIRST1 son los únicos
  que tocan el header de conjuntos; los de instrumentación, los únicos que tocan `parser.c`.

La planilla marca en verde los tickets cuyos bloqueantes ya están en Hecho. **Ese es el
menú: no elijas fuera de ahí.**

Los issues se crean con:

    python3 scripts/crear_issues.py --dry-run   # muestra qué haría
    python3 scripts/crear_issues.py             # crea labels e issues (idempotente)

## Gramática de referencia

**La BNFE es la fuente de verdad**, no la BNF. Tiene 30 no terminales y `parser.c` tiene 29
funciones: la diferencia es exactamente `<relación>` (ítem 6 de la guía práctica). La BNF
impresa tiene al menos un error —en `<declarador init>` ubica el `[` después del `=`, cuando
el código lo trata como alternativa hermana— y un `=` de más en `<op relacional>`.

La BNF se usa como **andamio de cálculo**: sus no terminales `<resto X>` son los nombres de
los conjuntos de continuación que los `{ }` de la BNFE dejan anónimos, y que hacen falta
para el `test` al final de cada cuerpo de bucle. Verificar cada producción contra la BNFE
antes de confiar en ella. Ver el ticket `T6`.

## Convención de git

- Tres capas: `main` <- `develop` <- `feat/<id>` / `fix/<id>`.
  - `feat/<id>` / `fix/<id>`: trabajo local de cada uno, rama corta por función
    del PDR (no por módulo/archivo — `parser.c` es un solo archivo que crece
    con cada etapa, ahí es donde se reparte el trabajo real). Se mergea a
    `develop` por PR.
  - `develop`: acumula el trabajo de la etapa en curso, recibe los PRs de
    `feat/*` y `fix/*`.
  - `main`: solo recibe el merge de `develop` en el momento de una entrega, vía
    PR aprobado por los otros dos integrantes (la aprobación del propio autor
    no cuenta). Ese merge es la entrega.
  - Tag por entrega aprobada en `main`: `entrega1`, `entrega2`, `entrega3` — para
    poder volver a un estado anterior si la corrección de una etapa exige
    recuperar algo.
- `main` y `develop` están protegidas: PR obligatorio, 1 aprobación (2 para el
  PR de entrega a `main`) que se descarta con cada commit nuevo, conversaciones
  resueltas, check de CI en verde, sin bypass para nadie (admins incluidos). Un
  PR contra `main` cuyo origen no sea `develop` se rechaza automáticamente
  (chequeo de CI, no solo convención de equipo).

## CI y validación de tests

- El exit code de `ucc` no distingue programa válido de inválido: `main()` en
  `parser.c` siempre devuelve 0 pase lo que pase durante el parseo (los
  `exit(1)` de `util.c` son solo por errores de invocación — archivo
  inexistente, argumentos mal puestos — no por errores de sintaxis del
  programa de entrada). La señal está en stdout, vía `error_print`: `Error N:
  ...` es una falla, `Warning N: ...` no lo es.
  - `validos/*.c`: el CI falla si aparece alguna línea `Error N` en stdout.
  - `invalidos/*.c`: assertion fuerte contra un `.esperado` por caso, con la
    secuencia exacta de errores que debe reportar. Corren con timeout: un bug
    en la sincronización antipánico puede colgar el parser en vez de fallar
    limpio, y sin timeout eso cuelga el job entero.
  - Ojo al armar un `.esperado`: los mensajes de `error_print` (`error.c`)
    tienen espacios finales antes del `\n` (ej. `"Error 10: Ocurrio un error "`).
    Generá el archivo copiando la salida real de una corrida de `ucc` ya
    verificada a ojo, no lo tipees de memoria — un espacio de más rompe el
    diff sin que se note por qué.
