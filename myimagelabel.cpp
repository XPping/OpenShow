#include "myimagelabel.h"

MyImageLabel::MyImageLabel(QWidget *parent) : QWidget(parent),
    m_image_label(0)
{
    m_image_label = new QLabel(this);
    m_image_label->setScaledContents(true);
    m_image_label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    // Label must in top-left;
    m_image_label->setGeometry(QRect(0, 0, 0, 0));

    this->show();
}

void MyImageLabel::setImage(QString filename)
{

    QImage img(filename);
    img.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_image_label->setPixmap(QPixmap::fromImage(img));
}

void MyImageLabel::setImage(QPixmap pix)
{
    if(pix.isNull()) return;
    m_image_label->setPixmap(pix.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MyImageLabel::paintEvent(QPaintEvent *event)
{
    if(m_image_label != NULL){
        m_image_label->resize(this->size());
    }
}
