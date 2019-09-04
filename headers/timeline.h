#ifndef TIMELINE_H
#define TIMELINE_H

#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QLineEdit>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLinearLayout>
#include <QGraphicsWidget>

class Timeline : public QWidget
{
    Q_OBJECT

public:
    Timeline(QWidget *parent);
    void addFrameToTimeline(QImage image);
    void updateTimeline();

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
    QGraphicsLinearLayout* containerLayout;
    QGraphicsWidget* form;

    QWidget* parentWidget;
};

#endif // TIMELINE_H
