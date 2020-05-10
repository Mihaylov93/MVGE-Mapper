#include "mainwindow.hpp"
#include "./ui_mainwindow.h"
#include "udplistener.hpp"

#include "setkeydialog.hpp"

#include <QNetworkInterface>
#include <QDebug>
#include <QKeyEvent>
#include <QEvent>
#include <QPushButton>
#include <QMetaEnum>
#include <QRegExpValidator>
#include <QVariant>

#include "keysender.hpp"

#if not defined(Q_OS_LINUX) and not defined(Q_OS_WIN)
    #define FORCE_REPAINT
#endif

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("MVGE Button Mapper");
    _udpListener = new UDPListener(this);
    _keySender = new KeySender(this);
    _settingsFile = qApp->applicationDirPath() + "/config.ini";
    _settings = new QSettings(_settingsFile, QSettings::IniFormat);
    _setDialog = new SetKeyDialog(this);

    ui->lePort->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), ui->lePort));
    loadSettings();

    connect(ui->btnBind, &QPushButton::clicked, this, &MainWindow::onBindClicked);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(_udpListener, &UDPListener::keyReceived, this, &MainWindow::onKeyReceived);

    ui->statusbar->showMessage("Disconnected: Not listening.");

    ui->tbLog->append("INFO: Disconnected and not listening to any port.");

    QList<QPushButton *> mButtonList = ui->tabButtons->findChildren<QPushButton *>();

    for (const auto *mButton : mButtonList) {
        connect(mButton, &QPushButton::clicked, _setDialog, &SetKeyDialog::onSetClicked);
    }

    connect(_setDialog, &SetKeyDialog::setKey, this, &MainWindow::onKeySet);

    initMap();
}

MainWindow::~MainWindow()
{
    _settings->setValue("nativekeys", _setDialog->accessMap());
    _settings->sync();
    delete ui;
}

void MainWindow::onBindClicked()
{
    _port = static_cast<quint16>(ui->lePort->text().toInt());

    if (_isBinded) {
        _udpListener->unBind();
        _isBinded = false;
        ui->statusbar->showMessage("Disconnected: Not listening.");
        #if defined(FORCE_REPAINT)
        ui->statusbar->repaint();
        #endif
        ui->btnBind->setText("Bind");
        ui->lePort->setDisabled(false);
        return;
    }

    if (_udpListener->bind(QHostAddress::Any, _port)) {
        const QString mMessage = "Connected: Listening on port " + QString::number(_port);
        ui->statusbar->showMessage(mMessage);
        #if defined(FORCE_REPAINT)
        ui->statusbar->repaint();
        #endif
        ui->tbLog->append("INFO: " + mMessage);
        _isBinded = true;
        ui->btnBind->setText("Disconnect");
        ui->lePort->setDisabled(false);
        checkPort();
        _settings->setValue("port", _port);
        _settings->sync();
        ui->tbLog->append(QString("INFO: Port [%1] saved to settings.").arg(QString::number(_port)));
        ui->lePort->setDisabled(true);
    } else {
        const QString mMessage = "Disconnected: Bind on port " + QString::number(_port) + " unsuccessful!";
        ui->statusbar->showMessage(mMessage);
        #if defined(FORCE_REPAINT)
        ui->statusbar->repaint();
        #endif
        ui->tbLog->append("ERROR: " + mMessage);
        _isBinded = false;
        ui->lePort->setDisabled(false);
    }
}

void MainWindow::onClearClicked()
{
    ui->tbLog->clear();
}

void MainWindow::onKeySet(QStringList iStringList)
{
    QString mLabelName = QString("lb").append(iStringList.at(0).mid(3));

    QLabel *mLabel = ui->tabButtons->findChild<QLabel *>(mLabelName);
    mLabel->setText(iStringList.at(1));
    // Save to settings
    _settings->setValue(mLabelName, iStringList.at(1));
    _settings->sync();
    ui->tbLog->append(
        QString("INFO: [%1] Set to [%2] and saved to settings.").arg(mLabelName.mid(2)).arg(iStringList.at(1)));
}

