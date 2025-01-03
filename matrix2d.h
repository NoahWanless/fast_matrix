#ifndef MATRIX2D_H
#define MATRIX2D_H


class Matrix2D{
    private:
        float** matrix;
        int num_rows;
        int num_columns;

    public:
        
        Matrix2D(int rows, int columns, float seed_Num = 0);
        Matrix2D(const Matrix2D& otherMatrix);
        float** copyMatrixPt();
        ~Matrix2D();
        void print_matrix();

        void addMatrix(Matrix2D& otherMatrix);
        void subtract_Matrix(Matrix2D& otherMatrix);
        Matrix2D multiply_matrix_with_matrix(Matrix2D& otherMatrix);
        void multiply_matrix_with_scaler(float scaler);    
        float* vector_matrix_dot_product(float* vec, int length);

        float get_element(int x, int y);
        Matrix2D* get_Transpose();
        float** get_pt_to_matrix();
        int get_column_size();
        int get_row_size();

        void set_element_value(int x, int y, float value);
        void set_matrix_pt_value(float** pt);



};


#endif