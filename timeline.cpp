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

    btn->setText("animate");
    layout->addWidget(btn);
    layout->addWidget(editDelay);

    setLayout(layout);

}

void Timeline::emitAnimationSignal(){
    emit doAnimation();
}
