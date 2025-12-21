# Coisas do compilador
CC = gcc # GCC eh o nosso compilador
CFLAGS = -Wall -Wextra -O2 -g -Iinclude # Flags de compilacao

# Definindo os diretorios
SRC_DIR = src
BUILD_DIR = output
BIN_DIR = $(BUILD_DIR)\bin
OBJ_DIR = $(BUILD_DIR)\obj


# Função recursiva pra achar os .c necessarios para a compilação
define find_srcs
$(foreach dir,$(wildcard $(1)/*),$(call find_srcs,$(dir)) $(filter %.c,$(wildcard $(1)/*)))
endef

# Definindo as fontes e a pasta da compilação
SRCS = $(call find_srcs,$(SRC_DIR))
OBJS = $(SRCS:$(SRC_DIR)\%.c=$(OBJ_DIR)\%.o)
TARGET = $(BIN_DIR)\raytracing


# Compilação geral
all: create_dirs $(TARGET) 

# Cria os diretorios caso nao exista
create_dirs:
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
	@for %%f in ($(OBJS)) do @if not exist "%%~pf" mkdir "%%~pf"

# Compila o executavel 
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Compila os objetos (-c)
$(OBJ_DIR)\%.o: $(SRC_DIR)\%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Dando clean
clean:
	@if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"

# Caso nao seja passado nenhum comando explicitamente, essa será a ordem de execução
.PHONY: all create_dirs  clean