from random import randint
import ctypes

clibrary = ctypes.CDLL("C:/Users/rherbin/OneDrive/Documents/Github/shape_game/lib.so")

import random
from enum import Enum
from collections import namedtuple
import numpy as np

#font = pygame.font.SysFont('arial', 25)

func = clibrary.take_step
func.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int]
func.restype = ctypes.POINTER(ctypes.c_int)

class ShapeGameAI:

    def __init__(self, w=640, h=480):
        self.reset()


    def reset(self):
        # init game state
        self.state = [randint(0,15) for _ in range(1)]+[16]*10
        self.score = 0
        
    def play_step(self, action):

        array = [0]+[self.score]+[x for x in self.state]
        array = (ctypes.c_int * len(array))(*array)

        action = action.index(1)

        new_array = func(array, action)

        self.state = np.array(new_array[2:13])
        if new_array[1] >= 3:
            reward = 10
            self.score = new_array[1]
        elif new_array[0]:
            reward = -10
        elif new_array[1] == 1:
            reward = 5
        else:
            reward = 0
        #print(self.score)

        return reward, bool(new_array[0]), self.score