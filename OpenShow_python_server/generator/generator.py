# coding: utf-8

import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.autograd import Variable
from torch.autograd import grad
from torchvision.utils import save_image

import numpy as np
import argparse
import threading

from generator.model import Generator

def last_act(act):
    if act == "relu":
        return nn.ReLU(inplace=True)
    elif act == "sigmoid":
        return nn.Sigmoid()
    elif act == "tanh":
        return nn.Tanh()
    else:
        return None

class Solver(object):
    def __init__(self, config):
        self.noise_n = config.noise_n
        self.G_last_act = last_act(config.G_last_act)
        self.G_pretrained_model = config.G_pretrained_model

        self.build_model()
        self.load_pretrained_model(self.G_pretrained_model)

    def build_model(self):
        self.G = Generator(self.noise_n, self.G_last_act)

        if torch.cuda.is_available():
            self.G.cuda()

    def load_pretrained_model(self, pretrained_model):
        self.G.load_state_dict(torch.load(pretrained_model, map_location='cpu'))

    def denorm(self, x):
        out = (x + 1) / 2
        return out.clamp_(0, 1)

    def to_var(self, x, volatile=False):
        if torch.cuda.is_available():
            x = x.cuda()
        return Variable(x, volatile=volatile)

    def noise_vector(self, batch_size, length):
        return np.random.normal(0., 1., size=[batch_size, length])

    def generate(self):
        mutex = threading.Lock()
        mutex.acquire()
        try:
            noise = self.noise_vector(1, self.noise_n)
            # print("noise vector: ", noise)
            noise_x = self.to_var(torch.FloatTensor(noise))
            fake_x = self.G(noise_x)
            save_image(self.denorm(fake_x.data)[0], "fake.png")
            fp = open("fake.png", "rb")
            ret = b""
            # ret += noise[0].tobytes()
            # ret += b"xppxppxpp"
            for data in fp:
                ret += data
            return ret
        finally:
            mutex.release()
        # save_image(self.denorm(fake_x.data), os.path.join(self.image_save_path, "{}_fake.png".format(e + 1)))