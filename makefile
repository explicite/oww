CC = gcc
CFLAGS = -std=c99
PROJ1_DIR = "./src/p1"
OUT_DIR = "./out"

all: mk_out matrix main app

app:
	$(CC) $(CFLAGS) $(OUT_DIR)/matrix.o $(OUT_DIR)/main.o -o app.out
	
main:
	$(CC) $(CFLAGS) -c $(PROJ1_DIR)/main.c -o $(OUT_DIR)/main.o
	
matrix: 
	$(CC) $(CFLAGS) -c $(PROJ1_DIR)/matrix.c -o $(OUT_DIR)/matrix.o
	
clean: del_app
	rm -r $(OUT_DIR)
	
del_app:
	rm app.out
mk_out: 
	mkdir $(OUT_DIR)
	