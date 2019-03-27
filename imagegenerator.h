#ifndef IMAGEGENERATOR_H
#define IMAGEGENERATOR_H

#include "abstractqwidget.h"
#include "widgetfactory.h"
#include "myimagelabel.h"
#include "server.h"

#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class ImageGenerator : public AbstractQWidget
{
    Q_OBJECT
public:
    explicit ImageGenerator(AbstractQWidget *parent = nullptr);

    void widgetShow();
    void widgetClose();

signals:

public slots:
    // Send image to server, getted by m_camera.getCapturedImage()
    void sendToServer();
    // Display image from server, output of server is QByteArray
    void displayImage(QByteArray &byte);
private:
    QPushButton *m_generate_btn;
    MyImageLabel *m_image_label;
    Server *m_server;

};

REGISTER_WIDGET_CLASS(ImageGenerator);

#endif // IMAGEGENERATOR_H
