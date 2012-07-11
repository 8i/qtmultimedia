load(qt_build_config)

TARGET = wmfengine
QT += multimedia-private network
!isEmpty(QT.widgets.name) {
    QT += multimediawidgets-private
    DEFINES += HAVE_WIDGETS
}
PLUGIN_TYPE=mediaservice

load(qt_plugin)

DESTDIR = $$QT.multimedia.plugins/$${PLUGIN_TYPE}

DEPENDPATH += .
INCLUDEPATH += .

HEADERS += \
    wmfserviceplugin.h \
    mfstream.h \
    sourceresolver.h \
    samplegrabber.h

SOURCES += \
    wmfserviceplugin.cpp \
    mfstream.cpp \
    sourceresolver.cpp \
    samplegrabber.cpp

include (player/player.pri)
include (decoder/decoder.pri)

OTHER_FILES += \
    wmf.json
