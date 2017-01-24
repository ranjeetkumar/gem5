#include <iomanip>
#include <iostream>
#include <random>

#include "../../../util/m5/m5op.h"

#define BLOCK_SIZE 16

using namespace std;

void multiply(double **A, double **B, double **C, int size)
{
    for (int k = 0; k < size; k += BLOCK_SIZE) {
        for (int j = 0; j < size; j += BLOCK_SIZE) {
            for (int i = 0; i < size; i++) {
                for (int jj = j; jj < min(j + BLOCK_SIZE, size); jj++) {
                    for (int kk = k; kk < min(k + BLOCK_SIZE, size); kk++) {
                        C[i][jj] += A[i][kk] * B[kk][jj];
                    }
                }
            }
        }
    }
}

void printMatrix(double **A, int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << setprecision(3) << setw(8) << A[i][j] << "  ";
        }
        cout << endl;
    }
}

int main(int argc, char *argv[])
{

    int size = 128;

    cout << "Initalizing the matricies...";

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1);

    double *dataA = new double[size*size];
    double *dataB = new double[size*size];
    double *dataC = new double[size*size];

    double **A = new double*[size];
    double **B = new double*[size];
    double **C = new double*[size];

    for (int i = 0; i < size; i++)	{
        A[i] = &dataA[size * i];
        B[i] = &dataB[size * i];
        C[i] = &dataC[size * i];
        for (int j = 0; j < size; j++) {
                A[i][j] = dis(gen);
                B[i][j] = dis(gen);
                C[i][j] = 0;
        }
    }

    cout << "Done." << endl;

    cout << "Beginning multiply...";

    m5_dumpreset_stats(0, 0);
    multiply(A, B, C, size);
    m5_dumpreset_stats(0, 0);

    cout << "Done." << endl;

    delete[] A;
    delete[] B;
    delete[] C;
    delete[] dataA;
    delete[] dataB;
    delete[] dataC;
}
