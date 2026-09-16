#!/usr/bin/env bash
# Corre localmente los mismos tests que .github/workflows/ci.yml.
# Uso: ./scripts/test_local.sh
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
SRC_DIR="$ROOT_DIR/src"

make -C "$SRC_DIR"

cd "$ROOT_DIR"
shopt -s nullglob
fail=0
casos=0

for entrega_dir in tests/entrega*/; do
  entrega="$(basename "$entrega_dir")"

  for f in "${entrega_dir}validos/"*.c; do
    casos=$((casos + 1))
    out="$(timeout 5 ./src/ucc -c "$f" 2>&1)"
    status=$?
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

    out="$(timeout 5 ./src/ucc -c "$f" 2>&1)"
    status=$?
    if [ $status -ne 0 ]; then
      echo "ERROR: [$entrega/invalidos] $f: ucc terminó con status $status (crash o timeout, no se pudo evaluar la recuperación antipánico)"
      fail=$((fail + 1))
      continue
    fi

    got="$(echo "$out" | grep -E "Error [0-9]+:" || true)"
    want="$(cat "$esperado")"
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
