# Decisiones de diseño — Entrega 1

> Curar desde la Bitácora de decisiones antes de empaquetar. Esto es lo que se sube a
> Classroom junto con el ejecutable y los fuentes (la guía general lo pide como
> "descripción puntual de las decisiones que ha tomado para abordar la etapa").

## Decisiones tomadas

Un `###` por ticket para que cada PR toque sólo su bloque y no genere conflictos de
merge con otro ticket en curso.

### Capa 0 · Contrato

#### T1

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
Corrección del procedimiento `error_handler()` en `src/error.c` para garantizar
salidas limpias y reproducibles:

- **Eliminación de comportamiento indefinido:** Se eliminó el uso de la variable
  `i` sin inicializar en la rama `last_call`, que generaba lecturas de basura en la
  pila y errores espurios no deterministas.
- **Salida limpia en programas válidos:** Las señales de vaciado
  (`COD_IMP_ERRORES` y `last_call`) ahora verifican `cant_errores_x_linea > 0` antes
  de imprimir la cabecera `Linea N - ...`, evitando imprimir código en stdout cuando
  no hubo errores sintácticos.
- **Unificación de fin de línea y fin de archivo:** Se unificó el mecanismo de
  reporte para que la última llamada (`last_call`) use la misma lógica consistente que
  el salto de línea `\n`.
- **Protección de buffer:** Se agregó la guarda `cant_errores_x_linea < E_X_LINEA`
  para prevenir desbordamientos de buffer ante ráfagas de errores en una misma línea.

#### T5

#### T6

### Capa 1 · FIRST1

#### F1

#### F2

#### F3

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

#### L4

#### L5

#### L6

#### L7

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
