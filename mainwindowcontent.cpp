#include <QtWidgets>
#include "headers/mainwindowcontent.h"
#include <iostream>

// https://doc.qt.io/qt-5/mainwindow.html
// https://doc.qt.io/qt-5/qtwidgets-tutorials-widgets-nestedlayouts-example.html
// https://doc.qt.io/qt-5/qtwidgets-layouts-borderlayout-example.html
// http://redino.net/blog/2014/05/qt-qwidget-add-menu-bar/
// https://forum.qt.io/topic/40676/how-to-set-initial-height-for-a-widget
// https://doc.qt.io/archives/qt-4.8/graphicsview.html#graphics-view
// https://www.qtcentre.org/threads/65194-Playing-Image-Sequence-using-Qt
// https://stackoverflow.com/questions/30330881/qt-cpp-delay-in-for-loop - this might be better for animation
// https://doc.qt.io/qt-5/qtimer.html

MainWindowContent::MainWindowContent(QWidget *parent)
: QWidget(parent)
{

    frameController = new FrameController(this);
    scribbleArea = new ScribbleArea(this);
    timeline = new Timeline(this);
    onionLayer = new ScribbleArea(this);
    frames.push_back(scribbleArea);
    animationCounter = 0;
    isAnimating = false;
    frameDelay = 500;

    // connect button signals to main window's slots
    connect(frameController, &FrameController::addFrame, this, &MainWindowContent::addFrame);
    connect(frameController, &FrameController::removeFrame, this, &MainWindowContent::removeFrame);
    connect(frameController, &FrameController::nextFrame, this, &MainWindowContent::nextFrame);
    connect(frameController, &FrameController::prevFrame, this, &MainWindowContent::prevFrame);
    connect(frameController, &FrameController::clearFrame, this, &MainWindowContent::clearFrame);

    // connect the timeline's doAnimation signal to this windowcontent's animation function
    connect(timeline, &Timeline::doAnimation, this, &MainWindowContent::preAnimation);
    connect(this, &MainWindowContent::animateSignal, this, &MainWindowContent::animate);

    layout = new BorderLayout();
    layout->addWidget(scribbleArea, BorderLayout::Center);
    layout->addWidget(frameController, BorderLayout::East);
    layout->addWidget(timeline, BorderLayout::South);
    setLayout(layout);
}


void MainWindowContent::addFrame(){
    //std::cout << "signal to add a new frame received!" << std::endl;
    ScribbleArea* newFrame = new ScribbleArea(this);
    frames.push_back(newFrame);

    // use QStackedWidget instead??? https://stackoverflow.com/questions/4625102/how-to-replace-a-widget-with-another-using-qt
    //layout->removeWidget(scribbleArea);
   // scribbleArea = newFrame;
    //layout->addWidget(scribbleArea, 0, 5);
}

void MainWindowContent::removeFrame(){
    // if the frame to be removed is the very first one,
    // then we need to move the current frame to the next one.
    // if there is only 1 frame, just clear it.
    // for any other case, move the current frame to the previous frame.
    int currFrame = frameController->getCurrFrame();
    int numFrames = frameController->getNumFrames();

    ScribbleArea* temp = scribbleArea;
    layout->removeWidget(temp);
    temp->setVisible(false);

    // eject temp from frames array
    QVector<ScribbleArea*> tempFrames;
    for(int i = 0; i < frames.size(); i++){
        if(frames[i] != scribbleArea){
            tempFrames.push_back(frames[i]);
        }
    }

    if(currFrame == 0){
        // set the current frame to now be the next one
        scribbleArea = frames[currFrame+1];
        // correct numFrames
        frameController->setNumFrames(numFrames-1);
        frameController->setCurrFrame(currFrame+1);
    }else{
        // if deleting any other frame, move curr frame to be previous frame
        scribbleArea = frames[currFrame-1];
        // correct numFrames
        frameController->setNumFrames(numFrames-1);
        frameController->setCurrFrame(currFrame-1);
    }

    layout->addWidget(scribbleArea, BorderLayout::Center);
    scribbleArea->setVisible(true);

    // delete old image
    delete temp;

    frames = tempFrames;
}

// for onion skin?
// https://forum.qt.io/topic/41237/how-to-set-opacity-of-a-qimage/7
//
void MainWindowContent::nextFrame(){

    layout->removeWidget(scribbleArea);
    scribbleArea->setVisible(false);

    // add next frame and show
    scribbleArea = frames[frameController->getCurrFrame()];
    layout->addWidget(scribbleArea, BorderLayout::Center);
    scribbleArea->setVisible(true);

    if(!isAnimating){
        // remove old onion skin
        layout->removeWidget(onionLayer);
        onionLayer->setVisible(false);

        // set up new onion skin and show
        QImage prevFrame = frames[frameController->getCurrFrame() - 1]->getImage();
        QImage temp(prevFrame.size(), QImage::Format_ARGB32);
        QPainter painter(&temp); // set destination to temp
        painter.setOpacity(.3);
        painter.drawImage(QPoint(0, 0), prevFrame); // draw on temp from prevFrame data
        onionLayer->setImage(&temp);
        layout->addWidget(onionLayer, BorderLayout::Center);
        onionLayer->setVisible(true);
    }

    //onionLayer->stackUnder(scribbleArea);
}

void MainWindowContent::prevFrame(){

    // remove old onion skin
    if(!isAnimating){
        layout->removeWidget(onionLayer);
        onionLayer->setVisible(false);
    }

    // take out current frame
    layout->removeWidget(scribbleArea);
    scribbleArea->setVisible(false);

    // add previous frame to layout
    scribbleArea = frames[frameController->getCurrFrame()];
    layout->addWidget(scribbleArea, BorderLayout::Center);
    scribbleArea->setVisible(true);

    //scribbleArea->clearImage();
   // std::cout << scribbleArea << std::endl;
}

void MainWindowContent::clearFrame(){
    scribbleArea->clearImage();
}

void MainWindowContent::preAnimation(int frameDelay){
    std::cout << "frame delay: " << frameDelay << std::endl;
    this->frameDelay = frameDelay;
    emit animateSignal();
}

void MainWindowContent::animate(){
    if(animationCounter < frameController->getNumFrames()){
        isAnimating = true;
        frameController->setCurrFrame(animationCounter++);
        nextFrame();
        QTimer::singleShot(frameDelay, this, SLOT(animate()));
    }else{
        isAnimating = false;
        animationCounter = 0;
        return;
    }
}


ScribbleArea* MainWindowContent::getCurrFrame(){
    return frames[frameController->getCurrFrame()];
}

QVector<ScribbleArea*> MainWindowContent::getAllFrames(){
    return frames;
}
