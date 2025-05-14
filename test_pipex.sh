#!/usr/bin/env bash
# Tester personalizado para tu pipex actual

PIPEX=./pipex
PASS=0
FAIL=0

run_test() {
  desc="$1"; infile="$2"; cmd1="$3"; cmd2="$4"; outfile="$5"
  exp_out="$6"; exp_err="$7"; exp_code="$8"

  echo -n "📋 $desc: "
  rm -f tmp_err "$outfile"
  $PIPEX "$infile" "$cmd1" "$cmd2" "$outfile" 2>tmp_err
  code=$?
  actual_err=$(<tmp_err)
  actual_out=$(<"$outfile" 2>/dev/null || echo)

  if [[ "$actual_err" != "$exp_err" ]]; then
    echo "❌ stderr mismatch"
    echo "  Esperado err> '$exp_err'"
    echo "  Recibido err> '$actual_err'"
    ((FAIL++)); return
  fi
  if [[ "$actual_out" != "$exp_out" ]]; then
    echo "❌ stdout mismatch"
    echo "  Esperado out> '$exp_out'"
    echo "  Recibido out> '$actual_out'"
    ((FAIL++)); return
  fi
  if [[ $code -ne $exp_code ]]; then
    echo "❌ exit code $code (esperado $exp_code)"
    ((FAIL++)); return
  fi
  echo "✅"
  ((PASS++))
}

# 📦 Test 1: Comando válido
echo "Hola Mundo" > infile1
run_test "grep + wc" infile1 "grep Mundo" "wc -l" outfile1 \
  "1" "" 0

# 📦 Test 2: Infile no existente
run_test "Infile no existe" nofile "cat" "wc -l" outfile2 \
  "" "nofile: No such file or directory" 1

# 📦 Test 3: Sin permisos en outfile
mkdir -p no_perm; chmod 500 no_perm
echo "x" > infile3
run_test "Outfile sin permiso" infile3 "cat" "wc -l" no_perm/out \
  "" "no_perm/out: Permission denied" 1
chmod -R +w no_perm; rm -rf no_perm

# 📦 Test 4: Comando 1 no existe
echo "Hola" > infile4
run_test "cmd1 inválido" infile4 "invalidoCMD" "wc -l" outfile4 \
  "" "Command not found: invalidoCMD" 127

# 📦 Test 5: Comando 2 no existe
echo "Hola" > infile5
run_test "cmd2 inválido" infile5 "cat" "noCMD" outfile5 \
  "" "Command not found: noCMD" 127

# 📦 Test 6: Ruta absoluta válida
echo "test" > infile6
run_test "ruta absoluta /bin/cat" infile6 "/bin/cat" "wc -l" outfile6 \
  "1" "" 0

# 📦 Test 7: PATH vacío
PATH="" run_test "PATH vacío" infile4 "cat" "wc -l" outfile7 \
  "" "Command not found: cat" 127

# 📦 Test 8: Archivo grande
yes "a" | head -n 5000 > infile8
run_test "archivo largo" infile8 "wc -l" "wc -c" outfile8 \
  "5000" "" 0

# 📦 Test 9: Argumentos con comillas
echo "foo bar" > infile9
run_test "args con espacio" infile9 "cut -d ' ' -f2" "wc -c" outfile9 \
  "4" "" 0

# 📦 Resultado final
echo
echo "✅ Passed: $PASS   ❌ Failed: $FAIL"

