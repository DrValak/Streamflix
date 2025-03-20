# Variáveis
CC = gcc                      # Compilador
CFLAGS = -Wall -Wextra -std=c99 -g  # Flags de compilação
SRC = src/main.c src/streaming.c src/csv_handler.c src/menus.c src/personal_list.c src/recommended.c src/favorite.c  src/report.c# Todos os arquivos fonte
OBJ = $(SRC:src/%.c=build/obj/%.o)  # Arquivos objeto gerados
TARGET = build/main           # Nome do executável final

# Diretórios
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Regra padrão (primeira regra executada ao rodar 'make')
.PHONY: all clean

all: $(TARGET)
# Regra para criar o executável
$(TARGET): $(OBJ)
    # Cria o diretório build, se necessário
	mkdir -p $(BUILD_DIR)
    # Compila os arquivos objeto e gera o executável
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)
# Regra para compilar os arquivos .c em .o
$(OBJ_DIR)/%.o: src/%.c
    # Cria o diretório obj, se necessário
	mkdir -p $(OBJ_DIR)
    # Compila um arquivo .c em um arquivo .o
	$(CC) $(CFLAGS) -c $< -o $@
# Limpar arquivos compilados
clean:
    # Remove o diretório build e os arquivos objeto
	rm -rf $(BUILD_DIR)