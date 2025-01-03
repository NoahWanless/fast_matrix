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
     
    for(int i = 0; i < rows; i++){ 
        for(int j = 0; j < columns; j++){ 
             matrix[i][j] = seed_Num; //seeds array

        }
    }
}

Matrix2D::Matrix2D(const Matrix2D& otherMatrix){ //this is the copy constructor
    matrix = otherMatrix.matrix;
}

Matrix2D::~Matrix2D(){
    for(int i = 0; i < num_rows; i++){
        delete matrix[i];
    }
    delete matrix;
}

Matrix2D* Matrix2D::get_Transpose(){ //this function isnt used in the python wrapper but thought i keep it anyways
    //Here when making the empty array, it flips the dimionsions, meaning the new matrix's number of rows is the old matrixs number of columns
    Matrix2D new_mat(num_columns,num_rows,0);
    Matrix2D* pt_to_matrix = &(new_mat);

    for(int i = 0; i < num_columns; i++){ 
        for(int j = 0; j < num_rows; j++){ 
            float value =  matrix[i][j];
            pt_to_matrix->set_element_value(j,i,value);
        }
    } 
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

void Matrix2D::addMatrix(Matrix2D& otherMatrix){ //this function applies the operation to itself, not returing a new object
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

void Matrix2D::subtract_Matrix(Matrix2D& otherMatrix){//this function applies the operation to itself, not returing a new object
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

Matrix2D Matrix2D::multiply_matrix_with_matrix(Matrix2D& otherMatrix){ //applies to itself
    if(num_columns != otherMatrix.get_row_size()){  //because internal dimensions of matrix product must match
        try{throw 1;}
        catch(int e){//throws error if internal sizes dont match
            std::cout << "Row size of matrix one does not match with column size of matrix 2" << std::endl;
            exit(-1);
        }
    }
    Matrix2D temp_obj(num_rows,otherMatrix.get_row_size(),0);

    for(int i = 0; i < num_rows; i++){ //generic matrix product formula
        for(int j = 0; j < otherMatrix.get_column_size(); j++){
            float sum = 0;
            for(int k = 0; k < num_columns; k++){
                float value = this->get_element(i,k) * otherMatrix.get_element(k,j);
                sum +=value;
                
            }
            temp_obj.set_element_value(i,j,sum);
            //this->set_element_value(i,j,sum);
        }
    }
    return temp_obj;
    
}

void Matrix2D::multiply_matrix_with_scaler(float scaler){//this function applies the operation to itself, not returing a new object
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_columns; j++){
            float value = this->get_element(i,j) * scaler;
            this->set_element_value(i,j,value);
        }
    }
}

float* Matrix2D::vector_matrix_dot_product(float* vec, int length){ //this function applies the operation to itself but does return a new list object
    if(num_columns != length){//check sizes
        try{
            throw 1; //throws error for desired index out of range
        }
        catch(int e) {
            std::cout << "Error, Matrix column size and vector length do not match" << std::endl;
            exit(-1);
        }
    }

    float* new_vec = new float[length]; //on heap, list of float    

    for(int i = 0; i < num_rows; i++){ //basic matrix vector product
        float sum = 0;
        for(int j = 0; j < num_columns; j++){ 
            sum += this->get_element(i,j) * vec[j];
        }
        new_vec[i] = sum;
    }
    return new_vec;
}

void Matrix2D::print_matrix(){
    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_columns; j++){
            std::cout << matrix[i][j] << " ";
        }   
        std::cout <<"\n";
    }
    
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

void Matrix2D::set_matrix_pt_value(float** pt){
    matrix = pt;
}


int main(){
    //tests
    std::cout << "Here are the tests/demonstrations of the matrix object:" << std::endl;
    std::cout << "||--------------|| Matrix copy: ||--------------||" << std::endl;
    Matrix2D o2(3,3,1); 
    o2.print_matrix();
    //Matrix2D o3 = o2.copyMatrix();
    //o3.print_matrix();

    std::cout << "||--------------|| Matrix addition: ||--------------||" << std::endl;
    Matrix2D m1(3,3,1); //2d matri of size 3x3 with 1's in it
    Matrix2D m2(3,3,1); 
    std::cout << "OG Matrix:" << std::endl;
    m1.print_matrix();
    m1.addMatrix(m2);
    std::cout << "New Matrix:" << std::endl;
    m1.print_matrix();
    std::cout << "||--------------|| Matrix subtraction: ||--------------||" << std::endl;
    Matrix2D s1(3,3,1); //2d matri of size 3x3 with 1's in it
    Matrix2D s2(3,3,1); 
    std::cout << "OG Matrix:" << std::endl;
    s1.print_matrix();
    s1.subtract_Matrix(s2);
    std::cout << "New Matrix:" << std::endl;
    s1.print_matrix();
    std::cout << "||--------------|| Matrix matrix product: ||--------------||" << std::endl;
    Matrix2D g1(2,2,1); 
    Matrix2D g2(2,2,2); 
    std::cout << "OG Matrix 1:" << std::endl;
    g1.print_matrix();
    std::cout << "OG Matrix 2:" << std::endl;
    g2.print_matrix();
    Matrix2D g3 = g1.multiply_matrix_with_matrix(g2);
    std::cout << "New Matrix:" << std::endl;
    g3.print_matrix();
    std::cout << "||--------------|| Matrix product with scalar: ||--------------||" << std::endl;
    Matrix2D p1(3,3,1); //2d matri of size 3x3 with 1's in it
    int value = 2;
    std::cout << "OG Matrix:" << std::endl;
    p1.print_matrix();
    p1.multiply_matrix_with_scaler(value);
    std::cout << "New Matrix:" << std::endl;
    p1.print_matrix();
    std::cout << "||--------------|| Matrix product with vector ||--------------||" << std::endl;
    Matrix2D v1(3,3,1); //2d matri of size 3x3 with 1's in it
    float l[3] = {1,1,1};
    std::cout << "OG Matrix:" << std::endl;
    v1.print_matrix();
    float* l2;
    l2 = v1.vector_matrix_dot_product(l,3);
    std::cout << "Output:" << std::endl;
    std::cout << l2[0] << std::endl;
    std::cout << l2[1] << std::endl;
    std::cout << l2[2] << std::endl;
    
    return 0; 
}
