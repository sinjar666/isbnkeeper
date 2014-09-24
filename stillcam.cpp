/*-----------------------------------------------------------------------/
/--------------------------MODULE--STILLCAM------------------------------/
/---------file:stillcam.h------------------------------------------------/
/---Author :: Srijan Mukherjee-------------------------------------------/
/-This module allows the user to scan a document or paper using----------/
/-the phone's camera.----------------------------------------------------/
/------------CAM SETTINGS ARE--------------------------------------------/
/----FOCUS MODE = AUTO, MACROFOCUS ENABLED-------------------------------/
/---------EXPOSURE MODE = AUTO ------------------------------------------/
/----------FLASH= OFF----------------------------------------------------/
/Makes use of gdigicam camerabin api and gstreamer plugins from bad set--/
/DO NOT FORCEFULLY END THE APPLICATION AS THIS DISABLES THE DEFAULT------/
/camera-ui AND LATER ENABLES IT ON CLOSING APP AS IT BINDS TO DBUS SIGNALS
/FOR SHUTTER RELEASE AND FOCUS LOCK--------------------------------------/
/IN THE EVENT OF SUCH FORCEFULLY ENDING THE APPLICATION USE dsmetool to--/
/restart camera-ui-------------------------------------------------------/
/----$ /usr/sbin/dsmetool -t /usr/bin/camera-ui--------------------------/
/Above to resume the normal functioning of the default camera application/
/To be used only on supported linux based os, eg Maemo5-fremantle-pr1.3-*/



#include "stillcam.h"

bool cam_capturing,started;
 bool Wait;

static QDBusConnection dBusConnection = QDBusConnection::systemBus();

//DBUS PATHS
#define DBUS_SHUTTER_RELEASE "/org/freedesktop/Hal/devices/platform_cam_launch"
#define DBUS_FOCUS_LOCK "/org/freedesktop/Hal/devices/platform_cam_focus"
#define DBUS_CAM_SHUTTER "/org/freedesktop/Hal/devices/platform_cam_shutter"

QDBusArgument &operator<<(QDBusArgument &argument, const Property &arg2)    {
    argument.beginStructure();
    argument << arg2.name << arg2.added << arg2.removed;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, Property &arg2)    {
    argument.beginStructure();
    argument >> arg2.name >> arg2.added >> arg2.removed;
    argument.endStructure();
    return argument;
}

QSize StillCam::minimumSizeHint() const
{
        return QSize(800, 600);
}

QSize StillCam::sizeHint() const
{
        return QSize(800,600);
}

void StillCam::paintEvent(QPaintEvent *event)   {
    if(isShutterOpen() && minimized==false) {
        QPainter painter(this);
        //QBrush brush;
        QColor color((colorkey & 0x00ff0000) >> 16,
                 (colorkey & 0x0000ff00) >> 8,
                 colorkey & 0x000000ff);

        painter.save();
        painter.fillRect(0, 0, width(), height(), color);
        painter.setPen(pencolor);
        painter.drawRect(375,165,100,75);
        painter.restore ();
    }
//    if(!isActiveWindow())   {
//        QPainter painter(this);
//        painter.save();
//        painter.setPen(QColor(Qt::white));
//        painter.drawText(*bound,Qt::AlignCenter,QString("<font size=10>Camera Standby</font>"),bound);
//        painter.restore();
//    }
    if(incorrect)  {
        QPainter painter(this);
        painter.save();
        painter.drawImage(QRectF(0,0,770,450),QImage(":/barcode_isbn.png"));
        painter.restore();
    }
    if(Wait)    {
        QPainter painter(this);
        painter.save();
        painter.drawImage(QRectF(0,0,800,480),QImage(":/please-wait.png"));
        painter.restore();
    }
}

void StillCam::closeEvent(QCloseEvent *event)
{
        g_digicam_manager_stop_bin(manager, NULL);
        process->execute("/usr/sbin/dsmetool -t /usr/bin/camera-ui");
        //process->deleteLater();
}

