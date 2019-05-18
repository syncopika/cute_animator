#ifndef TIMELINE_H
#define TIMELINE_H

#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QLineEdit>
#include <QGraphicsView>
#include <QGraphicsScene>

class Timeline : public QWidget
{
    Q_OBJECT

public:
    Timeline(QWidget *parent = nullptr);
    void addFrameToTimeline(QImage image);

signals:
    void doAnimation(int frameDelay);

public slots:
    void emitAnimationSignal();

private:
    QHBoxLayout* layout;
    QPushButton* btn;
    QLineEdit* editDelay;

    QGraphicsView* container;
    QGraphicsScene* containerScene;
};

#endif // TIMELINE_H
