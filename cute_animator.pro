# https://stackoverflow.com/questions/6873936/how-to-change-a-projects-name-in-qtcreator

QT += widgets
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

HEADERS       = \
    headers/scribblearea.h \
    headers/framecontroller.h \
    headers/mainwindowcontent.h \
    headers/mainwindow.h \
    headers/borderlayout.h \
    headers/timeline.h \
    headers/framethumbnail.h
SOURCES       = main.cpp \
                scribblearea.cpp \
    framecontroller.cpp \
    mainwindowcontent.cpp \
    mainwindow.cpp \
    borderlayout.cpp \
    timeline.cpp \
    framethumbnail.cpp \

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/scribble
#INSTALLS += target

DISTFILES += \
    other/bugstofix \
    other/todo

RESOURCES +=
