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
 * https://stackoverflow.com/questions/16609874/qgraphicsview-not-showing-the-picture
 *
 */

Timeline::Timeline(QWidget *parent)
{
    layout = new QHBoxLayout(this);

    // add QGraphicsView to hold the QGraphicsScene, which will hold each frame
    // as a QGraphicsPixmapItem
    //containerScene = new QGraphicsScene(this);
   // container = new QGraphicsView(containerScene, this);
   //containerScene->addText("blah blah blah frames show up here");
    //layout->addWidget(container);

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

    // check out the image to make sure its what you expect?
    qDebug() << "image width: " << image.width();
    qDebug() << "image height: " << image.height();
    for(int i = 0; i < image.height(); i++){
        for(int j = 0; j < image.width(); j++){
            if(i == 0 && j < 5){
                qDebug() << image.pixelColor(j, i);
            }
            QColor newColor = Qt::black;
            newColor.setAlpha(255);
            image.setPixelColor(j, i, newColor);
        }
    }

    // need to make sure image is scaled
    QPixmap pixmap = QPixmap::fromImage(image);//QPixmap("C:\\Users\\Nicholas Hung\\Desktop\\build-cute_animator-Desktop_Qt_5_13_0_MinGW_32_bit-Debug\\debug\\bocchi2.png"); //QPixmap::fromImage(image);
    QPixmap scaledPixmap = pixmap.scaled(50,50);

    QGraphicsPixmapItem* frame = new QGraphicsPixmapItem(scaledPixmap);
    containerScene->addItem(frame);

    QGraphicsPixmapItem* frame2 = new QGraphicsPixmapItem(scaledPixmap);
    frame2->moveBy(80, 0);
    containerScene->addItem(frame2);

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
