#ifndef MATRIX2D_H
#define MATRIX2D_H


class Matrix2D{
    private:
        float** matrix;
        int num_rows;
        int num_columns;

    public:
        
        Matrix2D(int rows, int columns, float seed_Num = 0);
        
        ~Matrix2D();

        Matrix2D operator+(Matrix2D& otherMatrix);
        Matrix2D operator-(Matrix2D& otherMatrix);
        Matrix2D operator*(Matrix2D& otherMatrix);
        float* operator*(float *array); 
        Matrix2D operator*(float scalar);
        
        

        float get_element(int x, int y);
        
        float** get_pt_to_matrix();

        int get_column_size();
        int get_row_size();

        void set_element_value(int x, int y, float value);

        //int[] get_shape();

        //float[] get_column(int index);

        //float[] get_row(int index);


};


#endif