#ifndef TIMELINE_H
#define TIMELINE_H

#include <QWidget>

class Timeline : public QWidget
{
    Q_OBJECT

public:
    Timeline(QWidget *parent = nullptr);

signals:
    void doAnimation(int frameDelay);

public slots:
    void emitAnimationSignal();

};

#endif // TIMELINE_H
