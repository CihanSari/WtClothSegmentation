################################################################

# wt pri

################################################################

CONFIG += debug_and_release

win32{
    CONFIG(debug, debug|release) {
        SUFFIX=d
        WTLIBSUFFIX=-vc100-mt-gd-1_59
    } else {
        SUFFIX=
        WTLIBSUFFIX=-vc100-mt-1_59
    }
    WTPATH="D:/Projects/libs/Wt 3.3.6 msvs2010 x64/"
    LIBS += -L$${WTPATH}/bin
    LIBS += -L$${WTPATH}/lib
    WTLIBPREFIX=
    WTLIBSUFFIX = $${SUFFIX}
    INCLUDEPATH += $${WTPATH}/include
} else {
    LIBS += -L/usr/lib
    WTLIBPREFIX=
    WTLIBSUFFIX=
    INCLUDEPATH += /usr/include
    LIBS += -L/usr/lib/x86_64-linux-gnu\
            -lboost_system -lz
}


LIBS += -l$${WTLIBPREFIX}wt$${WTLIBSUFFIX}\
        -l$${WTLIBPREFIX}wthttp$${WTLIBSUFFIX}
