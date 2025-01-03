import ctypes
import copy 
import numpy
import time

c_matrix_lib = ctypes.CDLL("./matrix.so")




class Matrix2D:
    def __init__(self,x,y,seed_num):
        c_matrix_lib.matrix2d_new.argtypes = [ctypes.c_int,ctypes.c_int,ctypes.c_float]
        c_matrix_lib.matrix2d_new.restype = ctypes.c_void_p

        c_matrix_lib.matrix2d_new_from_other_matrix = [ctypes.c_void_p]
        c_matrix_lib.matrix2d_new_from_other_matrix = ctypes.c_void_p

        c_matrix_lib.get_transpose.argtypes = [ctypes.c_void_p]
        c_matrix_lib.get_transpose.restype = ctypes.c_void_p

        c_matrix_lib.matrix2d_get_element.argtypes = [ctypes.c_void_p,ctypes.c_int,ctypes.c_int]
        c_matrix_lib.matrix2d_get_element.restype = ctypes.c_float

        c_matrix_lib.matrix2d_set_element.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_float]

        c_matrix_lib.set_matrix_pt_value.argtypes = [ctypes.c_void_p,ctypes.c_void_p]
        
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
    
        c_matrix_lib.multiply_matrix_with_matrix.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
        c_matrix_lib.multiply_matrix_with_matrix.restype = ctypes.c_void_p


        self.row_size = x
        self.column_size = y
        self._matrix = c_matrix_lib.matrix2d_new(x,y,seed_num)

    
    def delete_pt(self): #this deletes the internal pointer to the c matrix object, i personally have seen no problems with not using it, but its here regardless if needed
        print("deleting pt")
        c_matrix_lib.matrix2d_delete(self._matrix)
        print("pt gone ")
        
        
    def copy_matrix_object(self):
        temp_obj = Matrix2D(self.row_size,self.column_size,0)
        temp_obj._matrix_add(self)
        return temp_obj
        
    
    def get_element(self,x,y):
        return c_matrix_lib.matrix2d_get_element(self._matrix,x,y)
        
    def get_row_size(self):
        return self.row_size

    def get_column_size(self):
        return self.column_size    
    
    def get_transpose(self): 
        temp = Matrix2D(self.get_column_size(),self.get_row_size(),0)  #makes empty matrix of flipped size
        for x in range(self.column_size):
            for y in range(self.row_size):
                value = self.get_element(x,y)
                temp.set_element(y,x,value)
        
        return temp
        


    def print_matrix(self):
        for x in range(self.row_size):
            for y in range(self.column_size):
                print(self.get_element(x,y),end='')
                print(" ",end='')
            print()
            

    
    def set_element(self,x,y,value):
        c_matrix_lib.matrix2d_set_element(self._matrix,x,y,value)





    
    #_____||these functions before the operation on the matrix object itself, not returning a new matrix object, these will mostly be used internally
    def _matrix_add(self,matrix2): 
        c_matrix_lib.matrix2d_add(self._matrix,matrix2._matrix)

    def _matrix_add_using_pt(self,matrix2): 
        c_matrix_lib.matrix2d_add(self._matrix,matrix2)

    def _matrix_subtract(self,matrix2):
        c_matrix_lib.matrix2d_subtract(self._matrix,matrix2._matrix)

    def _matrix_multiply_by_matrix(self,matrix2):
        c_matrix_lib.multiply_matrix_with_matrix(self._matrix,matrix2._matrix)

    def _matrix_multi_by_scalar(self,scalar):
        c_matrix_lib.multiply_matrix_with_scalar(self._matrix,scalar)
    #_____||




    #_____||all functions from here on out return a new matrix returns new matrix object
    def add_matrix(self,matrix2): 
       temp_obj = Matrix2D(self.get_row_size(),self.get_column_size(),0) #make a temp empty matrix
       temp_obj._matrix_add(self) #give the temp matrix the same values as the og matrix
       temp_obj._matrix_add(matrix2) #then perform the actual operation on the temp matrix then return it
       return temp_obj
    #pretty much all the functions from here on out behave this way with different operations
    def subtract_matrix(self,matrix2):
       temp_obj = Matrix2D(self.get_row_size(),self.get_column_size(),0)
       temp_obj._matrix_add(self)
       temp_obj._matrix_subtract(matrix2)
       return temp_obj
    """
    def multiply_matrix_with_matrix(self,matrix2):
       temp_obj = Matrix2D(self.get_row_size(),self.get_column_size(),0)
       temp_obj._matrix_add(self)
       temp_obj._matrix_multiply_by_matrix(matrix2)
       return temp_obj
    """
    def multiply_matrix_with_matrix(self,matrix2):
        temp = Matrix2D(1,1,1)
        temp.delete_pt()
        #temp._matrix = c_matrix_lib.matrix2d_new_from_other_matrix(c_matrix_lib.multiply_matrix_with_matrix(self._matrix,matrix2._matrix))
        #print(type(temp._matrix))
        #pt_value = 
        #print(type(pt_value))
        #temp._matrix =  pt_value
        temp.row_size = self.row_size
        temp.column_size = matrix2.column_size 
        return temp
    
    def multiply_matrix_with_scalar(self,scaler):  
        temp_obj = Matrix2D(self.get_row_size(),self.get_column_size(),0)
        temp_obj._matrix_add(self)
        temp_obj._matrix_multi_by_scalar(scaler)
        return temp_obj
    
    def matrix_vec_product(self,list):
        length = len(list) #length we will be dealing wiht
        temp = numpy.array(list,dtype=ctypes.c_float) #makes the array to be passed in as numpy one (i cant find any better way of doing this)
        final = c_matrix_lib.vector_matrix_dot_prod(self._matrix,temp,length) #final is a list but of the ctypes type
        return_list = [] #needs to be made into a python list
        #print(final.contents) 
        for i in range(self.get_row_size()):
            return_list.append(final.contents[i])
        return return_list
    #_____||
    

    
    


