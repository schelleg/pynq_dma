
import cffi
from pynq_dma import general_const
from pynq import Bitstream,PL

pynq_dma_overlay_fn = "pynq_dma.bit"

class pynq_dma():

    def __init__(self):
        self.bitfile = general_const.BITFILE
        self.libfile = general_const.LIBRARY
        self.nshift_reg = 85
        ffi = cffi.FFI()
        ffi.cdef("void _p0_cpp_FIR_0(void *din, void *dout, int dlen);")
        self.lib = ffi.dlopen(self.libfile)
        if PL.bitfile_name != self.bitfile:
                self.download_bitstream()

    def download_bitstream(self):

        global pynq_dma_overlay
        pynq_dma_overlay = Bitstream(self.bitfile)
        pynq_dma_overlay.download()

    def copy(self,datain,dataout):

        if "cdata" not in str(datain) or "cdata" not in str(dataout):
                raise RuntimeError("Unknown buffer type!")
        self.lib._p0_cpp_FIR_0(datain,dataout,datalen)
