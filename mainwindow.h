#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QList>
#include "mainwindowcontent.h"
#include "scribblearea.h"
#include "framecontroller.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void open();
    void save();
    void saveAllFrames();
    void penColor();
    void penWidth();
    void about();

private:
    void createActions();
    void createMenus();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);
    void saveFileAll(const QByteArray &fileFormat);

    MainWindowContent* content;
    ScribbleArea* scribbleArea;
    FrameController* frameController;

    QMenu *saveAsMenu;
    QMenu *saveAllFramesMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;

    QAction *openAct;
    QList<QAction *> saveAsActs;
    QList<QAction *> saveAsAllFramesActs;
    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *printAct;
    QAction *clearScreenAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
};


#endif // MAINWINDOW_H
