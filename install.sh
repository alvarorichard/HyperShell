#!/bin/bash

# Verifica se o script está sendo executado como root
if [ "$EUID" -ne 0 ]
  then echo "Por favor, execute como root"
  exit
fi

# Define o compilador padrão como gcc
COMPILER="gcc"

# Verifica se o LLVM está instalado e, em caso afirmativo, usa-o como compilador
if command -v clang &> /dev/null
then
    COMPILER="clang"
fi

echo "Compilando com $COMPILER..."

# Compila o código

# use a pasta src/ para compilar o código
$COMPILER src/main.c src/hs_builtin.c src/hs_loop.c src/hs_read_line.c src/hs_split_line.c src/hs_launch.c -o hs



# Torna o binário executável
chmod +x hs

# Remove o link simbólico existente, se houver
rm -f /usr/local/bin/hs

# Cria um novo link simbólico para o binário
ln -s "$(pwd)/hs" /usr/local/bin/hs

echo "Compilação concluída. Link simbólico criado em /usr/local/bin/hs"
