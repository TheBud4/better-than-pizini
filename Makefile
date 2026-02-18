CC      = gcc
CFLAGS  = -Wall -Wextra -Iinclude -std=c99
SRC_DIR = source
OBJ_DIR = build

SRCS = main.c $(wildcard $(SRC_DIR)/*.c)

# Gera os .o no diretório build/
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = programa

# Regra principal
all: $(OBJ_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compila arquivos de source/
$(OBJ_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compila main.c
$(OBJ_DIR)/main.o: main.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Cria o diretório build se não existir
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean