#include "headers/tabletapplication.h"
#include <QDebug>

bool TabletApplication::event(QEvent* event)
{
    if (event->type() == QEvent::TabletEnterProximity || event->type() == QEvent::TabletLeaveProximity) {
        if(event->type() == QEvent::TabletEnterProximity){
            emit setTabletActive(true); // allow for tablet pen
        }else{
            emit setTabletActive(false);
        }
        return true;
    }
    // accept events normally (i.e. mouse)
    return QApplication::event(event);
}

void TabletApplication::addMainWindow(MainWindow* window){
    appWindow = window;
    connectMainWindow(appWindow); // the MainWindow will handle any tabletevent signals from TabletApplication
    connectFrameController(appWindow->getFrameController());
}

// allow MainWindow instance to receive setTabletActive signals from this class
// this will let MainWindow control tabletEvent in the current scribbleArea frame
// by passing the current frame whatever the value of setTabletActive is
// this way TabletApplication doesn't have to pass anything to ScribbleArea directly
// and this way we don't have to worry about connecting every new frame with the setTabletActive signal
// since MainWindow will just pass this flag to whatever the current frame is whenever a tabletevent occurs
// but need to consider cases when frame is switched
void TabletApplication::connectMainWindow(MainWindow* window){
   connect(this, &TabletApplication::setTabletActive, window, &MainWindow::setTabletActive);
}

// allow FrameController instance to receive setTabletActive signals from this class
void TabletApplication::connectFrameController(FrameController* controller){
   connect(this, &TabletApplication::setTabletActive, controller, &FrameController::setTabletActive);
}

