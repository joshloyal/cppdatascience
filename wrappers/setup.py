from distutils.core import setup, Extension
from Cython.Build import cythonize
import numpy

source_dir = '../dataframe/src/'
sourcefiles = ['statvec.pyx', 
               source_dir+'csv_reader.cxx', 
               source_dir+'statvector.cxx']
extensions = [
    Extension('statvec', sourcefiles, language='c++',
        include_dirs = ['../dataframe', '../dataframe/include', numpy.get_include()],
        extra_compile_args=['-std=c++11', '-stdlib=libc++']
        )]

setup(ext_modules = cythonize(extensions))
