QT = core network

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        commands.cpp \
        cryp.cpp \
        datastructures.cpp \
        email.cpp \
        input.cpp \
        jsonconverter.cpp \
        main.cpp \
        saveandload.cpp \
        ui.cpp \
        validation.cpp

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
    Config.h \
    commands.h \
    cryp.h \
    datastructures.h \
    email.h \
    input.h \
    jsonconverter.h \
    saveandload.h \
    ui.h \
    validation.h \
    dangerous_passwords.h
