#include "headers/tabletapplication.h"
#include <QDebug>

bool TabletApplication::event(QEvent* event)
{
    if (event->type() == QEvent::TabletEnterProximity || event->type() == QEvent::TabletLeaveProximity) {
        if(event->type() == QEvent::TabletEnterProximity){
            qDebug() << "entering tablet! sent signal to scribblearea.";
            emit setTabletActive(true); // allow for tablet pen
        }else{
            qDebug() << "leaving tablet! sent signal to scribblearea.";
            emit setTabletActive(false);
        }
        return true;
    }
    // accept events normally (i.e. mouse)
    return QApplication::event(event);
}

void TabletApplication::addWindow(MainWindow *win){
    connect(this, &TabletApplication::setTabletActive, win->getScribbleArea(), &ScribbleArea::setTabletActive);
    appWindow = win;
}
