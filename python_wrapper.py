import ctypes
import copy 
import numpy

#!||-----|| IMPORTANT, IT IS NECCASARY TO MAKE SURE YOU DELETE THE POINTER TO THE MATRIX OBJECT IN C++ BECAUSE IT IS ON THE HEAP ||-----||
c_matrix_lib = ctypes.CDLL("./matrix.so")
import time
def timeit(func):
    def wrapper(*args, **kwargs):
        start = time.perf_counter()
        result = func(*args, **kwargs)
        end = time.perf_counter()
        elapsed = end - start
        print(f'Time taken: {elapsed:.6f} seconds')
        return result
    return wrapper





class Matrix2D:
    def __init__(self,x,y,seed_num):
        c_matrix_lib.matrix2d_new.argtypes = [ctypes.c_int,ctypes.c_int,ctypes.c_float]
        c_matrix_lib.matrix2d_new.restype = ctypes.c_void_p

        c_matrix_lib.matrix2d_copy.argtypes = [ctypes.c_void_p]
        c_matrix_lib.matrix2d_copy.restype = ctypes.c_void_p

        c_matrix_lib.get_transpose.argtypes = [ctypes.c_void_p]
        c_matrix_lib.get_transpose.restype = ctypes.c_void_p

        c_matrix_lib.matrix2d_get_element.argtypes = [ctypes.c_void_p,ctypes.c_int,ctypes.c_int]
        c_matrix_lib.matrix2d_get_element.restype = ctypes.c_float

        c_matrix_lib.matrix2d_set_element.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_float]
        
        c_matrix_lib.matrix2d_get_row_size.argtypes = [ctypes.c_void_p]
        c_matrix_lib.matrix2d_get_row_size.restype = ctypes.c_int

        c_matrix_lib.matrix2d_get_column_size.argtypes = [ctypes.c_void_p]
        c_matrix_lib.matrix2d_get_column_size.restype = ctypes.c_int

        c_matrix_lib.matrix2d_add.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
        
        c_matrix_lib.matrix2d_subtract.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
        
        c_matrix_lib.multiply_matrix_with_scalar.argtypes = [ctypes.c_void_p, ctypes.c_float]
        
        float_list_data_type = numpy.ctypeslib.ndpointer(dtype=numpy.float32,ndim=1)
        
        c_matrix_lib.vector_matrix_dot_prod.argtypes = [ctypes.c_void_p,float_list_data_type, ctypes.c_int]
        
        c_matrix_lib.vector_matrix_dot_prod.restype = ctypes.POINTER(ctypes.c_float*y) #this is a ctpyes pointer  #,ay meed a *y maybe
        
        #fliberary.read_array_big_c.restype = None
        #flibera ry.read_array_big_c.argtypes = [dt]
        #g = numpy.zeros((2,4,4),numpy.int32)




        #c_matrix_lib.matrix2d_addition.argtypes = [ctypes.c_void_p,ctypes.c_void_p]
        #c_matrix_lib.matrix2d_addition.restype = ctypes.c_void_p

        c_matrix_lib.multiply_matrix_with_matrix.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
        self.row_size = x
        self.column_size = y
        self._matrix = c_matrix_lib.matrix2d_new(x,y,seed_num)
        
    def copy_matrix_object(self):
        
        print(self._matrix)
        temp_matrix = c_matrix_lib.matrix2d_copy(self._matrix) 
        print(temp_matrix)
        tempObj = Matrix2D(0,0,0)
        tempObj._matrix = temp_matrix
        
        
        return tempObj
        
    
    def get_element(self,x,y):
        return c_matrix_lib.matrix2d_get_element(self._matrix,x,y)
        
    def get_row_size(self):
        return self.row_size
        #return c_matrix_lib.matrix2d_get_row_size(self._matrix)
    
    def get_transpose(self): 
        print("-------------------------------Inside getting transpose funbction")
        temp = Matrix2D(self.get_column_size(),self.get_row_size(),0) 
        for x in range(self.column_size):
            for y in range(self.row_size):
                value = self.get_element(x,y)
                temp.set_element(y,x,value)
        print("-------------------------------leaving getting transpose funbction")
        return temp
        


    def print_matrix(self):
        for x in range(self.row_size):
            for y in range(self.column_size):
                print(self.get_element(x,y),end='')
                print(" ",end='')
            print()
            

    def get_column_size(self):
        return self.column_size
        #return c_matrix_lib.matrix2d_get_column_size(self._matrix)
    
    def set_element(self,x,y,value):
        c_matrix_lib.matrix2d_set_element(self._matrix,x,y,value)

    def _matrix_add(self,matrix2): #internal use funciton
        c_matrix_lib.matrix2d_add(self._matrix,matrix2._matrix)

    def _matrix_add_using_pt(self,matrix2): #internal use funciton adds with a pt to c object no with python object
        c_matrix_lib.matrix2d_add(self._matrix,matrix2)

    def _matrix_subtract(self,matrix2):#internal use funciton
        c_matrix_lib.matrix2d_subtract(self._matrix,matrix2._matrix)
    def _matrix_multiply_by_matrix(self,matrix2):#internal use funciton
        c_matrix_lib.multiply_matrix_with_matrix(self._matrix,matrix2._matrix)
    def _matrix_multi_by_scalar(self,scalar):
        c_matrix_lib.multiply_matrix_with_scalar(self._matrix,scalar)

    @timeit
    def add_matrix(self,matrix2):
       temp_obj = Matrix2D(self.get_row_size(),self.get_column_size(),0)
       temp_obj._matrix_add(self)
       temp_obj._matrix_add(matrix2)
       return temp_obj
    
    def subtract_matrix(self,matrix2):
       temp_obj = Matrix2D(self.get_row_size(),self.get_column_size(),0)
       temp_obj._matrix_add(self)
       temp_obj._matrix_subtract(matrix2)
       return temp_obj
       
    def multiply_matrix_with_matrix(self,matrix2):
       temp_obj = Matrix2D(self.get_row_size(),self.get_column_size(),0)
       temp_obj._matrix_add(self)
       temp_obj._matrix_multiply_by_matrix(matrix2)
       return temp_obj
    
    def multiply_matrix_with_scalar(self,scaler): #! UNTESTED   
        temp_obj = Matrix2D(self.get_row_size(),self.get_column_size(),0)
        temp_obj._matrix_add(self)
        temp_obj._matrix_multi_by_scalar(scaler)
        return temp_obj
    @timeit
    def dot_product(self,list):

        length = len(list) #length we will be dealing wiht
        temp = numpy.array(list,dtype=ctypes.c_float) #makes the array to be passed in as numpy one (i cant find any better way of doing this)
        
        print("we are now about to preform the dot porduct")
        final = c_matrix_lib.vector_matrix_dot_prod(self._matrix,temp,length)

        print("Dot product done!")
        return_list = []
        print(final.contents) #the answer is a list but of the ctypes type
        for i in range(self.get_row_size()):
            return_list.append(final.contents[i])
        return return_list


    """
    def __del__(self):
        print("We are about to delete our object!")
        c_matrix_lib.matrix2d_delete(self._matrix)'

        print("We deleted our object!")
        """



print("Now in python")
m100 = Matrix2D(3,3,1)
m100.set_element(2,1,6)
m100.print_matrix()

m110 = m100.get_transpose()
m110.print_matrix()
l100 = [1,1,1]

new_list = m100.dot_product(l100)
print("----------------------------------||||||||||||||||||||||")
print(new_list[0])
print(new_list[1])
print(new_list[2])

print("----------------------------------||||||||||||||||||||||")
m1 = Matrix2D(3,3,3)
m2 = Matrix2D(3,3,3)
print(m1.get_element(1,1))
print("Value before addition has occuered")
print(m1.get_element(1,1))
m3 = m1.add_matrix(m2)
print("Value after addition has occuered")
print(m1.get_element(1,1))
print(m3.get_element(1,1))
print("----------------------------------")
print("Value before subtraction has occuered")
print(m3.get_element(1,1))
m4 = m3.subtract_matrix(m2)
print("Value after subtraction has occuered")
print(m3.get_element(1,1))
print(m4.get_element(1,1))