#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

class Matrix
{
private:
    int** mat;
    unsigned int n;
    unsigned int m;
    void txt_file_to_matrix(unsigned int n, unsigned int m, string file_name);
    void csv_file_to_matrix(unsigned int n, unsigned int m, string file_name);
public:
    Matrix();
    void file_to_matrix(unsigned int n, unsigned int m, string file_name, string file_type);
    void print_matrix();
};

#endif // MATRIX_H
