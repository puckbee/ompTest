
OPT_FLAG= -O3 -DD=2048

all: gemm.cpp
	g++ $(OPT_FLAG) gemm.cpp -o gemm -Wunknown-pragmas

thread: gemm.cpp
	g++ $(OPT_FLAG) gemm.cpp -o gemm -fopenmp -Wunknown-pragmas

clean:
	rm gemm

