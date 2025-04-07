CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -L/opt/homebrew/lib -L/usr/local/lib -lSDL2 -lSDL2_image
INCLUDES = -I/opt/homebrew/include -I/usr/local/include

# Dossiers
SRC_DIR = .
OBJ_DIR = obj
INC_DIR = .

# Fichiers sources et objets
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = chess

# Règle principale
all: $(OBJ_DIR) $(TARGET)

# Création du dossier obj s'il n'existe pas
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Création de l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compilation des fichiers sources
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -I$(INC_DIR) -c $< -o $@

# Nettoyage
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean