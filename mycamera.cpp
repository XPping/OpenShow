#include "mycamera.h"

#include <QGridLayout>
#include <QTimer>

#include <QtMultimedia/QCameraInfo>
#include <QMessageBox>

MyCamera::MyCamera(QWidget *parent) : QWidget(parent),
    camera(0),
    imageCapture(0),
    cameraTimer(0),
    imageShowLabel(0)
{
    m_previewImage = QImage();
    // New camera capture image label
    imageShowLabel = new QLabel(this);
    imageShowLabel->setScaledContents(true);
    // Label must in top-left;
    imageShowLabel->setGeometry(QRect(0, 0, 0, 0));
    // New camera object
    if(QCameraInfo::availableCameras().size() != 0){
        camera = new QCamera(QCameraInfo::defaultCamera());
        // New camera caputre object
        imageCapture = new QCameraImageCapture(camera);
        // Connect imageCapture's imageCaptured(int, QImage) signal to slot;
        connect(imageCapture, SIGNAL(imageCaptured(int, QImage)), this, SLOT(imageCaptureSlot(int, QImage)));
        // Camera timer
        cameraTimer = new QTimer();
        cameraTimer->setInterval(33);
        // Camera timer timeout signal to takeCapture() slot;
        connect(cameraTimer, SIGNAL(timeout()), this, SLOT(takeCapture()));
    }else{
        QMessageBox::information(NULL, "Camera Error", "Can't open any camera. Please add a camera and restart");
    }

    //this->show();
}

MyCamera::~MyCamera()
{
    delete camera;
    delete imageCapture;
    delete cameraTimer;
    delete imageShowLabel;
}

QPixmap MyCamera::getCapturedImage()
{
    if(m_previewImage.isNull()) return QPixmap::fromImage(m_previewImage);
    return QPixmap::fromImage(m_previewImage);
}

void MyCamera::startCamera()
{
    camera->start();
    cameraTimer->start();
}

void MyCamera::stopCamera()
{
    // Close camera
    camera->stop();
    cameraTimer->stop();
}

void MyCamera::takeCapture()
{
    // Send imageCapure's imageCaptured(int, QImage) signal;
    imageCapture->capture("cpature.jpg"); // if not a name, will save image when captured every time
}

void MyCamera::imageCaptureSlot(int requestId, const QImage &img)
{
    // Show caputred image
    Q_UNUSED(requestId);
    QImage scaledImage = img.scaled(this->size(),
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);
    m_previewImage = img;
    imageShowLabel->setPixmap(QPixmap::fromImage(scaledImage));
}

void MyCamera::paintEvent(QPaintEvent *event)
{
    // Let image show label can zoom in/zoom out as father widget
    if(imageShowLabel != NULL){
        imageShowLabel->resize(this->size());
    }
}


