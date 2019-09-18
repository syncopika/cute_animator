#include "headers/framecontroller.h"
#include <QBoxLayout>
#include <QLabel>
#include <QShortcut>
#include <QKeySequence>
#include <QDebug>

/*
 *   provides adding, removing, clearing, and moving between frames functionalities
 *   need to provide tablet support for activating buttons?
 */
FrameController::FrameController(QWidget *parent)
{
    // set private vars
    numFrames = 1;
    currFrame = 0;
    tabletActive = false;

    // set up buttons/layout
    currFrameLabel = new QLabel(this);
    totalFramesLabel = new QLabel(this);

    totalFramesLabel->setMaximumHeight(15);
    currFrameLabel ->setMaximumHeight(15);

    nextBtn = new QPushButton(this);
    prevBtn = new QPushButton(this);
    addBtn = new QPushButton(this);
    removeBtn = new QPushButton(this);
    clearBtn = new QPushButton(this);

    addBtn->installEventFilter(this);
    nextBtn->installEventFilter(this);
    prevBtn->installEventFilter(this);
    removeBtn->installEventFilter(this);
    clearBtn->installEventFilter(this);

    prevBtn->setText("prev");
    nextBtn->setText("next");
    removeBtn->setText("remove");
    addBtn->setText("add");
    clearBtn->setText("clear");
    currFrameLabel->setText("curr frame: 1");
    totalFramesLabel->setText("total frames: 1");

    // hook up each button with their corresponding action
    connect(nextBtn, SIGNAL(clicked()), this, SLOT(nextButtonClicked()));
    connect(prevBtn, SIGNAL(clicked()), this, SLOT(prevButtonClicked()));
    connect(addBtn, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
    connect(removeBtn, SIGNAL(clicked()), this, SLOT(removeButtonClicked()));
    connect(clearBtn, SIGNAL(clicked()), this, SLOT(clearButtonClicked()));

    // hookup some keys to the button actions as well
    // https://stackoverflow.com/questions/4629629/assign-shortcut-keys-to-buttons-qt-c
    // https://thispointer.com/c11-lambda-how-to-capture-member-variables-inside-lambda-function/
    QShortcut *rightKey = new QShortcut(QKeySequence(Qt::Key_Right), nextBtn);
    connect(rightKey, &QShortcut::activated, [this](){nextBtn->animateClick();}); // using an anonymous function!

    QShortcut *leftKey = new QShortcut(QKeySequence(Qt::Key_Left), prevBtn);
    connect(leftKey, &QShortcut::activated, [this](){prevBtn->animateClick();});

    QShortcut *plusKey = new QShortcut(QKeySequence(Qt::Key_Plus), addBtn);
    connect(plusKey, &QShortcut::activated, [this](){addBtn->animateClick();});

    QShortcut *minusKey = new QShortcut(QKeySequence(Qt::Key_Minus), removeBtn);
    connect(minusKey, &QShortcut::activated, [this](){removeBtn->animateClick();});

    QShortcut *spaceKey = new QShortcut(QKeySequence(Qt::Key_Space), addBtn);
    connect(spaceKey, &QShortcut::activated, [this](){addBtn->animateClick();});

    QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    layout->addWidget(totalFramesLabel);
    layout->addWidget(currFrameLabel);

    layout->addWidget(addBtn);
    layout->addWidget(nextBtn);
    layout->addWidget(prevBtn);
    layout->addWidget(clearBtn);
    layout->addWidget(removeBtn);

    setLayout(layout);
}

int FrameController::getCurrFrame(){
    return currFrame;
}

int FrameController::getNumFrames(){
    return numFrames;
}

void FrameController::prevButtonClicked(){
    if(currFrame - 1 >= 0){
        currFrame--;
        currFrameLabel->setText("curr frame: " + QString::number(currFrame+1));
        emit prevFrame();
    }
}

void FrameController::nextButtonClicked(){
    if(currFrame + 1 < numFrames){
        currFrame++;
        currFrameLabel->setText("curr frame: " + QString::number(currFrame+1));
        emit nextFrame();
    }
}

void FrameController::addButtonClicked(){
    qDebug() << "clicked Add button!";
    numFrames++;
    totalFramesLabel->setText("total frames: " + QString::number(numFrames));
    emit addFrame();
}

void FrameController::removeButtonClicked(){
    if(numFrames == 1){
        emit clearFrame();
    }else{
        totalFramesLabel->setText("total frames: " + QString::number(numFrames-1));
        emit removeFrame();
    }
}

void FrameController::clearButtonClicked(){
    emit clearFrame();
}

void FrameController::setNumFrames(int num){
    numFrames = num;
}

void FrameController::setCurrFrame(int curr){
    currFrame = curr;
    currFrameLabel->setText("curr frame: " + QString::number(currFrame+1));
}

// https://stackoverflow.com/questions/36050747/qt-c-how-to-get-event-target-object
void FrameController::tabletEvent(QTabletEvent *event)
{
    if(!tabletActive){
        event->ignore();
        return;
    }

    switch(event->type()){
        case QEvent::TabletPress:
        {
            int eventPosY = event->y();
            int addBtnY = addBtn->y();
            int removeBtnY = removeBtn->y();
            int nextBtnY = nextBtn->y();
            int prevBtnY = prevBtn->y();
            int clearBtnY = clearBtn->y();

            if(eventPosY <= addBtnY + 15 && eventPosY >= addBtnY){
                qDebug() << "clicked add button with tablet pen!";
                addBtn->animateClick();
            }else if(eventPosY <= removeBtnY + 15 && eventPosY >= removeBtnY){
                removeBtn->animateClick();
                qDebug() << "clicked Remove button!";
            }else if(eventPosY <= nextBtnY + 15 && eventPosY >= nextBtnY){
                nextBtn->animateClick();
                qDebug() << "clicked Next button!";
            }else if(eventPosY <= prevBtnY + 15 && eventPosY >= prevBtnY){
                prevBtn->animateClick();
                qDebug() << "clicked Prev button!";
            }else if(eventPosY <= clearBtnY + 15 && eventPosY >= clearBtnY){
                clearBtn->animateClick();
                qDebug() << "clicked Clear button!";
            }
        }
        break;
        default:
            return;
    }
    event->accept();
}

// slot
void FrameController::setTabletActive(bool active){
    qDebug() << "received signal from app to toggle tablet active in framecontroller!";
    tabletActive = active;
}

bool FrameController::eventFilter(QObject* obj, QEvent* event){
    if(tabletActive && event->type() == QEvent::MouseButtonPress){
        qDebug() << "button was pressed and tabletactive";
        // don't let mousebuttonpress event come through when using tablet (only tabletevent should be handled)
        return true;
    }
    return QWidget::eventFilter(obj, event);
}
