from __future__ import division, print_function, absolute_import

import cv2
import numpy as np

from abstract_model import AbstractModel
from recognition.recognition import Solver

class FaceRecognition(AbstractModel):
    def __init__(self):
        AbstractModel.__init__(self)
        self.solver = Solver("database", "weights/recognition.pth")

    def processData(self, input):
        # image_path = "{}.jpg".format(0 % 50)
        # imageFile = open(image_path, "wb")
        # imageFile.write(input)
        # imageFile.close()
        image = cv2.imdecode(np.frombuffer(input, np.uint8), -1)
        result = self.solver.judge(image)
        if result is None:
            return b"END"
        result += b"END"
        print("Recognition!!!", result)
        return result
