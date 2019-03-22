#include <QPushButton>
#include <QBoxLayout>
#include "headers/framecontroller.h"
#include <iostream>
#include <QLabel>
#include <QShortcut>
#include <QKeySequence>

FrameController::FrameController(QWidget *parent)
{
    // set private vars
    numFrames = 1;
    currFrame = 0;

    // set up buttons/layout
    currFrameLabel = new QLabel(this);
    totalFramesLabel = new QLabel(this);

    //QPalette pal = palette();
    //pal.setColor(QPalette::Background, Qt::blue);
    //totalFramesLabel->setAutoFillBackground(true);
    //totalFramesLabel->setPalette(pal);

    totalFramesLabel->setMaximumHeight(15);
    currFrameLabel ->setMaximumHeight(15);

    QPushButton* nextBtn = new QPushButton();
    QPushButton* prevBtn = new QPushButton();
    QPushButton* addBtn = new QPushButton();
    QPushButton* removeBtn = new QPushButton();
    QPushButton* clearBtn = new QPushButton();

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
    QShortcut *rightKey = new QShortcut(QKeySequence(Qt::Key_Right), nextBtn);
    connect(rightKey, &QShortcut::activated, [nextBtn](){nextBtn->animateClick();}); // using an anonymus function!

    QShortcut *leftKey = new QShortcut(QKeySequence(Qt::Key_Left), prevBtn);
    connect(leftKey, &QShortcut::activated, [prevBtn](){prevBtn->animateClick();});

    QShortcut *plusKey = new QShortcut(QKeySequence(Qt::Key_Plus), addBtn);
    connect(plusKey, &QShortcut::activated, [addBtn](){addBtn->animateClick();});

    QShortcut *minusKey = new QShortcut(QKeySequence(Qt::Key_Minus), removeBtn);
    connect(minusKey, &QShortcut::activated, [removeBtn](){removeBtn->animateClick();});

    QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    layout->addWidget(totalFramesLabel);
    layout->addWidget(currFrameLabel);
    layout->addWidget(clearBtn);
    layout->addWidget(removeBtn);
    layout->addWidget(addBtn);
    layout->addWidget(prevBtn);
    layout->addWidget(nextBtn);

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
    //std::cout << "adding a new frame!" << std::endl;
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




