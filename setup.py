from setuptools import setup, find_packages
import subprocess
import sys
import shutil
import pynq_dma

def makefile():
    srclib = "src/hardware/libpynq_dma.so"
    dstlib = "pynq_dma/pynq_dma.so"
    #status = subprocess.check_call(["make", "-C", "src/hardware"])
    if status is not 0:
        print("Error while running make..Exiting")
        sys.exit(1)
    shutil.copyfile(srclib,dstlib)

if len(sys.argv) > 1 and sys.argv[1] == 'install':
    makefile()

setup(
    name = "pynq_dma",
    version = fir.__version__,
    url = 'https://github.com/schelleg/pynq_dma',
    license = 'BSD-3',
    author = "Graham Schelle",
    author_email = "graham.schelle@xilinx.com",
    packages = ['pynq_dma'],
    package_data = {
    '' : ['*.bit','*.tcl','*.so'],
    },
    description = "A simple SDSoC example"
)
