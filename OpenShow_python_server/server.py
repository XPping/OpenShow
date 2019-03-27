from __future__ import division, print_function, absolute_import

import socket
import sys
import threading
import os
import cv2

import str_type
from face_detector import FaceDetector
from image_generator import ImageGenerator
from face_recognition import FaceRecognition
class Server(object):
    def __init__(self):
        self.processor = {
            b"FaceDetector": FaceDetector,
            b"ImageGenerator": ImageGenerator,
            b"FaceRecognition": FaceRecognition
        }
        self.listen(ip="127.0.0.1", port=6666)

    def listen(self, ip, port):
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            s.bind((ip, port))
            s.listen(10)
            print("Listening...")
        except socket.error as msg:
            print(msg, "error")
            sys.exit(1)
        while True:
            conn, addr = s.accept()
            t = threading.Thread(target=self.processData, args=(conn, addr))
            t.start()
        s.close()

    def processData(self, conn, addr):
        End = b"End"
        recvData = b""
        while True:
            try:
                data = conn.recv(1024 * 1024)
            except:
                conn.close()
                return
            recvData += data
            if End in recvData:
                recvData = recvData[0:recvData.find(End)]
                break
        recv_list = recvData.split(b"xppxppxpp")
        msg_type = recv_list[0]
        if msg_type not in self.processor:
            raise ValueError("Message type error: ".format(msg_type))
        processor = self.processor[msg_type]()
        result = processor.processData(recv_list[1])
        # print(result)
        conn.sendall(result)
        conn.close()

"""
def server():
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind(("127.0.0.1", 6666))
        s.listen(10)
        print("Listening...")
    except socket.error as msg:
        print(msg, "error")
        sys.exit(1)
    while True:
        conn, addr = s.accept()
        t = threading.Thread(target=dealClientData, args=(conn, addr))
        t.start()
    s.close()

# load alexnet to predict a image 
def sendResult(conn, image_path):
    sendData = ""
    send = bytes(sendData, encoding="utf8")
    conn.sendall(send)

# Receive data from client
count = 0
def dealClientData(conn, addr):
    global count
    End = b"Send End"
    print(addr)
    count += 1
    image_path = "{}.jpg".format(count%50)
    imageFile = open(image_path, "wb")
    recvData = b""
    while True:
        data = conn.recv(1024*1024)
        recvData += data
        if End in recvData:
            recvData = recvData[0:recvData.find(End)]
            break
    recv_list = recvData.split(b"xppxppxpp")
    print(recv_list[0])
    imageFile.write(recv_list[1])
    imageFile.close()
    sendResult(conn, image_path)
    conn.close()
"""

def main():
    server = Server()

if __name__ == "__main__":
    main()