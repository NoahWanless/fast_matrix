#ifndef MATRIX2D_H
#define MATRIX2D_H


class Matrix2D{
    private:
        float** matrix;
        int num_rows;
        int num_columns;

    public:
        
        Matrix2D(int rows, int columns, float seed_Num = 0);
        Matrix2D(Matrix2D& otherMatrix);
        Matrix2D* get_Transpose();
        
        ~Matrix2D();

        void addMatrix(Matrix2D& otherMatrix);
        void subtract_Matrix(Matrix2D& otherMatrix);
        void multiply_matrix_with_matrix(Matrix2D& otherMatrix);
        float** copyMatrixPt();
        void multiply_matrix_with_scaler(float scaler);
        
        float* vector_matrix_dot_product(float* vec, int length);

        float* operator*(float *array); 
        
        
        

        float get_element(int x, int y);
        
        float** get_pt_to_matrix();

        int get_column_size();
        int get_row_size();

        void set_element_value(int x, int y, float value);



};


#endif