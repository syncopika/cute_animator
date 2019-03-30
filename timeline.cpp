#include "headers/timeline.h"
#include <QString>
#include <iostream>
#include <QTextStream>

Timeline::Timeline(QWidget *parent)
{
    layout = new QHBoxLayout(this);
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
