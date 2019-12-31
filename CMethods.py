"""from ctypes import cdll
lib = cdll.LoadLibrary('./libfoo.so')"""
from ctypes import cdll
lib = cdll.LoadLibrary("./builds/libCAlgos.so")


def test():
    lib.Foo_bar("hello".encode())

def findAddressChanges(filenameInput, filenameOutput, candleFilePath, summariesInput, algoType):
    lib.findAddressChanges(filenameInput, filenameOutput, candleFilePath, summariesInput, algoType)

"""class Foo(object):
    def __init__(self):
        self.obj = lib.Foo_new()

    def bar(self):
        lib.Foo_bar(self.obj)"""