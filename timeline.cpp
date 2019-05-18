#include "headers/timeline.h"
#include <QString>
#include <iostream>
#include <QTextStream>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QDebug>

/*
 *  provides animation button, allows setting the delay in ms between frames for animation
 *  should provide a 'timeline' that displays a thumbnail of the frames in order
 *
 * https://stackoverflow.com/questions/5960074/qimage-in-a-qgraphics-scene
 * https://www.qtcentre.org/threads/30011-How-to-design-a-thumbnail-viewer-in-QT
 * https://stackoverflow.com/questions/5960074/qimage-in-a-qgraphics-scene
 *
 */

Timeline::Timeline(QWidget *parent)
{
    layout = new QHBoxLayout(this);

    // add QGraphicsView to hold the QGraphicsScene, which will hold each frame
    // as a QGraphicsPixmapItem
    containerScene = new QGraphicsScene();
    container = new QGraphicsView(containerScene);
    containerScene->addText("blah blah blah frames show up here");
    layout->addWidget(container);

    btn = new QPushButton();
    connect(btn, SIGNAL(clicked()), this, SLOT(emitAnimationSignal()));

    editDelay = new QLineEdit(this);
    btn->setFixedWidth(80);
    editDelay->setFixedWidth(80);

    btn->setText("animate");
    layout->addWidget(btn);
    layout->addWidget(editDelay);

    setLayout(layout);

}

// is this even working? can we make the initial scribble area to be a solid color to check?
void Timeline::addFrameToTimeline(QImage image){
    QPixmap pixmap = QPixmap::fromImage(image);
    QGraphicsPixmapItem* frame = new QGraphicsPixmapItem(pixmap);
    containerScene->addItem(frame);
    container->show();
    qDebug() << "supposed to add frame to timeline...";
}

void Timeline::emitAnimationSignal(){
    // get int from textbox, which is the time delay between frames.
    int timeDelay = (editDelay->text()).toInt();
   // QTextStream out(stdout);
   //out << editDelay->text() << endl;
    if(timeDelay <= 0){
        timeDelay = 500;
    }
    emit doAnimation(timeDelay);
}
