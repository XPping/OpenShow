# coding: utf-8

import numpy as np
import os
import torch
import torch.nn.functional as F
from PIL import Image
import cv2
import threading
from torch.autograd import Variable
from torchvision import transforms

from recognition.face_align import alignCropFace
from recognition.model import DeepFace

class Solver(object):
    def __init__(self, database_path, model_path):
        self.n_class = 2
        self.image_size = 152
        self.database_path = database_path
        self.model_path = model_path

        self.transform = transforms.Compose([
            transforms.Resize((self.image_size, self.image_size)),
            transforms.ToTensor(),
            transforms.Normalize((123.68 / 255, 116.779 / 255, 103.939 / 255),
                                 (58.393 / 255, 47.12 / 255, 57.375 / 255))
        ])

        self.build_model()

    def build_model(self):
        self.net = DeepFace()
        self.net.load_state_dict(torch.load(self.model_path, map_location='cpu'))

    def to_var(self, x, volatile=False):
        if torch.cuda.is_available():
            x = x.cuda()
        return Variable(x, volatile=volatile)

    def judgeOne(self, imagepath1, imagepath2):
        face1 = alignCropFace(imagepath1)
        try:
            face2 = alignCropFace(imagepath2)
        except:
            return 0

        face1 = Image.fromarray(cv2.cvtColor(face1, cv2.COLOR_BGR2RGB))
        face1 = self.transform(face1)
        face2 = Image.fromarray(cv2.cvtColor(face2, cv2.COLOR_BGR2RGB))
        face2 = self.transform(face2)

        face1 = self.to_var(face1)
        face2 = self.to_var(face2)
        face1 = face1.view(1, 3, self.image_size, self.image_size)
        face2 = face2.view(1, 3, self.image_size, self.image_size)
        out_cls = self.net(face1, face2)
        pred = out_cls.cpu().detach().numpy() > 0.5
        return pred[0]

    def judge(self, image):
        mutex = threading.Lock()
        mutex.acquire()
        try:
            cv2.imwrite("recognition.png", image)
            database_file = os.listdir(self.database_path)
            for d1 in database_file:
                ret = self.judgeOne(os.path.join(self.database_path, d1), "recognition.png")
                if int(ret) == 1:
                    return bytes(d1.split(".")[0], encoding="utf-8")
            return b"UnKown"
        finally:
            mutex.release()

# print(solver.judgeOne(r"database/01_0001.jpg", r"database/01_0002.jpg"))
