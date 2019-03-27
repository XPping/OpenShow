#include "facerecognition.h"

#include <QVBoxLayout>
#include <QMessageBox>
#include <QBuffer>

FaceRecognition::FaceRecognition(AbstractQWidget *parent) :
    AbstractQWidget(parent),
    m_recognition_btn(0),
    m_who_is(0),
    m_image_label(0),
    m_server(0)
{
    this->setName("FaceRecognition");


    m_recognition_btn = new QPushButton("Pick");
    m_who_is = new QLineEdit;
    m_image_label = new MyImageLabel;

    // Top of widget layout
    QWidget *top_widget = new QWidget;
    QHBoxLayout *top_layout = new QHBoxLayout;
    top_layout->setMargin(0);
    top_layout->addWidget(m_recognition_btn);
    top_layout->addStretch();
    QLabel *label = new QLabel("Who is: ");
    label->adjustSize();
    top_layout->addWidget(label);
    top_layout->addWidget(m_who_is);
    top_layout->addStretch();
    top_layout->setStretch(0, 3);
    top_layout->setStretch(1, 2);
    top_layout->setStretch(2, 3);
    top_layout->setStretch(3, 3);
    top_layout->setStretch(4, 3);
    top_widget->setLayout(top_layout);
    // Total widget layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->addWidget(top_widget);
    layout->addWidget(m_image_label);
    layout->setStretch(0, 1);
    layout->setStretch(1, 5);
    this->setLayout(layout);

    // Server
    m_server = new Server(this->getName());

    connect(m_recognition_btn, SIGNAL(clicked()), SLOT(recognitionSlot()));
}

void FaceRecognition::widgetShow()
{
    this->show();
}

void FaceRecognition::widgetClose()
{

}

void FaceRecognition::recognitionSlot()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Open an image"),
                                                ".",
                                                tr("Images(*.png *.jpg"));
    if(!path.isEmpty()){
        QImage image(path);
        m_current_pixmap = QPixmap::fromImage(image);
        m_image_label->setImage(m_current_pixmap);
        m_server->connectToServer();
        QBuffer buffer; // save image into QBuffer
        buffer.open(QIODevice::ReadWrite);
        m_current_pixmap.save(&buffer, "jpg");
        QByteArray send_byte;   // send byte
        send_byte.append(this->getName().toUtf8());
        send_byte.append(QString("xppxppxpp").toUtf8());
        send_byte.append(buffer.data());
        send_byte.append(QString("End").toUtf8());
        m_server->sendMessage(send_byte);
        connect(m_server, SIGNAL(readyReceive(QByteArray &)), SLOT(displayResultSlot(QByteArray &)));

    }else{
        QMessageBox::warning(this, tr("Path"), tr("You did't select an image"));
    }

}

void FaceRecognition::displayResultSlot(QByteArray &byte)
{
    if(byte == ""){
        m_who_is->setText("Unkown");
        return;
    }
    QString str_byte = QString(byte);
    m_who_is->setText(str_byte);
}
