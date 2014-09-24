# Add files and directories to ship with the application 
# by adapting the examples below.
# file1.source = myfile
# dir1.source = mydir
DEPLOYMENTFOLDERS = # file1 dir1
#TARGET=isbnkeeper
TEMPLATE = app
symbian:TARGET.UID3 = 0xE6CE5078

# Smart Installer package's UID
# This UID is from the protected range 
# and therefore the package will fail to install if self-signed
# By default qmake uses the unprotected range value if unprotected UID is defined for the application
# and 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment
# the following lines and add the respective components to the 
# MOBILITY variable. 
# CONFIG += mobility
# MOBILITY +=


QT += core gui xml network webkit
maemo5  {
CONFIG += link_pkgconfig
PKGCONFIG += gtk+-2.0 \
            gstreamer-0.10 \
            gstreamer-plugins-bad-0.10 \
            gdigicam-0.3 \
            gdigicam-gst-camerabin-0.3
QT += dbus 

}

DEFINES += QT_NO_DEBUG_OUTPUT

SOURCES += main.cpp \
    Homescreen/searchbar.cpp \
    Homescreen/newfiledialog.cpp \
    Homescreen/middlewid.cpp \
    Homescreen/homescreen.cpp \
    Homescreen/filterdialog.cpp \
    Homescreen/delconfirmdialog.cpp \
    Homescreen/bottombar.cpp \
    Homescreen/engine/indexitem.cpp \
    Homescreen/engine/engine.cpp \
    Homescreen/configdialog.cpp \
    xml/xfile.cpp \
    stillcam.cpp \
    dip-backend/readean13.cpp \
    xml/isbn.cpp \
    BookInfo/upperwid.cpp \
    BookInfo/toplevelwid.cpp \
    BookInfo/bookinfowid.cpp \
    BookInfo/authpubwid.cpp \
    BookList/topmid.cpp \
    BookList/bottombar2.cpp \
    BookList/booklist.cpp \
    BookList/descdialog.cpp \
    Homescreen/aboutdialog.cpp \
    errorfiledialog.cpp \
    Homescreen/searchbox.cpp \
    fatalmessage.cpp \
    fatalnotavail.cpp \
    filecreationerr.cpp
HEADERS += \
    Homescreen/searchbar.h \
    Homescreen/newfiledialog.h \
    Homescreen/middlewid.h \
    Homescreen/homescreen.h \
    Homescreen/filterdialog.h \
    Homescreen/delconfirmdialog.h \
    Homescreen/bottombar.h \
    Homescreen/engine/indexitem.h \
    Homescreen/engine/engine.h \
    Homescreen/configdialog.h \
    xml/xfile.h \
    stillcam.h \
    dip-backend/readean13.h \
    xml/isbn.h \
    BookInfo/upperwid.h \
    BookInfo/toplevelwid.h \
    BookInfo/bookinfowid.h \
    BookInfo/authpubwid.h \
    BookList/topmid.h \
    BookList/booklist.h \
    BookList/bottombar2.h \
    BookList/descdialog.h \
    Homescreen/aboutdialog.h \
    errorfiledialog.h \
    Homescreen/searchbox.h \
    fatalmessage.h \
    fatalnotavail.h \
    filecreationerr.h


# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

OTHER_FILES += \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog \
    Homescreen/qml/Search-icon.png \
    retrieving.qml \
    please-wait.png \
    appicon.png \
    leather-book-preview.png \
    about.jpg

RESOURCES += \
    resources.qrc
