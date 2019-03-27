#ifndef WIDGETFACTORY_H
#define WIDGETFACTORY_H

#include <QMetaObject>
#include <QMap>
#include "abstractqwidget.h"


class ClassFactory{
public:
    ClassFactory(){}
    ~ClassFactory(){}
    typedef AbstractQWidget* (*Constructor)(AbstractQWidget* parent);

    template<typename T>
    static AbstractQWidget* constructorHelper(AbstractQWidget* parent){
        return new T(parent);
    }
    static QMap<QString, Constructor>& constructors(){
        static QMap<QString, Constructor> *instance = new QMap<QString, Constructor>;
        return *instance;
    }

    template<typename T>
    static void registerClass(){
        constructors().insert(T::staticMetaObject.className(), &constructorHelper<T>);
    }
    static AbstractQWidget* createObject(const QString& className, AbstractQWidget* parent=NULL){
        Constructor constructor = constructors().value(className);
        if(constructor == NULL)
            return NULL;
        return (*constructor)(parent);
    }

private:

};

template <class T>
class WidgetRegister{
public:
    WidgetRegister(){
        ClassFactory::registerClass<T>();
    }
};

//#define REGISTER(T) \
//    static WidgetRegister _register;

#define REGISTER_WIDGET_CLASS(T) \
    static WidgetRegister<T> _register;


#endif // WIDGETFACTORY_H
