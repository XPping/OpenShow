#ifndef ABSTACTQWDGET_H
#define ABSTACTQWDGET_H

#include <QWidget>



class AbstractQWidget : public QWidget
{
    Q_OBJECT
public:
    //AbstractQWidget(){}
    //AbstractQWidget(const AbstractQWidget& other){}
    explicit AbstractQWidget(QWidget *parent = nullptr);
    ~AbstractQWidget(){}

    virtual void widgetShow() = 0;
    virtual void widgetClose() = 0;

signals:


public slots:
    void setName(QString name){this->m_name = name;}
    QString getName(){return this->m_name;}

private:
    QString m_name;
};


#endif // ABSTACTQWDGET_H