bool StillCam::eventFilter(QObject *obj, QEvent *event) {
    if(obj == this && event->type()==QEvent::ActivationChange)   {
        if(!isActiveWindow())   {
            minimized=true;
            process=new QProcess();
            process->execute("/usr/sbin/dsmetool -t /usr/bin/camera-ui");
            process->deleteLater();
            qDebug() << "Stopping bin...";
            g_digicam_manager_stop_bin(manager,NULL);
            repaint();
            qDebug() << "Gstreamer Bin stoppped.";
        }
        else if(minimized)    {
            minimized=false;
            process=new QProcess();
            process->execute("/usr/sbin/dsmetool -k /usr/bin/camera-ui");
            process->deleteLater();
            qDebug() << "Playing bin..";
            g_digicam_manager_play_bin(manager,winId(),NULL);
            qDebug() << "Gstreamer bin playing...";
        }
        return true;
    }
    else    {
        return QWidget::eventFilter(obj,event);
    }
}

void StillCam::setFlashMode(GDigicamFlashmode mode)  {
    GDigicamCamerabinFlashModeHelper *helper=NULL;
    helper = g_slice_new(GDigicamCamerabinFlashModeHelper);
    helper->flash_mode=mode;
    if(!g_digicam_manager_set_flash_mode(manager,helper->flash_mode,NULL,helper))   {
        qDebug() << "Error:Unable to set flash mode";
    }
    g_slice_free(GDigicamCamerabinFlashModeHelper,helper);
}

void StillCam::setResolution(GDigicamResolution res, GDigicamAspectratio ratio) {
    GDigicamCamerabinAspectRatioResolutionHelper *helper = g_slice_new(GDigicamCamerabinAspectRatioResolutionHelper);

    helper->aspect_ratio=ratio;
    helper->resolution=res;
    if(!g_digicam_manager_set_aspect_ratio_resolution(manager,helper->aspect_ratio,helper->resolution,NULL,helper))  {
        qDebug() << "ERROR: Unable to set aspect ratio and resolution. ";
    }

    g_slice_free(GDigicamCamerabinAspectRatioResolutionHelper,helper);
}

void StillCam::setLock(GDigicamLock lock)   {
    if(!cam_capturing)  {
        if(!started)    {
            g_digicam_manager_play_bin(manager,winId(),NULL);
            started=true;
        }
    qDebug() << "In set lock function.";
    GDigicamCamerabinLocksHelper *helper=g_slice_new(GDigicamCamerabinLocksHelper);

    helper->locks=lock;

    if(!g_digicam_manager_set_locks(manager,helper->locks,NULL,helper)) {
        qDebug() << "Error: unabble to set lock";

    }
    g_slice_free(GDigicamCamerabinLocksHelper,helper);
    }
}

void StillCam::previewStatus(bool status)   {
    GDigicamCamerabinPreviewHelper *helper = g_slice_new(GDigicamCamerabinPreviewHelper);

    if(status)
        helper->mode=G_DIGICAM_PREVIEW_ON;
    else
        helper->mode=G_DIGICAM_PREVIEW_OFF;

    if(!g_digicam_manager_set_preview_mode(manager,helper->mode,NULL,helper))    {
        qDebug() << "Error: Unable to set preview mode";
    }

    g_slice_free(GDigicamCamerabinPreviewHelper,helper);
}

void StillCam::startCapture(GDigicamManager *manager, gpointer data)    {
    qDebug() << "Capture start signal received.";
}

void StillCam::endCapture(GDigicamManager *manager, gpointer data)  {
    qDebug() << "Capture end signal received";
}

void StillCam::captureDone(GDigicamManager *manager, GString *fname, gpointer data) {
    qDebug() << "Capture done signal received.";
    cam_capturing=false;
    Wait=true;
    g_digicam_manager_stop_bin(manager,NULL);
   // emit imageSaved();

}