print("||||--------------------|||| Tests/demonstration: ||||--------------------||||")
print("||-------|| Addition ||-------||")
print("Starting matrixs filled with one's")
addition_test1 = Matrix2D(3,3,1)
addition_test2 = Matrix2D(3,3,1)
addition_test3 = addition_test1.add_matrix(addition_test2)
print("Final matrix:")
addition_test3.print_matrix()

print("||-------|| Subtraction ||-------||")
print("Starting matrixs filled with one's")
addition_test1 = Matrix2D(3,3,1)
addition_test2 = Matrix2D(3,3,1)
addition_test3 = addition_test1.subtract_matrix(addition_test2)
print("Final matrix:")
addition_test3.print_matrix()

print("||-------|| Matrix matrix product ||-------||")
print("Starting matrix filled with one")
print("other matrix filled with twos")
matrix_test1 = Matrix2D(3,3,1)
matrix_test2 = Matrix2D(3,3,2)
matrix_test3 = matrix_test1.multiply_matrix_with_matrix(matrix_test2)
print("Final matrix:")
matrix_test3.print_matrix()

print("||-------|| Transpose ||-------||")
transpose_Test1 = Matrix2D(3,3,1)
transpose_Test1.set_element(2,1,6)
print("OG matrix:")
transpose_Test1.print_matrix()
transpose_Test2 = transpose_Test1.get_transpose()
print("Transpose:")
transpose_Test2.print_matrix()

print("||-------|| Matrix vector product ||-------||")
l1 = [1,1,1]
print("OG vector:")
print(l1)
print("OG matrix:")
vec_test1 = Matrix2D(3,3,1)
vec_test1.print_matrix()
print("Matrix vec product outcome:")
new_list = vec_test1.matrix_vec_product(l1)
print(new_list)

print("||-------|| Matrix scalar product ||-------||")
value = 2
scalar_test1 = Matrix2D(3,3,1)
print("OG matrix:")
scalar_test1.print_matrix()
scalar_test2 = scalar_test1.multiply_matrix_with_scalar(2)
print("Matrix after multicplication by scalar two:")
scalar_test2.print_matrix()

print("||-------|| Coping Matrix ||-------||")
cope_test1 = Matrix2D(3,3,1)
cope_test2 = cope_test1.copy_matrix_object()
print("Here is the OG Matrix:")
cope_test1.print_matrix()
print("Here is the Copied Matrix:")
cope_test2.print_matrix()