import os
import cffi
from pynq import Bitstream,PL


BS_SEARCH_PATH = os.path.dirname(os.path.realpath(__file__))

BITFILE = BS_SEARCH_PATH + "/pynq_dma.bit"
LIBRARY = BS_SEARCH_PATH + "/libpynq_dma.so"

class pynq_dma():

    def __init__(self):
        self.bitfile = BITFILE
        self.libfile = LIBRARY
 
        ffi = cffi.FFI()
        ffi.cdef("void _p0_array_zero_copy_1_noasync(char a[1048576], char b[1048576]);")
        self.lib = ffi.dlopen(self.libfile)
        if PL.bitfile_name != self.bitfile:
                self.download_bitstream()

    def download_bitstream(self):
        Bitstream(self.bitfile).download()

    def copy(self,datain,dataout):
        if "cdata" not in str(datain) or "cdata" not in str(dataout):
                raise RuntimeError("Unknown buffer type!")
        self.lib._p0_array_zero_copy_1_noasync(datain,dataout)
