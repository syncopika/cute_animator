#ifndef FRAMECONTROLLER_H
#define FRAMECONTROLLER_H

#include <QWidget>
#include <QLabel>
#include <QTabletEvent>
#include <QPushButton>

class FrameController : public QWidget
{

    Q_OBJECT

public:
    FrameController(QWidget *parent = nullptr);
    int getNumFrames();
    int getCurrFrame();
    void setNumFrames(int num);
    void setCurrFrame(int curr);

private:
    int numFrames;
    int currFrame;

    QLabel* currFrameLabel;
    QLabel* totalFramesLabel;

    QPushButton* nextBtn;
    QPushButton* prevBtn;
    QPushButton* addBtn;
    QPushButton* removeBtn;
    QPushButton* clearBtn;


protected:
    void tabletEvent(QTabletEvent *event) override;


signals:
    void addFrame();
    void removeFrame();
    void nextFrame();
    void prevFrame();
    void clearFrame(); //sent when only one frame and remove requested or when clear button is pressed


public slots:
    void prevButtonClicked();
    void nextButtonClicked();
    void addButtonClicked();
    void removeButtonClicked();
    void clearButtonClicked();

};

#endif // FRAMECONTROLLER_H
