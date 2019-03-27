from __future__ import division, print_function, absolute_import

import cv2
import numpy as np
import argparse

from abstract_model import AbstractModel
from generator.generator import Solver
class ImageGenerator(AbstractModel):
    def __init__(self):
        AbstractModel.__init__(self)

        parser = argparse.ArgumentParser()
        parser.add_argument('--noise_n', type=int, default=128)
        parser.add_argument('--G_last_act', type=str, default="tanh")
        parser.add_argument('--G_pretrained_model', type=str, default="weights/generator.pth")

        config = parser.parse_args()

        self.solver = Solver(config)

    def processData(self, input):
        # image_path = "{}.jpg".format(0 % 50)
        # imageFile = open(image_path, "wb")
        # imageFile.write(input)
        # imageFile.close()
        ret = self.solver.generate()
        ret += b"END"
        print("Generator", len(ret))
        return ret
