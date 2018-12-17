#include<iostream>
#include<omp.h>

void initMatrix(int**& a,int**& b,int**& c,int size) {
	a = new int*[size];
	b = new int*[size];
	c = new int*[size];
#pragma omp parallel for
	for (int i = 0; i < size; i++)
	{
		a[i] = new int[size];
		b[i] = new int[size];
		c[i] = new int[size];
#pragma ivdep
		for (int j = 0; j < size; j += 4)
		{
			a[i][j] = rand() % 100;
			a[i][j + 1] = rand() % 100;
			a[i][j + 2] = rand() % 100;
			a[i][j + 3] = rand() % 100;

			b[i][j] = rand() % 100;
			b[i][j + 1] = rand() % 100;
			b[i][j + 2] = rand() % 100;
			b[i][j + 3] = rand() % 100;

			c[i][j] = 0;
			c[i][j + 1] = 0;
			c[i][j + 2] = 0;
			c[i][j + 3] = 0;
		}

	}

	
}

int** T(int**& mat,int size) {
	int** res= new int*[size];
#pragma omp parallel for
	for (int i = 0; i < size; i++)
	{
		res[i] = new int[size];
#pragma ivdep
		for (int j = 0; j < size; j+=4) {
			res[i][j] = mat[j][i];
			res[i][j+1] = mat[j+1][i];
			res[i][j+2] = mat[j+2][i];
			res[i][j + 3] = mat[j + 3][i];
		}
	}
	return res;
}

void multiplyMat0(int **a, int **b, int **c, int size) {
	for (int i = 0; i < size; i++)
	for (int j = 0; j < size; j++)
			for (int k = 0; k < size; k++)
				c[i][j] += a[i][k] * b[k][j];
}

void multiplyMat1(int **a, int **b, int **c, int size) {
	b = T(b, size);
//#pragma omp parallel for
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			#pragma ivdep
			for (int k = 0; k < size; k+=4) {
				c[i][j] = c[i][j] + a[i][k] * b[j][k];
				c[i][j] = c[i][j] + a[i][k+1] * b[j][k+1];
				c[i][j] = c[i][j] + a[i][k+2] * b[j][k+2];
				c[i][j] = c[i][j] + a[i][k+3] * b[j][k+3];
			}
}

void multiplyMat2(int **a, int **b, int **c, int size) {
//#pragma omp parallel for
	for (int i = 0; i < size; i++)
		for (int k = 0; k < size; k++)
		for (int j = 0; j < size; j++)
				c[i][j] += a[i][k] * b[k][j];
}

void multiplyMat3(int **a, int **b, int **c, int size) {
//#pragma omp parallel for
	for (int i = 0; i < size; i+=16)
		for (int k = 0; k < size; k++)
			{for (int j = 0; j < size; j++)
		{
			
				c[i][j] += a[i][k] * b[k][j];
				c[i+1][j] += a[i+1][k] * b[k][j];
				c[i+2][j] += a[i+2][k] * b[k][j];
				c[i+3][j] += a[i+3][k] * b[k][j];
				c[i+4][j] += a[i+4][k] * b[k][j];
				c[i+5][j] += a[i+5][k] * b[k][j];
				c[i+6][j] += a[i+6][k] * b[k][j];
				c[i+7][j] += a[i+7][k] * b[k][j];
				c[i+8][j] += a[i+8][k] * b[k][j];
				c[i+9][j] += a[i+9][k] * b[k][j];
				c[i+10][j] += a[i+10][k] * b[k][j];
				c[i+11][j] += a[i+11][k] * b[k][j];
				c[i+12][j] += a[i+12][k] * b[k][j];
				c[i+13][j] += a[i+13][k] * b[k][j];
				c[i+14][j] += a[i+14][k] * b[k][j];
				c[i+15][j] += a[i+15][k] * b[k][j];
				
			}
		}
	
}


void multiplyMat4(int **a, int **b, int **c, int size) {
	
	
	b = T(b, size);
//#pragma omp parallel for
	for (int i = 0; i < size; i+=16)
		for (int j = 0; j < size; j++)
#pragma ivdep
			for (int k = 0; k < size; k++) {
				c[i][j] = c[i][j] + a[i][k] * b[j][k];
				c[i + 1][j] += a[i + 1][k] * b[j][k];
				c[i + 2][j] += a[i + 2][k] * b[j][k];
				c[i + 3][j] += a[i + 3][k] * b[j][k];
				c[i + 4][j] += a[i + 4][k] * b[j][k];
				c[i + 5][j] += a[i + 5][k] * b[j][k];
				c[i + 6][j] += a[i + 6][k] * b[j][k];
				c[i + 7][j] += a[i + 7][k] * b[j][k];
				c[i + 8][j] += a[i + 8][k] * b[j][k];
				c[i + 9][j] += a[i + 9][k] * b[j][k];
				c[i + 10][j] += a[i + 10][k] * b[j][k];
				c[i + 11][j] += a[i + 11][k] * b[j][k];
				c[i + 12][j] += a[i + 12][k] * b[j][k];
				c[i + 13][j] += a[i + 13][k] * b[j][k];
				c[i + 14][j] += a[i + 14][k] * b[j][k];
				c[i + 15][j] += a[i + 15][k] * b[j][k];
				
			}
}

