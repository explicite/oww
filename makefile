CC        = cc
MPI       = mpicc -D MPI
CFLAGS    = -fopenmp -pthread -O3 
SRC_BUILD = "./src"
BUILD_DIR = "./build"
OUT_DIR   = "./out"

all: mk_out bool random vector compres matrix test stoper main app

app:
	$(CC) $(CFLAGS) \
	$(BUILD_DIR)/bool.o \
	$(BUILD_DIR)/random.o \
	$(BUILD_DIR)/vector.o \
	$(BUILD_DIR)/compres.o \
	$(BUILD_DIR)/matrix.o \
	$(BUILD_DIR)/stoper.o \
	$(BUILD_DIR)/test.o \
	$(BUILD_DIR)/main.o -o $(OUT_DIR)/app.out

mpi: mk_out bool random vector compres mpi_matrix test stoper mtp_mpi mpi_main mpi_app

mpi_app:
	$(MPI) $(CFLAGS) \
	$(BUILD_DIR)/bool.o \
	$(BUILD_DIR)/random.o \
	$(BUILD_DIR)/vector.o \
	$(BUILD_DIR)/compres.o \
	$(BUILD_DIR)/mtp_mpi.o \
	$(BUILD_DIR)/matrix.o \
	$(BUILD_DIR)/stoper.o \
	$(BUILD_DIR)/test.o \
	$(BUILD_DIR)/mpi_main.o -o $(OUT_DIR)/mpi_app.out 

main:
	$(CC) -c $(CFLAGS) $(SRC_BUILD)/main.c -o $(BUILD_DIR)/main.o

stoper:
	$(CC) -c $(CFLAGS) $(SRC_BUILD)/stoper.c -o $(BUILD_DIR)/stoper.o

mtp_mpi:
	$(MPI) -c  $(SRC_BUILD)/mtp_mpi.c -o $(BUILD_DIR)/mtp_mpi.o

mpi_main:
	$(MPI) -c  $(SRC_BUILD)/mpi_main.c -o $(BUILD_DIR)/mpi_main.o

test: 
	$(CC) -c $(CFLAGS) $(SRC_BUILD)/test.c -o $(BUILD_DIR)/test.o

compres:
	$(CC) -c $(CFLAGS) $(SRC_BUILD)/compres.c -o $(BUILD_DIR)/compres.o

matrix: 
	$(CC) -c $(CFLAGS)  $(SRC_BUILD)/matrix.c -o $(BUILD_DIR)/matrix.o
	
mpi_matrix: 
	$(MPI) -c $(CFLAGS)  $(SRC_BUILD)/matrix.c -o $(BUILD_DIR)/matrix.o


vector: 
	$(CC) -c $(CFLAGS) $(SRC_BUILD)/vector.c -o $(BUILD_DIR)/vector.o

random:
	$(CC) -c $(CFLAGS) $(SRC_BUILD)/random.c -o $(BUILD_DIR)/random.o

bool:
	$(CC) -c $(CFLAGS) $(SRC_BUILD)/bool.c -o $(BUILD_DIR)/bool.o

clean: 
	rm -rf $(BUILD_DIR) $(OUT_DIR)

mk_out: 
	mkdir -p $(BUILD_DIR)
	mkdir -p $(OUT_DIR)
