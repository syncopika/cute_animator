#ifndef TIMELINE_H
#define TIMELINE_H

#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QLineEdit>

class Timeline : public QWidget
{
    Q_OBJECT

public:
    Timeline(QWidget *parent = nullptr);

signals:
    void doAnimation(int frameDelay);

public slots:
    void emitAnimationSignal();

private:
    QHBoxLayout* layout;
    QPushButton* btn;
    QLineEdit* editDelay;

};

#endif // TIMELINE_H