void multiplyMat5(int **a, int **b, int **c, int size) {
	a = T(a, size);
//#pragma omp parallel for
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
#pragma ivdep
			for (int k = 0; k < size; k ++) {
				c[i][j] = c[i][j] + a[k][i] * b[k][j];
			}
}
void multiplyMat6(int **a, int **b, int **c, int size) {


	b = T(b, size);
//#pragma omp parallel for
	for (int i = 0; i < size; i += 16)
		for (int j = 0; j < size; j++)
#pragma ivdep
			for(int r=0;r<size/16;r++)
			for (int k = r*16; k < (r+1)*16; k++) {
				c[i][j] = c[i][j] + a[i][k] * b[j][k];
				c[i + 1][j] += a[i + 1][k] * b[j][k];
				c[i + 2][j] += a[i + 2][k] * b[j][k];
				c[i + 3][j] += a[i + 3][k] * b[j][k];
				c[i + 4][j] += a[i + 4][k] * b[j][k];
				c[i + 5][j] += a[i + 5][k] * b[j][k];
				c[i + 6][j] += a[i + 6][k] * b[j][k];
				c[i + 7][j] += a[i + 7][k] * b[j][k];
				c[i + 8][j] += a[i + 8][k] * b[j][k];
				c[i + 9][j] += a[i + 9][k] * b[j][k];
				c[i + 10][j] += a[i + 10][k] * b[j][k];
				c[i + 11][j] += a[i + 11][k] * b[j][k];
				c[i + 12][j] += a[i + 12][k] * b[j][k];
				c[i + 13][j] += a[i + 13][k] * b[j][k];
				c[i + 14][j] += a[i + 14][k] * b[j][k];
				c[i + 15][j] += a[i + 15][k] * b[j][k];

			}
}


int check(int **a, int **b, int size) {
	int **c1 = new int*[size];
	for (int i = 0; i < size; i++)
	{
		c1[i] = new int[size];
		for (int j = 0; j < size; j++)
			c1[i][j] = 0;
	}
	int **c2 = new int*[size];
	for (int i = 0; i < size; i++)
	{
		c2[i] = new int[size];
		for (int j = 0; j < size; j++)
			c2[i][j] = 0;
	}
	multiplyMat0(a, b, c1, size);
	multiplyMat6(a, b, c2, size);
	int sum = 0;
	int sum2 = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			sum += c1[i][j] - c2[i][j];
			sum2 += c1[i][j];
		}
	return sum;

}
int main(int argc, char** argv) {
	int size = 2000;
	int **a;
	int **b;
	int **c;
	int mode;
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
		std::cout << "Time : " << finish - start << std::endl;
		break;
	}
	case 1: {
		double start = omp_get_wtime();
		multiplyMat1(a, b, c, size);
		double finish = omp_get_wtime();
		std::cout << "Time : " << finish - start << std::endl;
		break;
	}
	case 2: {
		double start = omp_get_wtime();
		multiplyMat2(a, b, c, size);
		double finish = omp_get_wtime();
		std::cout << "Time : " << finish - start << std::endl;
		break;
	}
	case 3: {
		double start = omp_get_wtime();
		multiplyMat3(a, b, c, size);
		double finish = omp_get_wtime();
		std::cout << "Time : " << finish - start << std::endl;
		break;
	}
	case 4: {
		double start = omp_get_wtime();
		multiplyMat4(a, b, c, size);
		double finish = omp_get_wtime();
		std::cout << "Time : " << finish - start << std::endl;
		break;
	}
	case 5: {
		double start = omp_get_wtime();
		multiplyMat5(a, b, c, size);
		double finish = omp_get_wtime();
		std::cout << "Time : " << finish - start << std::endl;
		break;
	}
	case 6: {
		double start = omp_get_wtime();
		multiplyMat6(a, b, c, size);
		double finish = omp_get_wtime();
		std::cout << "Time : " << finish - start << std::endl;
		break;
	}

	
	default:
		break;
	}

	//system("pause");
}
