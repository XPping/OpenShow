#include "imagegenerator.h"

#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QBuffer>
#include <QMessageBox>

ImageGenerator::ImageGenerator(AbstractQWidget *parent) : AbstractQWidget(parent),
    m_image_label(0),
    m_generate_btn(0),
    m_server(0)
{
    // Widget name
    this->setName("ImageGenerator");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);

    m_generate_btn = new QPushButton("Generate");

    QHBoxLayout *btn_layout = new QHBoxLayout;
    btn_layout->addWidget(m_generate_btn);
    btn_layout->addStretch();
    btn_layout->setStretch(0, 1);
    btn_layout->setStretch(1, 3);
    QWidget *btn_widget = new QWidget;
    btn_widget->setLayout(btn_layout);
    layout->addWidget(btn_widget);
    //layout->addStretch();
    m_image_label = new MyImageLabel;
    m_image_label->show();
    layout->addWidget(m_image_label);
    layout->setStretch(0, 1);
    layout->setStretch(1, 12);
    this->setLayout(layout);

    m_server = new Server(this->getName());
    connect(m_generate_btn, SIGNAL(clicked()), SLOT(sendToServer()));

}

void ImageGenerator::widgetShow()
{
    this->show();
}

void ImageGenerator::widgetClose()
{
    this->close();
}

void ImageGenerator::sendToServer()
{
    QByteArray send_byte;
    send_byte.append(this->getName().toUtf8());
    send_byte.append(QString("xppxppxpp").toUtf8());
    send_byte.append(QString("Send End").toUtf8());
    m_server->connectToServer();
    bool is_connected = m_server->connectToServer();
    if(!is_connected){
        QMessageBox::information(NULL, "Server Error", "Can't connect to Server");
        return;
    }
    m_server->sendMessage(send_byte);

    connect(m_server, SIGNAL(readyReceive(QByteArray &)), SLOT(displayImage(QByteArray &)));
}

void ImageGenerator::displayImage(QByteArray &byte)
{
    if(byte == "") return;



    QPixmap ret;
    ret.loadFromData(byte);
    m_image_label->setImage(ret);
    return;
    /*
    ret.save("/images/images/B.png");
    qDebug()<<byte.length();
    QBuffer buffer(&byte);
    buffer.open(QIODevice::ReadOnly);
    QImage img;
    img.save(&buffer, "jpg");
    if(img.isNull()) return;
    img.save("a.png");
    qDebug()<<"save";
    m_image_label->setImage(QPixmap::fromImage(img));
    */
}




