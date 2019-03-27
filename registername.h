#ifndef REGISTERNAME_H
#define REGISTERNAME_H


#include <QSet>

//typedef QObject* (*Creator)(QObject* parent);


class NameFactory{
public:
    static QSet<QString>& Registry(){
        static QSet<QString>* g_registry_ = new QSet<QString>;
        return *g_registry_;
    }
    static void AddCreator(const QString& name){
        QSet<QString> &registry = Registry();
        registry.insert(name);
    }
};

class NameRegister{
public:
    NameRegister(const QString &name){
        NameFactory::AddCreator(name);
    }
};

#define REGISTER_NAME(name) \
    static NameRegister _g(name)


#endif // REGISTERNAME_H
