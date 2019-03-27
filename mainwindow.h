#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QListView>
#include <QVector>
#include <QListWidget>

#include "abstractqwidget.h"

#define NEW_WIDGET_BY_NAME(T) \
    new T()


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void listWidgetSlot(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::MainWindow *ui;
    QStackedWidget *m_stacked_widget;
};

#endif // MAINWINDOW_H
