from __future__ import division, print_function, absolute_import

import cv2
import numpy as np

from abstract_model import AbstractModel
import str_type

class FaceDetector(AbstractModel):
    def __init__(self):
        AbstractModel.__init__(self)
        self.classfier = cv2.CascadeClassifier(r"weights/haarcascade_frontalface_alt.xml")

    def faceDetector(self, image):
        frame = image
        divisor = 8
        h, w = frame.shape[0:2]
        min_size = (w // divisor, h // divisor)
        face_rects = self.classfier.detectMultiScale(frame, 1.2, 2, cv2.CASCADE_SCALE_IMAGE, min_size)

        if len(face_rects) == 0:
            return None
        x, y, w, h = face_rects[0]
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 3)
        ret = "{},{},{},{}".format(x, y, x+w, y+h)
        ret = bytes(ret, encoding="utf-8")
        return ret

    def processData(self, input):
        # image_path = "{}.jpg".format(0 % 50)
        # imageFile = open(image_path, "wb")
        # imageFile.write(input)
        # imageFile.close()
        image = cv2.imdecode(np.frombuffer(input, np.uint8), -1)
        result = self.faceDetector(image)
        if result is None:
            return b"END"
        result += b"END"
        print("Detected!!!", result)
        return result
