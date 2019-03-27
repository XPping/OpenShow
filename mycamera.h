#ifndef MYCAMERA_H
#define MYCAMERA_H

#include <QLabel>
#include <QWidget>

#include <QtMultimedia/QCamera>
#include <QtMultimedia/QCameraImageCapture>

/*
 * Used QTimer to capture camrea image, and display
 */
class MyCamera : public QWidget
{
    Q_OBJECT
public:
    explicit MyCamera(QWidget *parent = nullptr);
    ~MyCamera();
    QPixmap getCapturedImage();
signals:

public slots:
    void startCamera(); // Start Camera
    void stopCamera();  // Stop Camera
    void takeCapture();// Capture Image;

protected slots:
    // Used of QCameraImageCapture's SIGNAL(imageCaptured(int, QImage))
    void imageCaptureSlot(int requestId, const QImage &img);

protected:
    void paintEvent(QPaintEvent *event);

private:

private:
    QCamera *camera;                       // QCamera object
    QCameraImageCapture *imageCapture;     // QCamera image capture object
    QTimer *cameraTimer;                   // QCamera timer
    QLabel *imageShowLabel;                  // Camera infomation;
    QImage m_previewImage;               // Captured preview Image;
};


#endif // MYCAMERA_H
