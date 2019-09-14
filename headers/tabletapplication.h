#ifndef TABLETAPPLICATION_H
#define TABLETAPPLICATION_H
#include <QApplication>
#include "headers/mainwindow.h"

class TabletApplication : public QApplication
{
    Q_OBJECT

public:
    using QApplication::QApplication;
    bool event(QEvent* event) override;
    void addMainWindow(MainWindow* window);
    void connectMainWindow(MainWindow* canvas);
    void connectFrameController(FrameController* controller);

private:
    MainWindow* appWindow;

signals:
    void setTabletActive(bool signal);
};

#endif // TABLETAPPLICATION_H
