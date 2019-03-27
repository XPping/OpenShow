from __future__ import division, print_function, absolute_import

class AbstractModel(object):
    def __init__(self):
        pass

    def processData(self, input):
        raise NotImplementedError
