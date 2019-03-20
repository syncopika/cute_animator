QT += widgets
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

HEADERS       = \
                scribblearea.h \
    framecontroller.h \
    mainwindowcontent.h \
    mainwindow.h \
    borderlayout.h \
    timeline.h
SOURCES       = main.cpp \
                scribblearea.cpp \
    framecontroller.cpp \
    mainwindowcontent.cpp \
    mainwindow.cpp \
    borderlayout.cpp \
    timeline.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/scribble
INSTALLS += target

DISTFILES += \
    bugstofix
