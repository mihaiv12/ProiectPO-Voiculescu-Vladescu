QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    User.cpp \
    Product.cpp \
    Order.cpp \
    Session.cpp \
    AuthController.cpp \
    LoginWindow.cpp \
    CatalogWindow.cpp \
    CartWindow.cpp

HEADERS += \
    User.h \
    Product.h \
    Order.h \
    Session.h \
    AuthController.h \
    LoginWindow.h \
    CatalogWindow.h \
    CartWindow.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target