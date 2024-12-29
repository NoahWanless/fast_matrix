#include "matrix2d.h"
#include <stdio.h>
//g++ -fPIC -shared -o matrix.so matrix2d.cpp c_wrapper.cpp

extern "C"{

    Matrix2D* matrix2d_new(int rows, int columns, float seed_num){
        return new Matrix2D(rows,columns,seed_num); //pointer to the matrix object in c++ on heap
    }

    void matrix2d_delete(Matrix2D* pt){ 
        delete (pt->get_pt_to_matrix()); //deletes the pointer inside the cpp matrix object
        delete pt;
    }    

    Matrix2D* matrix2d_copy(Matrix2D* pt){ 
        Matrix2D* temp_pt; //matrix pt"
        Matrix2D temp(*pt); //makes a new copied matrix object using the one passed in 
        
        
        temp_pt = &temp;
        
        return temp_pt;
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
    /*
    Matrix2D* matrix2d_addition(Matrix2D* pt, Matrix2D* pt2){ //!A LOT OF THE BELLOW MAY BREAK WHEN BINDED TOGETHER (THE THINGS THAT RETRUN THE ADDRESS OF STACK MEMORY WHICH THE THINGY TAKES ISSUE WITH)
        Matrix2D pt_added = *pt + *pt2;

        Matrix2D* pt_final = &(pt_added);
        printf("testing");
        printf("%d",(pt_final->get_row_size()));
        printf("%d",(pt_final->get_column_size()));
        return pt_final; 
    }
    */
    void matrix2d_add(Matrix2D* pt, Matrix2D* pt2){
        pt->addMatrix(*pt2);
    }
    void matrix2d_subtract(Matrix2D* pt, Matrix2D* pt2){
        pt->subtract_Matrix(*pt2);
    }
    void multiply_matrix_with_matrix(Matrix2D* pt, Matrix2D* pt2){
        pt->multiply_matrix_with_matrix(*pt2);
    }
    void multiply_matrix_with_scalar(Matrix2D* pt, float scalar){
        pt->multiply_matrix_with_scaler(scalar);
    }
    float* vector_matrix_dot_prod(Matrix2D* pt, float* vec, int vec_len){
        return pt->vector_matrix_dot_product(vec,vec_len);
    }
    Matrix2D* get_transpose(Matrix2D* pt){
        return pt->get_Transpose();
    }
}