void StillCam::getPicture() {
    qDebug()<< "in get picture";
    GDigicamCamerabinPictureHelper *helper;

    helper = g_slice_new(GDigicamCamerabinPictureHelper);
    helper->file_path=g_strdup((const gchar *)Path);

    helper->metadata=NULL;
    if(!g_digicam_manager_capture_still_picture(manager,helper->file_path,NULL,helper))  {
        qDebug() << "Error: Unable to capture picture";
    }

    g_slice_free(GDigicamCamerabinPictureHelper,helper);
//    qDebug() << "Stopping bin...";
//    g_digicam_manager_stop_bin(manager,NULL);
//    qDebug() << "Gstreamer Bin stopped.";
    emit imageSaved();
}

void StillCam::setupCameraBin() {
    GstElement *bin;
    GDigicamDescriptor *descriptor=NULL;
    manager = g_digicam_manager_new();
    colorkey=1;

    //standard gstreamer bin setup for nokia-n900

    bin = g_digicam_camerabin_element_new ("v4l2camsrc",
                                           "dspmp4venc",
                                           "hantromp4mux",
                                           "pulsesrc",
                                           "nokiaaacenc",
                                           "jpegenc",
                                           NULL,
                                           "xvimagesink",
                                           &colorkey);
    descriptor = g_digicam_camerabin_descriptor_new(bin);
    descriptor = g_digicam_camerabin_descriptor_new (bin);
    descriptor->max_zoom_macro_enabled = 6;
    descriptor->max_zoom_macro_disabled = 6;
    descriptor->max_digital_zoom = 6;
    descriptor->supported_modes = descriptor->supported_modes |
            G_DIGICAM_MODE_STILL | G_DIGICAM_MODE_VIDEO;
    descriptor->supported_iso_sensitivity_modes = descriptor->supported_iso_sensitivity_modes |
            G_DIGICAM_ISOSENSITIVITYMODE_MANUAL |
            G_DIGICAM_ISOSENSITIVITYMODE_AUTO;
    descriptor->supported_white_balance_modes = descriptor->supported_white_balance_modes |
            G_DIGICAM_WHITEBALANCEMODE_MANUAL       |
            G_DIGICAM_WHITEBALANCEMODE_AUTO         |
            G_DIGICAM_WHITEBALANCEMODE_SUNLIGHT     |
            G_DIGICAM_WHITEBALANCEMODE_CLOUDY       |
            G_DIGICAM_WHITEBALANCEMODE_SHADE        |
            G_DIGICAM_WHITEBALANCEMODE_TUNGSTEN     |
            G_DIGICAM_WHITEBALANCEMODE_FLUORESCENT  |
            G_DIGICAM_WHITEBALANCEMODE_INCANDESCENT |
            G_DIGICAM_WHITEBALANCEMODE_FLASH        |
            G_DIGICAM_WHITEBALANCEMODE_SUNSET;
    descriptor->supported_audio_states = descriptor->supported_audio_states |
            G_DIGICAM_AUDIO_RECORDON |
            G_DIGICAM_AUDIO_RECORDOFF;
    descriptor->supported_preview_modes = descriptor->supported_preview_modes |
            G_DIGICAM_PREVIEW_ON |
            G_DIGICAM_PREVIEW_OFF;
    descriptor->supported_features = descriptor->supported_features |
            G_DIGICAM_CAPABILITIES_VIEWFINDER  |
            G_DIGICAM_CAPABILITIES_RESOLUTION  |
            G_DIGICAM_CAPABILITIES_ASPECTRATIO  |
            G_DIGICAM_CAPABILITIES_MANUALFOCUS |
            G_DIGICAM_CAPABILITIES_AUTOFOCUS   |
            G_DIGICAM_CAPABILITIES_MACROFOCUS  |
            G_DIGICAM_CAPABILITIES_DIGITALZOOM |
            G_DIGICAM_CAPABILITIES_MANUALEXPOSURE |
            G_DIGICAM_CAPABILITIES_AUTOEXPOSURE |
            G_DIGICAM_CAPABILITIES_AUTOWHITEBALANCE |
            G_DIGICAM_CAPABILITIES_MANUALWHITEBALANCE |
            G_DIGICAM_CAPABILITIES_AUTOISOSENSITIVITY |
            G_DIGICAM_CAPABILITIES_MANUALISOSENSITIVITY|
            G_DIGICAM_CAPABILITIES_FLASH |
            G_DIGICAM_CAPABILITIES_AUDIO |
            G_DIGICAM_CAPABILITIES_PREVIEW;
    descriptor->supported_flash_modes = descriptor->supported_flash_modes |
            G_DIGICAM_FLASHMODE_OFF  |
            G_DIGICAM_FLASHMODE_ON   |
            G_DIGICAM_FLASHMODE_AUTO |
            G_DIGICAM_FLASHMODE_REDEYEREDUCTION |
            G_DIGICAM_FLASHMODE_REDEYEREDUCTIONAUTO |
            G_DIGICAM_FLASHMODE_FILLIN;
    descriptor->supported_resolutions = descriptor->supported_resolutions |
            G_DIGICAM_RESOLUTION_HIGH |
            G_DIGICAM_RESOLUTION_MEDIUM |
            G_DIGICAM_RESOLUTION_LOW;
    descriptor->supported_aspect_ratios = descriptor->supported_aspect_ratios |
            G_DIGICAM_ASPECTRATIO_4X3 |
            G_DIGICAM_ASPECTRATIO_16X9;



    if(!g_digicam_manager_set_gstreamer_bin(manager,bin,descriptor,NULL))
        qDebug() << "Fatal Error: unable to set gstreamer bin";
    g_signal_connect(manager,"pict-done",(GCallback)captureDone,this);
    g_signal_connect(manager,"capture-start",(GCallback)startCapture,this);
    g_signal_connect(manager,"capture-end",(GCallback)endCapture,this);
    //g_signal_connect(manager,"image-preview",(GCallback)preview,this);

    GDigicamCamerabinModeHelper *m_helper = g_slice_new(GDigicamCamerabinModeHelper);
    m_helper->mode=G_DIGICAM_MODE_STILL;
    if(!g_digicam_manager_set_mode(manager,m_helper->mode,NULL,m_helper))
        qDebug() << "Error: unable to set to still mode.";
    g_slice_free(GDigicamCamerabinModeHelper,m_helper);

    setFlashMode(G_DIGICAM_FLASHMODE_OFF);
    //to scan a paper placed close we should not use flash otherwise glare occurs
    //hence flash is set off

    setResolution(G_DIGICAM_RESOLUTION_HIGH,G_DIGICAM_ASPECTRATIO_4X3);

    //Set the exposure to automatically adjust depending on external lighting conditions
    GDigicamCamerabinExposureModeHelper *e_helper=g_slice_new(GDigicamCamerabinExposureModeHelper);
    e_helper->exposure_mode=G_DIGICAM_EXPOSUREMODE_AUTO;
    if(!g_digicam_manager_set_exposure_mode(manager,e_helper->exposure_mode,NULL,NULL,e_helper))
        qDebug() << "Error:unable to set exposure mode";
    g_slice_free(GDigicamCamerabinExposureModeHelper,e_helper);


    //Set autofocus to on and set macro focus mode enabled
    GDigicamCamerabinFocusModeHelper *f_helper=g_slice_new(GDigicamCamerabinFocusModeHelper);
    f_helper->focus_mode=G_DIGICAM_FOCUSMODE_CENTROID;
    f_helper->macro_enabled=true;
    if(!g_digicam_manager_set_focus_mode(manager,f_helper->focus_mode,f_helper->macro_enabled,NULL,f_helper))
        qDebug() << "Unable to set autofocus";
    g_slice_free(GDigicamCamerabinFocusModeHelper,f_helper);

    //Fix the digital zoom to 3
    GDigicamCamerabinZoomHelper *z_helper=g_slice_new(GDigicamCamerabinZoomHelper);
    z_helper->value=3;
    gboolean digital=0;
    if(!g_digicam_manager_set_zoom(manager,z_helper->value,&digital,NULL,z_helper))
        qDebug() << "Unable to set zoom level";
    g_slice_free(GDigicamCamerabinZoomHelper,z_helper);
    //previewStatus(true);
    cam_capturing=false;
    previewStatus(false);
}


