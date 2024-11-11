QT       += core gui
QT       += multimedia multimediawidgets
QT       += spatialaudio

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Apple.cpp \
    AudioPlayer.cpp \
    BurstWeapon.cpp \
    Cycle.cpp \
    EnemyProjectile.cpp \
    EnemyTank.cpp \
    Fireball.cpp \
    Fonts.cpp \
    GameCharacter.cpp \
    GameScene.cpp \
    HUD.cpp \
    Health.cpp \
    Heart.cpp \
    Item.cpp \
    Menu.cpp \
    Score.cpp \
    Settings.cpp \
    Shield.cpp \
    TripleShot.cpp \
    VIew.cpp \
    main.cpp

HEADERS += \
    Apple.h \
    AudioPlayer.h \
    BurstWeapon.h \
    Character.h \
    Cycle.h \
    EStates.h \
    EnemyProjectile.h \
    EnemyTank.h \
    Fireball.h \
    Fonts.h \
    GameCharacter.h \
    GameScene.h \
    HUD.h \
    Health.h \
    Heart.h \
    Item.h \
    Menu.h \
    Projectile.h \
    Score.h \
    Settings.h \
    Shield.h \
    TripleShot.h \
    VIew.h

#INCLUDEPATH += "C:/Program Files (x86)/Visual Leak Detector/include/" LIBS      += -L"C:/Program Files (x86)/Visual Leak Detector/lib/Win64"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