void MainWindow::onKeyReceived(const QString &iKey)
{
    const QStringList mKey = iKey.split(':');
    // Validate external input. Example received key: "Key_Down:1"
    if (mKey.size() < 2) {
        return;
    }

    const QString mLabelName = _mappedKeys.value(mKey.at(0));
    const QLabel *mLabel = ui->tabButtons->findChild<QLabel *>(mLabelName);

    const int mKeyValue = QMetaEnum::fromType<Qt::Key>().keyToValue(mLabel->text().toStdString().c_str());

    if (mKeyValue != -1) _keySender->sendKeyPress(_setDialog->keyToNative(Qt::Key(mKeyValue)), mKey.at(1).trimmed());

}

void MainWindow::loadSettings()
{
    foreach (QString mSettingKey, _settings->allKeys()) {

        const QString mText = _settings->value(mSettingKey, "").toString();
        if (mText != "") {
            // Check if its a valid value.
            const int mKeyValue = QMetaEnum::fromType<Qt::Key>().keyToValue(mText.toStdString().c_str());
            if (mKeyValue != -1) {
                ui->tbLog->append(
                    QString("INFO: [%1] Initialized to [%2] from settings.").arg(mSettingKey.mid(2)).arg(mText));
                ui->tabButtons->findChild<QLabel *>(mSettingKey)->setText(mText);
            }
        }
    }

    const QString mText = _settings->value("port", "").toString();
    if (mText != "") {
        ui->lePort->setText(mText);
        ui->tbLog->append(QString("INFO: Port initialized to [%1] from settings.").arg(ui->lePort->text()));
    }

    const QMap<QString, QVariant> mMap = _settings->value("nativekeys", "").toMap();
    if (!mMap.isEmpty()) _setDialog->accessMap() = mMap;
}
void MainWindow::initMap()
{

    _mappedKeys["Key_U"] = "lbX";
    _mappedKeys["Key_I"] = "lbY";
    _mappedKeys["Key_J"] = "lbA";
    _mappedKeys["Key_K"] = "lbB";
    _mappedKeys["Key_Y"] = "lbAltX";
    _mappedKeys["Key_O"] = "lbAltY";
    _mappedKeys["Key_H"] = "lbAltA";
    _mappedKeys["Key_L"] = "lbAltB";

    _mappedKeys["Key_Space"] = "lbSelect";
    _mappedKeys["Key_Return"] = "lbStart";
    _mappedKeys["Key_Minus"] = "lbAltSelect";
    _mappedKeys["Key_Plus"] = "lbAltStart";

    _mappedKeys["Key_Escape"] = "lbMenu";

    _mappedKeys["Key_Up"] = "lbUp";
    _mappedKeys["Key_Down"] = "lbDown";
    _mappedKeys["Key_Left"] = "lbLeft";
    _mappedKeys["Key_Right"] = "lbRight";

    _mappedKeys["Key_Home"] = "lbLK1";
    _mappedKeys["Key_PageUp"] = "lbLK2";
    _mappedKeys["Key_PageDown"] = "lbLK4";
    _mappedKeys["Key_End"] = "lbLK5";
}

void MainWindow::checkPort()
{
    // cat /proc/sys/net/ipv4/ip_local_port_range 32768   60999
    if (_port >= quint16(32768) and _port <= quint16(60999)) {
        ui->tbLog->append("WARNING: Using ephemeral ports (32768 - 60999 may lead to random issues.");
    } else if (_port >= quint16(1) and _port <= quint16(1023)) {
        ui->tbLog->append("WARNING: Using reserved ports (1 - 1024) may lead to random issues.");
    } else if (_port == 0) {
        ui->tbLog->append(
            "ERROR: Using reserved port 0 is unavailable. Maybe you tried to use a port higher than (2^16)-1 ? ");
        ui->tbLog->append("       Falling back to port 3000!");
        _port = 3000;
    }
}
