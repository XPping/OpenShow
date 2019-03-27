#ifndef WIDGETREGISTRY_H
#define WIDGETREGISTRY_H

#include <QVector>
#include <QMap>
#include <QMetaObject>

//typedef QObject* (*Creator)(QObject* parent);
typedef void* (*Creator)();
typedef QMap<QString, Creator> CreatorRegistry;
class WidgetRegistry{
public:
    static CreatorRegistry& Registry(){
        static CreatorRegistry* g_registry_ = new CreatorRegistry;
        return *g_registry_;
    }
    static void AddCreator(const QString& name, Creator creator){
        CreatorRegistry &registry = Registry();
        registry.insert(name, creator);
    }
};

class WidgetRegister{
public:
    WidgetRegister(const QString &name, Creator creator){
        WidgetRegistry::AddCreator(name, creator);
    }
};

#define REGISTER_WIDGET_CREATOR(name, creator) \
    static WidgetRegister g_creator_##name(#name, creator)

#define REGISTER_WIDGET(name)                       \
    void* Creator_##name()                          \
    {                                               \
        return void* (new name());                  \
    }                                               \
    REGISTER_WIDGET_CREATOR(name, Creator_##name)
// typedef shared_ptr<Layer<Dtype> > (*Creator)(const LayerParameter&);
// typedef std::map<string, Creator> CreatorRegistry;

#endif // WIDGETREGISTRY_H
