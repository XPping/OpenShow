#ifndef MYIMAGELABEL_H
#define MYIMAGELABEL_H

#include <QLabel>
#include <QWidget>

class MyImageLabel : public QWidget
{
    Q_OBJECT
public:
    explicit MyImageLabel(QWidget *parent = nullptr);

    void setImage(QString filename);
    void setImage(QPixmap pix);
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);

private:
    QLabel *m_image_label;
};

#endif // MYIMAGELABEL_H
