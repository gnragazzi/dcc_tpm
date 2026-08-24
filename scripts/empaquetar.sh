#!/usr/bin/env bash
# Empaqueta una entrega para subir a Classroom.
# Uso: ./scripts/empaquetar.sh <numero_entrega>
# Compila desde cero, valida que exista la descripcion de decisiones
# de la etapa, y arma el .zip con ejecutable + fuentes + decisiones.
set -euo pipefail

if [ $# -ne 1 ]; then
  echo "Uso: $0 <numero_entrega>" >&2
  exit 1
fi

ETAPA="$1"
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
SRC_DIR="$ROOT_DIR/src"
DECISIONES="$ROOT_DIR/docs/decisiones/entrega${ETAPA}.md"
DEST="$ROOT_DIR/ucc_entrega${ETAPA}.zip"

if [ ! -f "$DECISIONES" ]; then
  echo "No existe $DECISIONES — completa las decisiones de la etapa antes de empaquetar." >&2
  exit 1
fi

echo "== Compilando =="
make -C "$SRC_DIR" clean
make -C "$SRC_DIR"

echo "== Empaquetando =="
TMP_DIR="$(mktemp -d)"
cp -r "$SRC_DIR" "$TMP_DIR/src"
cp "$DECISIONES" "$TMP_DIR/decisiones.md"

rm -f "$DEST"
(cd "$TMP_DIR" && zip -r "$DEST" src decisiones.md)
rm -rf "$TMP_DIR"

echo "Listo: $DEST"
