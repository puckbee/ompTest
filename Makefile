
OPT_FLAG= -O3 -DD=2048

all: gemm.cpp
	g++ $(OPT_FLAG) $(SERIAL_FLAG) gemm.cpp -o gemm

thread: gemm.cpp
	g++ $(OPT_FLAG) gemm.cpp -o gemm -fopenmp

clean:
	rm gemm

