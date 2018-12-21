#include<iostream>
#include <immintrin.h> 
#include<omp.h>
#include<tuple>

void initMatrix(int*& a, int*& b, int*& c, int size) {
	
#pragma omp parallel for
	for (int i = 0; i < size; i++)
	{

		for (int j = 0; j < size; j++)
		{
			//a[i*size + j] = rand() % 100;
			//b[i*size + j] = rand() % 100;
			c[i*size + j] = 0;


		}
	}


}
void multiplyMat0(int *a, int *b, int *c, int size) {
	for (int i = 0; i < size; i++)
	for (int j = 0; j < size; j++)
			for (int k = 0; k < size; k++)
				c[i*size+j] += a[i*size+k] * b[k*size+j];
}

void multiplyMat1(int *a, int *b, int *c, int size) {
	int bSize = 64;
	int cell =size / bSize;
	for (int jk = 0; jk < cell; jk++) 
		for (int ik = 0; ik < cell; ik++) 
			for (int j = jk * bSize; j < jk * bSize + bSize; j++)
				for (int k = ik * bSize; k < ik * bSize + bSize; k++) {
					int A = a[j*size+k];
					int j_size = j*size, k_size = k*size;
					for (int i = 0; i < size; i++) {
						c[j_size+i] += A * b[k_size+i];
					}
				}
}




std::tuple<int,int,int,int,int> check(int *a, int *b, int size) {
	int *c1 = (int*)_mm_malloc(sizeof(int)*(size*size), 64);
	
	int *c2 = (int*)_mm_malloc(sizeof(int)*(size*size), 64);
	
	multiplyMat0(a, b, c1, size);
	multiplyMat1(a, b, c2, size);
	int sum = 0;
	int sum2 = 0;
	int sum3 = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			sum += c1[i*size+j] - c2[i*size+j];
			sum2 += c1[i*size+j];
			sum3  += c2[i*size + j];
		}
	
	
	return std::make_tuple(sum, sum2, sum3,c1[0],c2[0]);

}


int main(int argc, char** argv) {
	int size = 1024*4;
	int mode;
	int *a = (int*)malloc(sizeof(int)*(size*size));
	int *b = (int*)malloc(sizeof(int)*(size*size));
	int *c = (int*)malloc(sizeof(int)*(size*size));
	initMatrix(a, b, c, size);
	//check(a, b, size);
	if (argc != 2) {
		std::cout<<"Error! argument not exist!" << std::endl;
		
		return -1;
	}
	else
		mode = atoi(argv[1]);
	switch (mode)
	{
	case 0:{
		double start = omp_get_wtime();
		
		multiplyMat0(a, b, c, size);
		double finish = omp_get_wtime();
		std::cout<< "Time : " << finish - start << std::endl;
		break;
	}
	case 1: {
		double start = omp_get_wtime();
		multiplyMat1(a, b, c, size);
		double finish = omp_get_wtime();
		std::cout << "Time : " << finish - start << std::endl;
		break;
	}
	default:
		break;
	}

	//system("pause");
}