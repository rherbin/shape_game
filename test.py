import torch
import torch.nn as nn
import torch.optim as optim
import numpy as np
import ctypes
from random import randint

clibrary = ctypes.CDLL("C:/Users/rherbin/OneDrive/Documents/Github/shape_game/lib.so")
func = clibrary.take_step
func.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int]
func.restype = ctypes.POINTER(ctypes.c_int)

array = [0]+[0]+[randint(0,15) for _ in range(5)] + [16]*15

for i in range(100):
    array = [array[x] for x in range(22)]
    array = (ctypes.c_int * len(array))(*array)
    array = func(array, 1)

    print([array[x] for x in range(22)])