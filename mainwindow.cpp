#include <QtWidgets>
#include <iostream>
#include "mainwindow.h"

//! [0]
MainWindow::MainWindow()
{
    content = new MainWindowContent(this);
    scribbleArea = content->getCurrFrame();
    setCentralWidget(content);

    createActions();
    createMenus();

    setWindowTitle(tr("Simple Animation Application"));
    resize(1000, 850); // height, width
}

//! [1]
void MainWindow::closeEvent(QCloseEvent *event)
//! [1] //! [2]
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}
//! [2]

//! [3]
void MainWindow::open()
//! [3] //! [4]
{
    scribbleArea = content->getCurrFrame();
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty())
            scribbleArea->openImage(fileName);
    }
}
//! [4]

//! [5]
void MainWindow::save()
//! [5] //! [6]
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}
//! [6]
//!
void MainWindow::saveAllFrames(){
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFileAll(fileFormat);
}

//! [7]
void MainWindow::penColor()
//! [7] //! [8]
{
    scribbleArea = content->getCurrFrame();
    QColor newColor = QColorDialog::getColor(scribbleArea->penColor());
    if (newColor.isValid())
        scribbleArea->setPenColor(newColor);
}
//! [8]

//! [9]
void MainWindow::penWidth()
//! [9] //! [10]
{
    scribbleArea = content->getCurrFrame();
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Scribble"),
                                        tr("Select pen width:"),
                                        scribbleArea->penWidth(),
                                        1, 50, 1, &ok);
    if (ok)
        scribbleArea->setPenWidth(newWidth);
}
//! [10]

//! [11]
void MainWindow::about()
//! [11] //! [12]
{
    QMessageBox::about(this, tr("About Scribble"),
            tr("<p>The <b>Scribble</b> example shows how to use QMainWindow as the "
               "base widget for an application, and how to reimplement some of "
               "QWidget's event handlers to receive the events generated for "
               "the application's widgets:</p><p> We reimplement the mouse event "
               "handlers to facilitate drawing, the paint event handler to "
               "update the application and the resize event handler to optimize "
               "the application's appearance. In addition we reimplement the "
               "close event handler to intercept the close events before "
               "terminating the application.</p><p> The example also demonstrates "
               "how to use QPainter to draw an image in real time, as well as "
               "to repaint widgets.</p>"));
}
//! [12]

//! [13]
void MainWindow::createActions()
//! [13] //! [14]
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    const QList<QByteArray> imageFormats = QImageWriter::supportedImageFormats();
    for (const QByteArray &format : imageFormats) {
        QString text = tr("%1...").arg(QString::fromLatin1(format).toUpper());

        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, &QAction::triggered, this, &MainWindow::save);
        saveAsActs.append(action);

        QAction *action2 = new QAction(text, this);
        action2->setData(format);
        connect(action2, &QAction::triggered, this, &MainWindow::saveAllFrames);
        saveAsAllFramesActs.append(action2);

    }

    printAct = new QAction(tr("&Print..."), this);
    connect(printAct, &QAction::triggered, scribbleArea, &ScribbleArea::print);

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, &QAction::triggered, this, &MainWindowContent::close);

    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, &QAction::triggered, this, &MainWindow::penColor);

    penWidthAct = new QAction(tr("Pen &Width..."), this);
    connect(penWidthAct, &QAction::triggered, this, &MainWindow::penWidth);

    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, &QAction::triggered,
            scribbleArea, &ScribbleArea::clearImage);

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
}
//! [14]

//! [15]
void MainWindow::createMenus()
//! [15] //! [16]
{
    // https://www.qtcentre.org/threads/42976-Add-QMenuBar-into-QWidget

    saveAsMenu = new QMenu(tr("&Save As"), this);
    for (QAction *action : qAsConst(saveAsActs))
        saveAsMenu->addAction(action);

    saveAllFramesMenu = new QMenu(tr("&Save All Frames As"), this);
    for (QAction *action : qAsConst(saveAsAllFramesActs))
        saveAllFramesMenu->addAction(action);


    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addMenu(saveAllFramesMenu);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    //optionMenu->addSeparator();
   // optionMenu->addAction(clearScreenAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(helpMenu);
}
//! [16]

//! [17]
bool MainWindow::maybeSave()
//! [17] //! [18]
{
    scribbleArea = content->getCurrFrame();
    if (scribbleArea->isModified()) {
       QMessageBox::StandardButton ret;
       ret = QMessageBox::warning(this, tr("Scribble"),
                          tr("The image has been modified.\n"
                             "Do you want to save your changes?"),
                          QMessageBox::Save | QMessageBox::Discard
                          | QMessageBox::Cancel);
        if (ret == QMessageBox::Save) {
            return saveFile("png");
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}
//! [18]

//! [19]
bool MainWindow::saveFile(const QByteArray &fileFormat)
//! [19] //! [20]
{
    scribbleArea = content->getCurrFrame();
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString::fromLatin1(fileFormat.toUpper()))
                               .arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty()) {
        return false;
    } else {
        return scribbleArea->saveImage(fileName, fileFormat.constData());
    }
}
//! [20]
//!

void MainWindow::saveFileAll(const QByteArray &fileFormat)
{
    //scribbleArea = content->getCurrFrame();
    QString initialPath = QDir::currentPath() + "/untitled";

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString::fromLatin1(fileFormat.toUpper()))
                               .arg(QString::fromLatin1(fileFormat)));

    if (!fileName.isEmpty()) {
        QVector<ScribbleArea*> allFrames = content->getAllFrames();
        for(int i = 0; i < allFrames.size(); i++){
            ScribbleArea* frame = allFrames[i];
            QString newFileName = fileName + "_" + QString::number(i) + "." + fileFormat;
            frame->saveImage(newFileName, fileFormat.constData());
        }
    }
}