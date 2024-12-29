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
    for(int i = 0; i < rows; i++){ 
        for(int j = 0; j < columns; j++){ 
             matrix[i][j] = seed_Num; //seeds array

        }
    }
}

Matrix2D::Matrix2D(Matrix2D& otherMatrix){ //this is the copy constructor
    matrix = otherMatrix.copyMatrixPt();
    num_rows = otherMatrix.get_row_size();
    num_columns = otherMatrix.get_column_size();
}

Matrix2D::~Matrix2D(){
    for(int i = 0; i < num_rows; i++){
        delete matrix[i];
    }
    delete matrix;
}

Matrix2D* Matrix2D::get_Transpose(){
    //Here when making the empty array, it flips the dimionsions, meaning the new matrix's number of rows is the old matrixs number of columns
    Matrix2D new_mat(num_columns,num_rows,0);
    Matrix2D* pt_to_matrix = &(new_mat);

    for(int i = 0; i < num_columns; i++){ 
        for(int j = 0; j < num_rows; j++){ 
            float value =  matrix[i][j];
            pt_to_matrix->set_element_value(j,i,value);
        }
    } 
    std::cout << "Here is the matrixs size: " << pt_to_matrix->get_row_size() << " by " << pt_to_matrix->get_column_size() << std::endl;
    return pt_to_matrix;
}

float** Matrix2D::copyMatrixPt(){ //returns copy of matrix pt on heap 
    float** temp_matrix = new float*[num_columns]; //on heap, list of pointers to lists of floats
    for(int i = 0; i < num_rows;i++){
        temp_matrix[i] = new float[num_columns];  //actaually givees the pointers lists of floats to point to, on heap
    }
    for(int j = 0; j < num_columns; j++){ //fills array with other arrays on heap
        temp_matrix[j] = new float[num_rows];
    }   
    for(int i = 0; i < num_columns; i++){ 
        for(int j = 0; j < num_rows; j++){ 
             temp_matrix[i][j] = this->get_element(i,j); //puts array in of other value

        }
    }
    return temp_matrix;

}

void Matrix2D::addMatrix(Matrix2D& otherMatrix){
    int otherRowSize = otherMatrix.get_row_size();
    int otherColumnSize = otherMatrix.get_column_size();
    if(num_rows != otherRowSize || num_columns != otherColumnSize){//check sizes
        try{
            throw 1; //throws error for desired index out of range
        }
        catch(int e) {
            std::cout << "Error, Matrix sizes do not match" << std::endl;
            std::cout << "Matrix 1: " << num_rows << " by " << num_columns << std::endl;
            std::cout << "Matrix 2: " << otherRowSize << " by " << otherColumnSize << std::endl;
            exit(-1);
        }
    }
    for (int i = 0; i < this->num_rows; i++){
        for (int j = 0; j < this->num_columns; j++){
            float value = this->matrix[i][j] + otherMatrix.matrix[i][j];
            matrix[i][j] = value;
        }
    }

}

void Matrix2D::subtract_Matrix(Matrix2D& otherMatrix){
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
    for (int i = 0; i < this->num_rows; i++){
        for (int j = 0; j < this->num_columns; j++){
            float value = this->matrix[i][j] - otherMatrix.matrix[i][j];
            matrix[i][j] = value;
        }
    }
}

void Matrix2D::multiply_matrix_with_matrix(Matrix2D& otherMatrix){ //applies to itself
    if(num_columns != otherMatrix.get_row_size()){ 
        try{throw 1;}
        catch(int e){//throws error if internal sizes dont match
            std::cout << "Row size of matrix one does not match with column size of matrix 2" << std::endl;
            exit(-1);
        }
    }

    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < otherMatrix.get_column_size(); j++){
            for(int k = 0; k < otherMatrix.get_row_size(); k++){
                float value = this->get_element(i,k) * otherMatrix.get_element(k,j);
                this->set_element_value(i,j,value);
            }
        }
    }
    
}

void Matrix2D::multiply_matrix_with_scaler(float scaler){
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_columns; j++){
            float value = this->get_element(i,j) * scaler;
            this->set_element_value(i,j,value);
        }
    }
}

float* Matrix2D::vector_matrix_dot_product(float* vec, int length){ //!|||||--------UNTESTED, SO FURTURE ME PLEASE TEST THIS OUT---------|||||
    if(num_columns != length){//check sizes
        try{
            throw 1; //throws error for desired index out of range
        }
        catch(int e) {
            std::cout << "Error, Matrix column size and vector length do not match" << std::endl;
            exit(-1);
        }
    }

    float* new_vec = new float[length]; //on heap, list of float    #!\\\\\\-----DONT KNOW IF THIS WILL NEED TO BE DELETED LATER ON, OR IF IT CAN JUST BE LEFT-----||||
    for(int i = 0; i < num_rows; i++){
        float sum = 0;
        for(int j = 0; j < num_columns; j++){
            sum += this->get_element(i,j) * vec[j];
        }
        new_vec[i] = sum;
    }
    return new_vec;
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
    Matrix2D m1(3,3,1); //2d matri of size 3x3 with 1's in it

    float list[3] = {1,1,1};
    std::cout << "Beginning of dot product test" << std::endl;
    float* lfinal = m1.vector_matrix_dot_product(list,3);
    for(int i = 0; i < 3; i ++){
        std::cout << lfinal[i] << std::endl;
    }
    std::cout << "end of dot product test" << std::endl;
    Matrix2D m2(3,3,2);




    std::cout << "beginning of test Zero" << std::endl; 
    std::cout << "-----------------------------" << std::endl; 
    std::cout << "Here is m1's element" << std::endl;
    std::cout << m1.get_element(2,2) << std::endl;
    Matrix2D m10(m1);
    std::cout << "Here is m10's element" << std::endl;
    std::cout << m10.get_element(2,2) << std::endl;
    std::cout << "------------Now a change has occured-----------------" << std::endl; 
    m1.set_element_value(2,2,7);
    std::cout << "Here is m1's element" << std::endl;
    std::cout << m1.get_element(2,2) << std::endl;
    std::cout << "Here is m10's element" << std::endl;
    std::cout << m10.get_element(2,2) << std::endl;
    std::cout << "-----------------------------" << std::endl; 
    
    return 0; 
}
