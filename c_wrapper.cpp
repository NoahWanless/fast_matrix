#include "matrix2d.h"
#include <stdio.h>
//bellow is what im running in terminal to complie the CDLL libaray
//g++ -fPIC -shared -o matrix.so matrix2d.cpp c_wrapper.cpp
//where the so file is the CDLL, the matrix2d.cpp is the file where im pulling c++ code from, and c_wrapper.cpp is where the c code is coming from
extern "C"{

    //all these functions call the c++ functions in regular c so ctypes can access them

    Matrix2D* matrix2d_new(int rows, int columns, float seed_num){
        return new Matrix2D(rows,columns,seed_num); //pointer to the matrix object in c++ on heap
    }

    Matrix2D* matrix2d_new_from_other_matrix(Matrix2D* otherMatrix){
        return new Matrix2D(*otherMatrix);
    }

    void matrix2d_delete(Matrix2D* pt){ 
        delete (pt->get_pt_to_matrix()); //deletes the pointer inside the cpp matrix object
        delete pt;
    }    
    Matrix2D* multiply_matrix_with_matrix(Matrix2D* pt, Matrix2D* pt2){
        Matrix2D* temp_pt;
        Matrix2D temp = pt->multiply_matrix_with_matrix(*pt2);
        temp_pt = &temp;
        return temp_pt;
    }
    Matrix2D* get_transpose(Matrix2D* pt){
        return pt->get_Transpose();
    }
    void delete_pt(Matrix2D* pt){
        delete pt;
    }
    void set_matrix_pt_value(Matrix2D* pt, Matrix2D* pt2){
        pt->set_matrix_pt_value(pt2->get_pt_to_matrix());
    }


    float matrix2d_get_element(Matrix2D* pt, int x, int y){
        return pt->get_element(x,y);
    }

    void matrix2d_set_element(Matrix2D* pt, int x, int y, float value){
        pt->set_element_value(x,y,value);
    }

    int matrix2d_get_row_size(Matrix2D* pt){
        return pt->get_row_size();
    }
    int matrix2d_get_column_size(Matrix2D* pt){
        return pt->get_column_size();
    }

    void matrix2d_add(Matrix2D* pt, Matrix2D* pt2){
        pt->addMatrix(*pt2);
    }
    void matrix2d_subtract(Matrix2D* pt, Matrix2D* pt2){
        pt->subtract_Matrix(*pt2);
    }
    
    void multiply_matrix_with_scalar(Matrix2D* pt, float scalar){
        pt->multiply_matrix_with_scaler(scalar);
    }
    float* vector_matrix_dot_prod(Matrix2D* pt, float* vec, int vec_len){
        return pt->vector_matrix_dot_product(vec,vec_len);
    }


    
}