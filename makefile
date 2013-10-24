CC = gcc
CFLAGS = -std=c99
PROJ1_DIR = "./src/p1"
OUT_DIR = "./out"

all: mk_out random vector matrix compres main app

app:
	$(CC) $(CFLAGS) \
	$(OUT_DIR)/random.o \
	$(OUT_DIR)/vector.o \
	$(OUT_DIR)/matrix.o \
	$(OUT_DIR)/compres.o \
	$(OUT_DIR)/main.o -o app.out

main:
	$(CC) $(CFLAGS) -c $(PROJ1_DIR)/main.c -o $(OUT_DIR)/main.o

compres:
	$(CC) $(CFLAGS) -c $(PROJ1_DIR)/compres.c  -o $(OUT_DIR)/compres.o

matrix: 
	$(CC) $(CFLAGS) -c $(PROJ1_DIR)/matrix.c  -o $(OUT_DIR)/matrix.o

vector: 
	$(CC) $(CFLAGS) -c $(PROJ1_DIR)/vector.c  -o $(OUT_DIR)/vector.o

random:
	$(CC) $(CFLAGS) -c $(PROJ1_DIR)/random.c -o $(OUT_DIR)/random.o

clean: 
	rm -rf $(OUT_DIR)
	rm -f app.out

mk_out: 
	mkdir -p $(OUT_DIR)
