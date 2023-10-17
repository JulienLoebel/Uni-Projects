QT       += core gui
QT += testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abcdialog.cpp \
    addbookingdialog.cpp \
    addcustomerdialog.cpp \
    airport.cpp \
    booking.cpp \
    checkdialog.cpp \
    customer.cpp \
    flightbooking.cpp \
    hotelbooking.cpp \
    main.cpp \
    rentalcarreservation.cpp \
    sortdialog.cpp \
    sortfunktor.cpp \
    test.cpp \
    travel.cpp \
    travelagency.cpp \
    upandaway.cpp

HEADERS += \
    abcdialog.h \
    addbookingdialog.h \
    addcustomerdialog.h \
    airport.h \
    booking.h \
    checkdialog.h \
    customer.h \
    flightbooking.h \
    graph.h \
    hotelbooking.h \
    rentalcarreservation.h \
    search.h \
    sortdialog.h \
    sortfunktor.h \
    test.h \
    travel.h \
    travelagency.h \
    upandaway.h

FORMS += \
    abcdialog.ui \
    addbookingdialog.ui \
    addcustomerdialog.ui \
    checkdialog.ui \
    sortdialog.ui \
    upandaway.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
