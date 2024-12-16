#include "matrix2d.h"
#include <iostream>



Matrix2D::Matrix2D(int rows, int columns, float seed_Num){
    if(rows < 0 || columns < 0){ //throws error for undesired shape
        try{
            throw 1;
        }
        catch(int e){
            std::cout << "Error, cant have matrix with sizes of a negative number" << std::endl;
            exit(-1);
        }
    }
    matrix = new float*[columns]; //on heap, list of pointers to lists of floats
    for(int i = 0; i < rows;i++){
        matrix[i] = new float[columns];  //actaually givees the pointers lists of floats to point to, on heap
    }
    num_rows = rows;
    num_columns = columns;
    for(int j = 0; j < columns; j++){ //fills array with other arrays on heap
        matrix[j] = new float[rows];
    }   
    for(int i = 0; i < columns; i++){ 
        for(int j = 0; j < rows; j++){ 
             matrix[i][j] = seed_Num; //seeds array

        }
    }
}

Matrix2D::~Matrix2D(){
    for(int i = 0; i < num_rows; i++){
        delete matrix[i];
    }
    delete matrix;
}

Matrix2D Matrix2D::operator+(Matrix2D& otherMatrix){ 
    int otherRowSize = otherMatrix.get_row_size();
    int otherColumnSize = otherMatrix.get_column_size();
    if(num_rows != otherRowSize || num_columns != otherColumnSize){//check sizes
        try{
            throw 1; //throws error for desired index out of range
        }
        catch(int e) {
            std::cout << "Error, Matrix sizes do not match" << std::endl;
            exit(-1);
        }
    }

    Matrix2D newMatrix(otherRowSize,otherColumnSize);
    
    for (int i = 0; i < this->num_rows; i++){
        for (int j = 0; j < this->num_columns; j++){
            float value = this->matrix[i][j] + otherMatrix.matrix[i][j];
            newMatrix.set_element_value(i,j,value);
        }
    }
    return newMatrix;
}

Matrix2D Matrix2D::operator-(Matrix2D& otherMatrix){
    int otherRowSize = otherMatrix.get_row_size();
    int otherColumnSize = otherMatrix.get_column_size();
    if(num_rows != otherRowSize || num_columns != otherColumnSize){//check sizes
        try{
            throw 1; //throws error for desired index out of range
        }
        catch(int e) {
            std::cout << "Error, Matrix sizes do not match" << std::endl;
            exit(-1);
        }
    }

    Matrix2D newMatrix(otherRowSize,otherColumnSize);
    
    for (int i = 0; i < this->num_rows; i++){
        for (int j = 0; j < this->num_columns; j++){
            float value = this->matrix[i][j] - otherMatrix.matrix[i][j];
            newMatrix.set_element_value(i,j,value);
        }
    }
    return newMatrix;
}

Matrix2D Matrix2D::operator*(float scalar){
    Matrix2D newMatrix(num_rows,num_columns);
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_columns; j++){
            float value = this->get_element(i,j) * scalar;
            newMatrix.set_element_value(i,j,value);
        }
    }
    return newMatrix;
}

float* Matrix2D::operator*(float *array){
    int len = *(&array + 1) - array; //the first thing is the address of the last element in the array, and then array is the address of the first
    if(len != num_columns){
        try{throw 1;}
        catch(int e){
            std::cout << "Array size and the number of columns of the matrix do not match" << std::endl;
            exit(-1);
        }
    }
    float* newArray = new float[num_columns]; //!IT IS CRICAL TO KNOW THAT THIS POINTER IS STORED ON THE HEAP AND THAT IT THUS NEEDS TO BE DELETED WHEN FINISHED BEING USED
     
}

//https://www.geeksforgeeks.org/c-program-multiply-two-matrices/
//This website is were I got the formula for matrix matrix multiplication from
Matrix2D Matrix2D::operator*(Matrix2D& otherMatrix){ //!|||-------||| NEEDS TESTING |||-------|||
    if(num_columns != otherMatrix.get_row_size()){ 
        try{throw 1;}
        catch(int e){//throws error if internal sizes dont match
            std::cout << "Row size of matrix one does not match with column size of matrix 2" << std::endl;
            exit(-1);
        }
    }

    Matrix2D newMatrix(num_rows,otherMatrix.get_column_size());

    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < otherMatrix.get_column_size(); j++){
            for(int k = 0; k < otherMatrix.get_row_size(); k++){
                float value = this->get_element(i,k) * otherMatrix.get_element(k,j);
                newMatrix.set_element_value(i,j,value);
            }
        }
    }
    return newMatrix;
}

int Matrix2D::get_column_size(){
    return num_columns;
}
int Matrix2D::get_row_size(){
    return num_rows;
}
float** Matrix2D::get_pt_to_matrix(){
    return matrix;
}
float Matrix2D::get_element(int x, int y){
    if(x >= num_rows || y >= num_columns || x < 0 || y < 0){ 
        try{
            throw 1; //throws error for desired index out of range
        }
        catch(int e) {
            std::cout << "Error, Index: " << x << "," << y <<  " is out of range of a matrix of size: " << num_rows << "," << num_columns << std::endl;
            exit(-1);
        }
    } else{
        return matrix[x][y];
    }
}

void Matrix2D::set_element_value(int x, int y, float value){
    matrix[x][y] = value;
}



int main(){
    //tests
    Matrix2D m1(3,3,1);
    Matrix2D m2(3,3,2);
    Matrix2D m3 = m1 + m2 + m2; //addition
    std::cout << m3.get_element(2,2) << std::endl; //getting elements should be 5 if addition worked 
    m3.set_element_value(2,2,6); //element editing
    std::cout << m3.get_element(2,2) << std::endl; //should be 6
    Matrix2D m4 = m2 * m1;
    std::cout << m4.get_element(2,2) << std::endl; //should be 2

    Matrix2D m5 = m2 - m1;
    std::cout << m5.get_element(2,2) << std::endl; //should be 1

    Matrix2D m6 = m5 * 3;
    std::cout << m6.get_element(2,2) << std::endl; //should be 3
    return 0; 
}
