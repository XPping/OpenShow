#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

#include "abstractqwidget.h"
#include "widgetfactory.h"
#include "mycamera.h"
#include "myimagelabel.h"
#include "server.h"

#include <QMutex>
#include <QPushButton>
#include <QStackedWidget>

class FaceDetector : public AbstractQWidget
{
    Q_OBJECT
public:
    //FaceDetector(){}
    //FaceDetector(const FaceDetector &other){}
    explicit FaceDetector(AbstractQWidget *parent = nullptr);
    ~FaceDetector(){}
    // Show widget
    void widgetShow();
    // Close widget
    void widgetClose();

signals:

public slots:
    // Send image to server, getted by m_camera.getCapturedImage()
    void sendToServer();
    // Display image from camera
    void displayImage(QByteArray &byte);
    // Display image from server, output of server is QByteArray
    void displayDetectedImage();

private:
    // camera, to get image cpatured by it.
    MyCamera *m_camera;
    // Display image
    QStackedWidget *m_stack_widget;
    MyImageLabel *m_image_label1, *m_image_label2; // label1 display image in time, label2 display face
    QPixmap m_camera_image;
    // Timer to detect face
    QTimer *m_timer;
    // Server
    Server *m_server;
    // mutex, wait server result before send to server again
    bool m_mutex;
};


REGISTER_WIDGET_CLASS(FaceDetector);
#endif // FACEDETECTOR_H
