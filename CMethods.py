"""from ctypes import cdll
lib = cdll.LoadLibrary('./libfoo.so')"""
from ctypes import cdll
lib = cdll.LoadLibrary("./builds/libCAlgos.so")


def test():
    lib.Foo_bar("hello".encode())

def findAddressChanges(filenameInput, filenameOutput):
    lib.findAddressChanges(filenameInput, filenameOutput)

"""class Foo(object):
    def __init__(self):
        self.obj = lib.Foo_new()

    def bar(self):
        lib.Foo_bar(self.obj)"""