QT       += core gui \
            multimedia

CONFIG += c++20

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    commands/print_command.cpp\
    commands/attack_nearest_enemy_command.cpp \
    commands/command_factory.cpp \
    commands/down_command.cpp \
    commands/goto_command.cpp \
    commands/help_command.cpp \
    commands/left_command.cpp \
    commands/moveto_command.cpp \
    commands/right_command.cpp \
    commands/take_nearest_healthpack_command.cpp \
    commands/up_command.cpp \
    controllers/enemy_controller.cpp \
    controllers/healthpack_controller.cpp \
    controllers/p_enemy_controller.cpp \
    controllers/x_enemy_controller.cpp \
    pathfinder/astar.cpp \
    pathfinder/node.cpp \
    views/graphics/custom_scene.cpp \
    views/graphics/custom_view.cpp \
    views/graphics/enemy_graphics_view.cpp \
    game.cpp \
    main.cpp \
    mainwindow.cpp \
    views/graphics/energy_graphics_view.cpp \
    views/graphics/graphics_view.cpp \
    views/graphics/health_graphics_view.cpp \
    views/graphics/healthpack_graphics_view.cpp \
    views/graphics/p_enemy_graphics_view.cpp \
    controllers/protagonist_controller.cpp \
    views/graphics/protagonist_graphics_view.cpp \
    views/graphics/x_enemy_graphics_view.cpp \
    views/text/enemy_text_view.cpp \
    views/text/healthpack_text_view.cpp \
    views/text/p_enemy_textview.cpp \
    views/text/protagonist_textview.cpp \
    views/text/textview.cpp \
    views/graphics/tile_graphics_view.cpp\
    commands/command.cpp \
    views/text/x_enemy_textview.cpp

HEADERS += \
    commands/print_command.h\
    commands/attack_nearest_enemy_command.h \
    commands/command_factory.h \
    commands/commands.h \
    commands/down_command.h \
    commands/goto_command.h \
    commands/help_command.h \
    commands/left_command.h \
    commands/moveto_command.h \
    commands/right_command.h \
    commands/take_nearest_healthpack_command.h \
    commands/up_command.h \
    controllers/controllers_struct.h \
    controllers/enemy_controller.h \
    controllers/healthpack_controller.h \
    controllers/p_enemy_controller.h \
    controllers/poisened_tile_struct.h \
    controllers/x_enemy_controller.h \
    pathfinder/astar.h \
    pathfinder/comparator.h \
    pathfinder/node.h \
    views/graphics/custom_scene.h \
    views/graphics/custom_view.h \
    views/graphics/enemy_graphics_view.h \
    game.h \
    mainwindow.h \
    views/graphics/energy_graphics_view.h \
    views/graphics/graphics_view.h \
    views/graphics/health_graphics_view.h \
    views/graphics/healthpack_graphics_view.h \
    views/graphics/p_enemy_graphics_view.h \
    controllers/protagonist_controller.h \
    views/graphics/protagonist_graphics_view.h \
    views/graphics/x_enemy_graphics_view.h \
    views/text/enemy_text_view.h \
    views/text/healthpack_text_view.h \
    views/text/p_enemy_textview.h \
    views/text/protagonist_textview.h \
    views/text/textview.h \
    views/graphics/tile_graphics_view.h\
    commands/command.h \
    views/text/x_enemy_textview.h

FORMS += \
        mainwindow.ui
RESOURCES += \
        images.qrc \
        sounds.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

macx: LIBS += -L$$PWD/libs/ -lworld.1.0.0
else:win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/ -llibworld
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/ -llibworld
else:unix: LIBS += -L$$PWD/libs/ -lworld
win32: DEFINES+=WIN32;

INCLUDEPATH += $$PWD/includes
DEPENDPATH += $$PWD/includes


