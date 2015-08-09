from libcpp.vector cimport vector

import numpy as np
cimport numpy as np

ctypedef np.float64_t DTYPE_t

# test declare the statvector class
cdef extern from "statvector.hh" namespace "ds":
    ctypedef vector[double] record_t
    cdef cppclass statvector:
        # constructors
        statvector(record_t &data) except +
         
        # size / other information
        size_t count()
        record_t& raw()

        # statistics
        double min()
        double max()
        double sum()
        double std()
        double mean()
        double percentile(float percent) except +
        
        # element access
        double at(const size_t &idx)

cdef class PyStatvector:
    cdef statvector* svec
    def __cinit__(self, sv):#np.ndarray[DTYPE_t, ndim=1, mode='c'] data):
        self.svec = new statvector(sv)

        if self.svec is NULL:
            raise MemoryError()

    def __dealloc__(self):
        if self.svec is not NULL:
            del self.svec

    def percentile(self, float percent):
        if percent < 1 or percent > 0:
            raise ValueError('`percent` must be in range [0,1]')
        return self.svec.percentile(percent) # internal error complains about deallocation?
