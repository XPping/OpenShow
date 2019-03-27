#ifndef FACERECOGNITION_H
#define FACERECOGNITION_H

#include "abstractqwidget.h"
#include "widgetfactory.h"
#include "myimagelabel.h"
#include "server.h"

#include <QFileDialog>
#include <QLineEdit>
#include <QPushButton>

class FaceRecognition : public AbstractQWidget
{
    Q_OBJECT
public:
    explicit FaceRecognition(AbstractQWidget *parent = nullptr);
    ~FaceRecognition(){}

    // Show widget
    void widgetShow();
    // Close widget
    void widgetClose();

public slots:
    void recognitionSlot();
    void displayResultSlot(QByteArray &byte);

private:
    QPushButton *m_recognition_btn;
    QLineEdit *m_who_is;
    MyImageLabel *m_image_label;

    Server *m_server;
    QPixmap m_current_pixmap;
};

REGISTER_WIDGET_CLASS(FaceRecognition);

#endif // FACERECOGNITION_H
