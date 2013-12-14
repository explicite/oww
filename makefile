CC = cc
CFLAGS = -std=c99 -fopenmp -pthread -O3 
PROJ1_DIR = "./src"
OUT_DIR = "./out"

all: mk_out random vector compres matrix test stoper main app

app:
	$(CC) $(CFLAGS) \
	$(OUT_DIR)/random.o \
	$(OUT_DIR)/vector.o \
	$(OUT_DIR)/compres.o \
	$(OUT_DIR)/matrix.o \
	$(OUT_DIR)/stoper.o \
	$(OUT_DIR)/test.o \
	$(OUT_DIR)/main.o -o app.out

main:
	$(CC) -c $(CFLAGS) $(PROJ1_DIR)/main.c -o $(OUT_DIR)/main.o

stoper:
	$(CC) -c -O3       $(PROJ1_DIR)/stoper.c -o $(OUT_DIR)/stoper.o
	
test: 
	$(CC) -c $(CFLAGS) $(PROJ1_DIR)/test.c -o $(OUT_DIR)/test.o

compres:
	$(CC) -c $(CFLAGS) $(PROJ1_DIR)/compres.c  -o $(OUT_DIR)/compres.o

matrix: 
	$(CC) -c $(CFLAGS)  $(PROJ1_DIR)/matrix.c  -o $(OUT_DIR)/matrix.o

vector: 
	$(CC) -c $(CFLAGS) $(PROJ1_DIR)/vector.c  -o $(OUT_DIR)/vector.o

random:
	$(CC) -c $(CFLAGS) $(PROJ1_DIR)/random.c -o $(OUT_DIR)/random.o

clean: 
	rm -rf $(OUT_DIR)
	rm -f app.out

mk_out: 
	mkdir -p $(OUT_DIR)
