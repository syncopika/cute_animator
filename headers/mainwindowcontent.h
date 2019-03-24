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
    QVector<ScribbleArea*> getAllFrames();

private slots:
    void addFrame();
    void removeFrame();
    void nextFrame();
    void prevFrame();
    void clearFrame();
    void doAnimation();

private:
    BorderLayout* layout;
    ScribbleArea* scribbleArea;
    ScribbleArea* onionLayer;
    QVector<ScribbleArea*> frames;
    FrameController* frameController;
    Timeline* timeline;
    int counter; // for animation
    bool isAnimating; // for animation
};


#endif
