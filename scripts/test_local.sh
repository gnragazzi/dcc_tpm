#!/usr/bin/env bash
# Corre localmente los mismos tests que .github/workflows/ci.yml.
# Uso: ./scripts/test_local.sh [-e N]
#   -e N  corre solo los tests de tests/entregaN (por defecto, todas)
set -euo pipefail

trim_lineas() { sed -E 's/^[[:space:]]+//; s/[[:space:]]+$//' | sed '/^$/d'; }

entrega_sel=""
while getopts "e:" opt; do
  case "$opt" in
    e) entrega_sel="$OPTARG" ;;
    *) echo "Uso: $0 [-e N]" >&2; exit 2 ;;
  esac
done

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
SRC_DIR="$ROOT_DIR/src"

make -C "$SRC_DIR"

cd "$ROOT_DIR"
shopt -s nullglob
fail=0
casos=0

if [ -n "$entrega_sel" ]; then
  entregas=("tests/entrega$entrega_sel/")
  if [ ! -d "${entregas[0]}" ]; then
    echo "ERROR: no existe ${entregas[0]}" >&2
    exit 2
  fi
else
  entregas=(tests/entrega*/)
fi

for entrega_dir in "${entregas[@]}"; do
  entrega="$(basename "$entrega_dir")"

  for f in "${entrega_dir}validos/"*.c; do
    casos=$((casos + 1))
    status=0
    out="$(timeout 5 ./src/ucc -c "$f" 2>&1)" || status=$?
    if [ $status -ne 0 ]; then
      echo "ERROR: [$entrega/validos] $f: ucc terminó con status $status (crash o timeout)"
      fail=$((fail + 1))
    elif echo "$out" | grep -Eq "Error [0-9]+:"; then
      echo "ERROR: [$entrega/validos] $f: se esperaba sin errores, pero reportó:"
      echo "$out" | grep -E "Error [0-9]+:"
      fail=$((fail + 1))
    fi
  done

  for f in "${entrega_dir}invalidos/"*.c; do
    casos=$((casos + 1))
    esperado="${f%.c}.esperado"
    if [ ! -f "$esperado" ]; then
      echo "ERROR: [$entrega/invalidos] $f: falta $esperado (secuencia de errores esperada)"
      fail=$((fail + 1))
      continue
    fi

    status=0
    out="$(timeout 5 ./src/ucc -c "$f" 2>&1)" || status=$?
    if [ $status -ne 0 ]; then
      echo "ERROR: [$entrega/invalidos] $f: ucc terminó con status $status (crash o timeout, no se pudo evaluar la recuperación antipánico)"
      fail=$((fail + 1))
      continue
    fi

    got="$(echo "$out" | grep -E "Error [0-9]+:" | trim_lineas || true)"
    want="$(trim_lineas < "$esperado")"
    if [ "$got" != "$want" ]; then
      echo "ERROR: [$entrega/invalidos] $f: la secuencia de errores no coincide con $esperado"
      diff <(echo "$want") <(echo "$got") || true
      fail=$((fail + 1))
    fi
  done
done

if [ "$casos" -eq 0 ]; then
  echo "ERROR: No se ejecutó ningún caso de prueba: los tests deben ser archivos .c bajo tests/entrega*/validos/ o tests/entrega*/invalidos/"
  fail=$((fail + 1))
fi

echo "Casos ejecutados: $casos"
echo "Tests fallados: $fail"
exit $((fail > 0 ? 1 : 0))
