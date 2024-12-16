import ctypes

#!||-----|| IMPORTANT, IT IS NECCASARY TO MAKE SURE YOU DELETE THE POINTER TO THE MATRIX OBJECT IN C++ BECAUSE IT IS ON THE HEAP ||-----||
c_matrix_lib = ctypes.CDLL("./matrix.so")



class Matrix2D:
    def __init__(self,x,y,seed_num):
        print("Here are my sizes of the array: ")
        print(x)
        print(y)
        c_matrix_lib.matrix2d_new.argtypes = [ctypes.c_int,ctypes.c_int,ctypes.c_float]
        c_matrix_lib.matrix2d_new.restype = ctypes.c_void_p

        c_matrix_lib.matrix2d_get_element.argtypes = [ctypes.c_void_p,ctypes.c_int,ctypes.c_int]
        c_matrix_lib.matrix2d_get_element.restype = ctypes.c_float

        c_matrix_lib.matrix2d_delete.argtypes = [ctypes.c_void_p]

        print("We are about to make our object!")
        self._matrix = c_matrix_lib.matrix2d_new(x,y,seed_num)
        print("We made our object!")

    def get_element(self,x,y):
        return c_matrix_lib.matrix2d_get_element(self._matrix,x,y)
        
    """
    def __del__(self):
        print("We are about to delete our object!")
        c_matrix_lib.matrix2d_delete(self._matrix)
        print("We deleted our object!")
        """

m1 = Matrix2D(2,2,3)
print(m1.get_element(1,1))