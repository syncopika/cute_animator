#include "headers/timeline.h"
#include "headers/scribblearea.h"
#include "headers/mainwindowcontent.h"
#include "headers/framethumbnail.h"

#include <QString>
#include <iostream>
#include <QTextStream>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QPen>
#include <QPainter>

/*
 *  provides animation button, allows setting the delay in ms between frames for animation
 *  should provide a 'timeline' that displays a thumbnail of the frames in order
 *
 * https://stackoverflow.com/questions/5960074/qimage-in-a-qgraphics-scene
 * https://www.qtcentre.org/threads/30011-How-to-design-a-thumbnail-viewer-in-QT
 * https://stackoverflow.com/questions/5960074/qimage-in-a-qgraphics-scene
 * https://stackoverflow.com/questions/16609874/qgraphicsview-not-showing-the-picture
 *
 *
 * https://www.qtcentre.org/threads/22835-QGraphicsScene-item-positioning
 * https://stackoverflow.com/questions/10230696/how-to-correctly-use-qgraphicslinearlayout-together-with-qgraphicsscene-in-order?rq=1
 * https://stackoverflow.com/questions/17395312/subclassing-qgraphicslayoutitem-to-display-a-pixmap
 *
 */

Timeline::Timeline(QWidget *parent)
{
    layout = new QHBoxLayout(this);
    parentWidget = parent;

    // add QGraphicsView to hold the QGraphicsScene, which will hold each frame
    // as a QGraphicsPixmapItem
    //containerScene = new QGraphicsScene(this);
    // container = new QGraphicsView(containerScene, this);
    //containerScene->addText("blah blah blah frames show up here");
    //layout->addWidget(container);

    btn = new QPushButton(); // button to animate sequence
    connect(btn, SIGNAL(clicked()), this, SLOT(emitAnimationSignal()));

    editDelay = new QLineEdit(this); // edit box to enter animation speed
    btn->setFixedWidth(80);
    editDelay->setFixedWidth(80);

    btn->setText("animate");


    // display thumbnails linearly
    containerLayout = new QGraphicsLinearLayout;

    // display for thumbnails of current frames
    containerScene = new QGraphicsScene(this);
    container = new QGraphicsView(containerScene, this);

    form = new QGraphicsWidget;
    form->setLayout(containerLayout);
    containerScene->addItem(form);

    //container->setBackgroundBrush(Qt::black);
    //containerScene->addText("blah blah blah frames show up here");

    layout->addWidget(container, 60); // the container will occupy 60% of the timeline
    layout->addWidget(btn, 20);
    layout->addWidget(editDelay, 20);

    // testing
    //addFrameToTimeline(QImage("C:\\Users\\Nicholas\\Desktop\\programming\\build-cute_animator-Desktop_Qt_5_12_2_MinGW_32_bit-Debug\\debug\\screen12.bmp"));

    setLayout(layout);
}

// is this even working? can we make the initial scribble area to be a solid color to check?
void Timeline::addFrameToTimeline(QImage image){

   // qDebug() << "image is null: " << image.isNull();

    /* check out the image to make sure its what you expect?
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
    }*/

    // need to make sure image is scaled
    QPixmap pixmap = QPixmap::fromImage(image);

    //qDebug() << "image width: " << pixmap.width();
    //qDebug() << "image height: " << pixmap.height();

    //QPixmap("C:\\Users\\Nicholas Hung\\Desktop\\build-cute_animator-Desktop_Qt_5_13_0_MinGW_32_bit-Debug\\debug\\bocchi2.png"); //QPixmap::fromImage(image);
    // use painer.drawPixmap to add the actual image to another pixmap while also having borders that don't interfere with the original image
    QPixmap scaledPixmap = pixmap.scaled(50,50,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    QPainter* painter = new QPainter(&scaledPixmap);
    painter->setPen(QPen(Qt::black, 3));
    painter->drawRect(0,0,scaledPixmap.width()-1,scaledPixmap.height()-1);
    delete painter;

    QGraphicsPixmapItem* frame = new QGraphicsPixmapItem(scaledPixmap);

    // YOU NEED TO DELETE THIS SOMEHOW IF THE FRAME NEEDS TO BE REMOVED
    // YOU ARE RESPONSIBLE FOR PROPER DELETION OK?
    //FrameThumbnail* frame = new FrameThumbnail(scaledPixmap, 50, 50);
    containerScene->addItem(frame);

    // fix this
    //containerLayout->addItem(frame);

    //QGraphicsPixmapItem* frame2 = new QGraphicsPixmapItem(scaledPixmap);
   // frame2->moveBy(80, 0);
    //containerScene->addItem(frame2);

    container->show();
   // qDebug() << "supposed to add frame to timeline...";
}

void Timeline::updateTimeline(){
    // clear the timeline
    QList<QGraphicsItem*> images = containerScene->items();
    for(int i = 0; i < images.size(); i++){
        containerScene->removeItem(images[i]);
    }

    QVector<ScribbleArea*> frames = ((MainWindowContent *)parentWidget)->getAllFrames();
    for(int i = 0; i < frames.size(); i++){
        addFrameToTimeline(frames[i]->getImage());
    }
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
