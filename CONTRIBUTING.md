# Cómo trabajamos: ramas, PRs y CI

Guía paso a paso para el equipo. Si nunca usaste un flujo con `develop`, seguí
esto literal las primeras veces — después se vuelve automático.

## 1. Estructura de ramas

```
main     <- solo recibe una entrega ya aprobada (tag entrega1, entrega2, entrega3)
develop  <- acumula el trabajo de la etapa en curso
feat/<id> o fix/<id>  <- tu trabajo del día a día, sale de develop y vuelve a develop
```

- Nunca se trabaja directo sobre `main` ni sobre `develop`: ambas están protegidas,
  un push directo va a ser rechazado por GitHub.
- El nombre de la rama va por **función del PDR que estás tocando**, no por
  archivo (`parser.c` es un solo archivo que vamos a tocar los tres, así que
  "una rama por archivo" no tiene sentido). Ejemplos: `feat/decl-init`,
  `fix/recovery-factor`.

## 2. Flujo para una feature o fix

```bash
git checkout develop
git pull

git checkout -b feat/mi-cosa

# ... trabajás, commiteás normal ...

git push -u origin feat/mi-cosa
```

Después abrís el Pull Request **contra `develop`** (no contra `main`):

```bash
gh pr create --base develop --fill
```

o desde la web: te va a aparecer un botón "Compare & pull request" al pushear.

Para que se pueda mergear necesitás:
- **1 aprobación de un compañero** (tu propia aprobación no cuenta, ni siquiera
  siendo admin del repo).
- Todas las conversaciones/comentarios del PR resueltos.
- El check **`build-and-test`** en verde (lo corre el CI automáticamente, ver
  abajo).

Cuando esté todo en verde, mergeá desde la web (botón "Merge pull request").

## 3. Flujo de entrega (develop → main)

Esto se hace una sola vez por etapa, cuando la entrega está lista:

```bash
gh pr create --base main --head develop --fill
```

Diferencias con un PR normal:
- Necesita **2 aprobaciones** (los otros dos integrantes).
- El CI además verifica que el PR venga específicamente de `develop` — si por
  error alguien abre un PR de `feat/algo` directo a `main`, el job falla solo
  y no hay forma de mergearlo aunque junte las aprobaciones.

Una vez mergeado, taggeá la entrega:

```bash
git checkout main
git pull
git tag entregaN
git push origin entregaN
```

## 4. Qué hace el CI (`build-and-test`)

Se dispara solo, en cada PR. Pasos:

1. `make -C src` — si no compila, el check falla ahí mismo.
2. Recorre cada `tests/entregaN/`:
   - **`validos/*.txt`**: corre `./ucc -c archivo`. Falla si aparece cualquier
     línea `Error N: ...` en la salida (un `Warning N: ...` no cuenta como
     falla).
   - **`invalidos/*.txt`**: corre `./ucc -c archivo` y compara la salida contra
     un archivo `archivo.esperado` (mismo nombre, extensión `.esperado`) con la
     secuencia exacta de errores que tiene que reportar. Corre con timeout, por
     si un bug de recuperación antipánico cuelga el parser en vez de terminar.
   - **`pendientes/{validos,invalidos}/`**: el CI **no las toca nunca**. Ahí van
     los casos que ya escribiste pero cuya feature todavía no está resuelta.

### Cómo agregar un test tuyo

1. Escribí el `.txt` de entrada en `tests/entregaN/pendientes/validos/` o
   `pendientes/invalidos/`, según corresponda.
2. Cuando termines la feature que lo resuelve, corré a mano y revisá que la
   salida sea la que esperás:
   ```bash
   ./src/ucc -c tests/entregaN/pendientes/invalidos/mi_caso.txt
   ```
3. Promovelo como parte del **mismo PR** que resuelve la feature:
   - Si es válido: `git mv` el `.txt` a `validos/`. No necesita `.esperado`.
   - Si es inválido: copiá del output real las líneas `Error N: ...` (tal cual
     salen, con espacios y todo — no las tipees de memoria) a
     `mi_caso.esperado`, y movés ambos archivos a `invalidos/`.

Esto es a propósito: si a alguien se le ocurre cargar de una todos los tests de
la entrega, van a estar todos en `pendientes/` fallando en silencio (el CI ni
los mira) hasta que cada uno se resuelva y promueva por su cuenta — evita el
PR gigante que "resuelve toda la consigna junta".

## 5. Reglas duras (para que no sorprendan)

- No podés aprobar tu propio PR.
- No se puede pushear directo a `main` ni a `develop`.
- No se puede forzar push ni borrar esas ramas, ni siendo admin del repo.
- Un PR contra `main` que no venga de `develop` se rechaza automáticamente.

## 6. Si el check `build-and-test` falla

Mirá el log del step "Tests por entrega" en la pestaña **Checks** del PR.
Causas más comunes:
- Falta el `.esperado` de un caso nuevo en `invalidos/` (el CI lo dice
  explícitamente en el error).
- El `.esperado` no coincide por un espacio o salto de línea de más — generalo
  copiando la salida real, no a mano.
- `ucc` no compiló (`make -C src` a mano te da el error real).
- Timeout en un caso de `invalidos/` — probable loop infinito en la
  recuperación antipánico, no un test mal armado.