void StillCam::shutter_released(int num_updates, QList<Property> updates)   {
    QDBusInterface propertyInterface("org.freedesktop.Hal",DBUS_SHUTTER_RELEASE,"org.freedesktop.Hal.Device",QDBusConnection::systemBus());
    bool pressed=propertyInterface.call("GetProperty","button.state.value").arguments().at(0).toBool();
    if(pressed) {
        cam_capturing=true;
        getPicture();
    }
}

void StillCam::focus_locked(int num_updates, QList<Property> updates)   {
    QDBusInterface propertyInterface("org.freedesktop.Hal",DBUS_FOCUS_LOCK,"org.freedesktop.Hal.Device",QDBusConnection::systemBus());
    bool pressed = propertyInterface.call("GetProperty","button.state.value").arguments().at(0).toBool();
    if(pressed) {
        pencolor=Qt::green;
        repaint();
        setLock(G_DIGICAM_LOCK_AUTOFOCUS);
    }
    else    {
        pencolor=Qt::white;
        repaint();
        setLock(G_DIGICAM_LOCK_AUTOFOCUS_NONE);
    }


}

void StillCam::cam_shutter(int num_updates, QList<Property> updates)    {
    QDBusInterface propertyInterface("org.freedesktop.Hal",DBUS_CAM_SHUTTER,"org.freedesktop.Hal.Device",QDBusConnection::systemBus());
    bool closed=propertyInterface.call("GetProperty","button.state.value").arguments().at(0).toBool();
    if(!closed)  {
        qDebug() << "Ready to play bin.";
        if(message) message->hide();
        //message->deleteLater();
        g_digicam_manager_play_bin(manager,winId(),NULL);
    }
    else    {
        qDebug() << "Ready to stop bin";
        g_digicam_manager_stop_bin(manager,NULL);
        close();
    }
}

