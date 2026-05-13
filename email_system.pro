QT = core network

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Commands.cpp \
        Cryp.cpp \
        Datastructures.cpp \
        Email.cpp \
        Input.cpp \
        JsonConverter.cpp \
        SaveAndLoad.cpp \
        UI.cpp \
        Validation.cpp \
        main.cpp

# === nlohmann/json ===
INCLUDEPATH += $$PWD/libs/nlohmann

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# === Crypto++ setup (cross-platform) ===
win32 {
    INCLUDEPATH += C:/Users/teemu/vcpkg/installed/x64-mingw-static/include
    LIBS += -LC:/Users/teemu/vcpkg/installed/x64-mingw-static/lib -lcryptopp
}

unix {
    LIBS += -lcryptopp
}

DEFINES += CRYPTOPP_ENABLE_NAMESPACE_WEAK

HEADERS += \
    Commands.h \
    Config.h \
    Cryp.h \
    DangerousPasswords.h \
    Datastructures.h \
    Email.h \
    Input.h \
    JsonConverter.h \
    SaveAndLoad.h \
    UI.h \
    Validation.h
