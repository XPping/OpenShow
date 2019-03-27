#include "facedetector.h"

#include <QBuffer>
#include <QMessageBox>
#include <QThread>
#include <QTimer>
#include <QVBoxLayout>
#include <math.h>

FaceDetector::FaceDetector(AbstractQWidget *parent) : AbstractQWidget(parent),
    m_camera(0),
    m_stack_widget(0),
    m_image_label1(0),
    m_image_label2(0),
    m_timer(0),
    m_server(0)
{
    this->setName("FaceDetector");
    // Init ui
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    m_stack_widget = new QStackedWidget;
    layout->addWidget(m_stack_widget);
    this->setLayout(layout);

    m_image_label1 = new MyImageLabel;
    m_image_label2 = new MyImageLabel;

    QWidget *widget1 = new QWidget;
    QVBoxLayout *layout1 = new QVBoxLayout;
    layout1->setMargin(0);
    layout1->addWidget(m_image_label1);
    widget1->setLayout(layout1);
    m_stack_widget->addWidget(widget1);

    QWidget *widget2 = new QWidget;
    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->setMargin(0);
    layout2->addWidget(m_image_label2);
    widget2->setLayout(layout2);
    m_stack_widget->addWidget(widget2);

    layout->setMargin(0);
    m_camera = new MyCamera;
    this->setLayout(layout);
    // Timer
    m_timer = new QTimer;
    m_timer->setInterval(100);
    // Camera timer timeout signal to displayImage() slot;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(sendToServer()));
    // Server
    m_server = new Server(this->getName());
    m_mutex = false;
}

void FaceDetector::widgetShow()
{

    m_camera->startCamera();
    m_timer->start();
    this->show();
    m_mutex = false;
}

void FaceDetector::widgetClose()
{
    m_camera->stopCamera();
    m_timer->stop();
    this->close();
}

void FaceDetector::sendToServer()
{
    // get QPixmap from camera
    QPixmap pix = m_camera->getCapturedImage();
    if(pix.isNull()) return;
    if(m_mutex) return;
    m_mutex = true;

    m_camera_image = pix;
    m_image_label1->setImage(pix);
    m_stack_widget->setCurrentIndex(0);
    bool is_connected = m_server->connectToServer();
    if(!is_connected){
        QMessageBox::information(NULL, "Server Error", "Can't connect to Server");
        return;
    }
    QBuffer buffer; // save image into QBuffer
    buffer.open(QIODevice::ReadWrite);
    pix.save(&buffer, "jpg");
    QByteArray send_byte;   // send byte
    send_byte.append(this->getName().toUtf8());
    send_byte.append(QString("xppxppxpp").toUtf8());
    send_byte.append(buffer.data());
    send_byte.append(QString("End").toUtf8());
    m_server->sendMessage(send_byte);
    connect(m_server, SIGNAL(readyReceive(QByteArray &)), SLOT(displayImage(QByteArray &)));
}

void FaceDetector::displayImage(QByteArray &byte)
{
    if(byte == "" || m_camera_image.isNull()){
        m_mutex = false;
        return;
    }
    QString str_byte = QString(byte);
    QStringList ret_list = str_byte.split(",");
    int x1 = ret_list[0].toInt(), y1 = ret_list[1].toInt();
    int x2 = ret_list[2].toInt(), y2 = ret_list[3].toInt();
    QImage img(m_camera_image.toImage());

    //qDebug()<<x1<<";"<<y1<<";"<<x2<<";"<<y2<<";"<<img.size();
    // label the face rect
    for(int i=x1; i<=x2; i++){
        img.setPixelColor(i, y1, QColor(255, 0, 0));
        img.setPixelColor(i, y2, QColor(255, 0, 0));

    }
    for(int i=y1; i<=y2; i++){
        img.setPixelColor(x1, i, QColor(255, 0, 0));
        img.setPixelColor(x2, i, QColor(255, 0, 0));
    }
    m_image_label2->setImage(QPixmap::fromImage(img));
    m_stack_widget->setCurrentIndex(1);
    m_timer->stop();
    m_timer->start(100);
    m_mutex = false;
    //QTimer::singleShot(500, this, SLOT(displayDetectedImage()));
}

void FaceDetector::displayDetectedImage()
{
    //m_timer->start();
    m_stack_widget->setCurrentIndex(0);
    m_mutex = false;
}