//void StillCam::screen_lock(int num_updates, QList<Property> updates)    {
//    QDBusInterface propertyInterface("org.freedesktop.Hal",DBUS_SCREEN_LOCK,"org.freedesktop.Hal.Device",QDBusConnection::systemBus());
//    bool closed=propertyInterface.call("GetProperty","button.state.value").arguments().at(0).toBool();
//    if(!closed) {
//        qDebug() << "locked.";
//    }
//    else    {
//        qDebug() << "unlocked.";
//    }
//}


StillCam::StillCam(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle(tr("Take an Image."));
    installEventFilter(this);
    minimized=false;
    incorrect=false;
    Wait=false;
    bound=new QRectF(0,0,width(),height());
    process=new QProcess();
    process->execute("/usr/sbin/dsmetool -k /usr/bin/camera-ui");
    qDBusRegisterMetaType<Property>();
    qDBusRegisterMetaType< QList<Property> >();

    Path="/home/user/isbn-image.jpg";
    pencolor=Qt::white;

    //Connecting slots for camera button to dbus signals
    QDBusConnection::systemBus().connect(QString(),DBUS_SHUTTER_RELEASE,"org.freedesktop.Hal.Device","PropertyModified",this,
                                         SLOT(shutter_released(int,QList<Property>)));

    QDBusConnection::systemBus().connect(QString(),DBUS_FOCUS_LOCK,"org.freedesktop.Hal.Device","PropertyModified",
                                         this,SLOT(focus_locked(int,QList<Property>)));

    QDBusConnection::systemBus().connect(QString(),DBUS_CAM_SHUTTER,"org.freedesktop.Hal.Device","PropertyModified",
                                         this,SLOT(cam_shutter(int,QList<Property>)));

   dBusInterface = new QDBusInterface(MCE_SERVICE, MCE_REQUEST_PATH,
                                           MCE_REQUEST_IF, dBusConnection, this);
   dBusConnection.connect(MCE_SERVICE, MCE_SIGNAL_PATH, MCE_SIGNAL_IF,
                              MCE_DISPLAY_SIG, this, SLOT(displayStateChanged(const QDBusMessage &)));

   dBusInterface->callWithCallback(MCE_DISPLAY_STATUS_GET,QList<QVariant>(),this,SLOT(setDisplayState(QString)),SLOT(displayStateError(QDBusError)));

    setupCameraBin();
    started=true;
    connect(this,SIGNAL(imageSaved()),this,SLOT(doBarcodeRead()));
    if(isShutterOpen()) {
        qDebug() << "BIN PLAYING...";
        started=false;
        //if(message) message->hide();
        //delete(message);
        //delete(message);
        //g_digicam_manager_play_bin(manager,winId(),NULL);
    }
    else    {
        lay = new QVBoxLayout(this);
        message = new QLabel();
        message->setTextFormat(Qt::RichText);
        message->setAlignment(Qt::AlignCenter);
        message->setText("<font size=10><b> <p align='center'> Please open the shutter </p> </b></font>");
        lay->addWidget(message);
       // message->show();
    }
    //repaint();

}

