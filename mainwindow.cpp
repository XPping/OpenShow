#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include<QMetaType>
#include<facedetector.h>


#include "abstractqwidget.h"
#include "widgetfactory.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_stacked_widget(0)
{
    ui->setupUi(this);

    m_stacked_widget = new QStackedWidget;
    // All AbstractWidget for m_stacked_widget
    auto factory = ClassFactory::constructors();
    auto key_list = factory.keys();
    // Only show the first AbstractWidget
    if(key_list.size()>0){
        AbstractQWidget *it = ClassFactory::createObject(key_list[0]);
        qDebug()<<it->getName();
        m_stacked_widget->addWidget(it);
        ui->list_widget->addItem(new QListWidgetItem(it->getName()));
        it->widgetShow();
    }
    for(int i=1; i<key_list.size(); i++){
        AbstractQWidget *it = ClassFactory::createObject(key_list[i]);
        qDebug()<<it->getName();
        m_stacked_widget->addWidget(it);
        ui->list_widget->addItem(new QListWidgetItem(it->getName()));
        //it->widgetShow();
    }

    // Add m_stacked_widget to ui->stacked_wdget
    m_stacked_widget->show();
    ui->stacked_widget->layout()->setMargin(0);
    ui->stacked_widget->layout()->addWidget(m_stacked_widget);

    // The signal and slot for ui->list_widget. When change the list, show the abstractWidget corresponsed
    connect(ui->list_widget, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            SLOT(listWidgetSlot(QListWidgetItem *, QListWidgetItem *)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::listWidgetSlot(QListWidgetItem *current, QListWidgetItem *previous)
{
    int pre_row = ui->list_widget->row(previous);
    if(pre_row != -1){
        AbstractQWidget *widget = (AbstractQWidget *)m_stacked_widget->widget(pre_row);
        widget->widgetClose();
    }
    int cur_row = ui->list_widget->row(current);
    //qDebug()<<pre_row<<"; "<<cur_row;
    AbstractQWidget *widget =  (AbstractQWidget *)m_stacked_widget->widget(cur_row);
    widget->widgetShow();
    m_stacked_widget->setCurrentIndex(cur_row);
}
