#ifndef MAINWINDOWCONTENT_H
#define MAINWINDOWCONTENT_H

#include <QList>
#include <QWidget>
#include <QMenu>
#include "framecontroller.h"
#include "scribblearea.h"
#include "borderlayout.h"
#include "timeline.h"

class ScribbleArea;

class MainWindowContent : public QWidget
{
    Q_OBJECT

public:
    MainWindowContent(QWidget *parent = nullptr);
    ScribbleArea* getCurrFrame();
    FrameController* getFrameController();
    QVector<ScribbleArea*> getAllFrames();

signals:
    void animateSignal(); // this does the actual animating

private slots:
    void addFrame();
    void removeFrame();
    void nextFrame();
    void prevFrame();
    void clearFrame();
    void preAnimation(int frameDelay); // update the delay between frames, then animate
    void animate();

private:
    BorderLayout* layout;
    ScribbleArea* scribbleArea;
    ScribbleArea* onionLayer;
    QVector<ScribbleArea*> frames;
    FrameController* frameController;
    Timeline* timeline;
    int animationCounter; // for animation
    bool isAnimating; // for animation
    int frameDelay; // for animation
};


#endif