void StillCam::displayStateChanged(const QDBusMessage &msg) {
    QString state=msg.arguments().at(0).toString();
    setDisplayState(state);
}

void StillCam::displayStateError(const QDBusError &error)   {
    qDebug() << error.message();

}

void StillCam::setDisplayState(const QString &state)    {
    if (!state.isEmpty()) {
            if (state == MCE_DISPLAY_ON_STRING) {
                qDebug() << "Display on";
                if(isShutterOpen()) {
                    qDebug() << "Playing the pipeline";
                    g_digicam_manager_play_bin(manager,winId(),NULL);
                    qDebug() << "Bin played";
                }
            }
            else if (state == MCE_DISPLAY_OFF_STRING)   {
                qDebug() << "Display off";
                qDebug("Stopping bin");
                g_digicam_manager_stop_bin(manager,NULL);
                qDebug("Bin stopped.");

            }
        }
}

bool StillCam::isShutterOpen()    {
    QFile *temp = new QFile("/sys/devices/platform/gpio-switch/cam_shutter/state");
    if(!temp->open(QIODevice::ReadOnly)) {
        qDebug() << "Thats strange.";
    }
    QTextStream stream(temp);
    QString state;
    stream >> state;
    temp->close();
    delete(temp);
    if(state=="open")
        return true;
    else return false;
}

StillCam::~StillCam()   {
    g_digicam_manager_stop_bin(manager,NULL);
    process->execute("/usr/sbin/dsmetool -t /usr/bin/camera-ui");
    delete(bound);
    //deleteLater(process);
}

void StillCam::doBarcodeRead()  {
    reader=new ReadEAN13(Path);
    connect(reader,SIGNAL(finished()),this,SLOT(checkBarcode()));
    //g_digicam_manager_stop_bin(manager,NULL);
    reader->start();
    //g_digicam_manager_stop_bin(manager,NULL);
}

void StillCam::checkBarcode()   {
    QString isbn=reader->getResult();
    if(isbn=="") {
        qDebug() << "Try Again...";
        reader->deleteLater();
        incorrect = true;
        Wait=false;
        g_digicam_manager_stop_bin(manager,NULL);
        repaint();
        sleep(3);
        incorrect=false;
        g_digicam_manager_play_bin(manager,winId(),NULL);
        repaint();
    }
    else    {
        qDebug() << "Result: " +isbn;
        reader->deleteLater();
        emit gotISBN(isbn);
    }
}
