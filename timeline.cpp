#include "headers/timeline.h"
#include <QHBoxLayout>
#include <QTimeLine>
#include <QPushButton>
#include <QProgressBar>
#include <QLineEdit>

Timeline::Timeline(QWidget *parent)
{

    QHBoxLayout* layout = new QHBoxLayout(this);
    QPushButton* btn = new QPushButton();
    connect(btn, SIGNAL(clicked()), this, SLOT(emitAnimationSignal()));

    QLineEdit* editDelay = new QLineEdit(this);
    btn->setFixedWidth(80);
    editDelay->setFixedWidth(60);

    btn->setText("animate");
    layout->addWidget(btn);
    layout->addWidget(editDelay);

    setLayout(layout);

}

void Timeline::emitAnimationSignal(){
    // get int from textbox, which is the time delay between frames.
    emit doAnimation(500);
}
