#include "matrix2d.h"

//g++ -fPIC -shared -o matrix.so matrix2d.cpp c_wrapper.cpp

extern "C"{

    Matrix2D* matrix2d_new(int rows, int columns, float seed_num){
        return new Matrix2D(rows,columns,seed_num); //pointer to the matrix object in c++ on heap
    }

    void matrix2d_delete(Matrix2D* pt){ 
        delete (pt->get_pt_to_matrix()); //deletes the pointer inside the cpp matrix object
        delete pt;
    }    

    float matrix2d_get_element(Matrix2D* pt, int x, int y){
        return pt->get_element(x,y);
    }

    Matrix2D* matrix2d_addition(Matrix2D* pt, Matrix2D* pt2){ //!A LOT OF THE BELLOW MAY BREAK WHEN BINDED TOGETHER (THE THINGS THAT RETRUN THE ADDRESS OF STACK MEMORY WHICH THE THINGY TAKES ISSUE WITH)
        Matrix2D pt_added = *pt + *pt2;
        return &(pt_added); //dereferences to the matrix value to add then, then makes it a pointer to return 
    }

    Matrix2D* matrix2d_subtraction(Matrix2D* pt, Matrix2D* pt2){
        Matrix2D pt_subbed = *pt - *pt2;
        return &(pt_subbed); //dereferences to the matrix value to add then, then makes it a pointer to return 
    }

    Matrix2D* matrix2d_matrix_to_matrix_mult(Matrix2D* pt, Matrix2D* pt2){
        Matrix2D pt_multed = *pt * *pt2;
        return &(pt_multed); //dereferences to the matrix value to add then, then makes it a pointer to return 
    }
    Matrix2D* matrix2d_matrix_scaled(Matrix2D* pt,float scalar){
        Matrix2D pt_scaled = *pt * scalar;
        return &(pt_scaled); //dereferences to the matrix value to add then, then makes it a pointer to return 
    }

}