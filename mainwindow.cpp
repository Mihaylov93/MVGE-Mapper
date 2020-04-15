#include "mainwindow.hpp"
#include "./ui_mainwindow.h"
#include "udplistener.hpp"
#include "keysender.hpp"

#include "setkeydialog.hpp"

#include <QNetworkInterface>
#include <QDebug>
#include <QKeyEvent>
#include <QEvent>
#include <QPushButton>

#include <QDir>
#include <QMetaEnum>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _udpListener = new UDPListener(this);
    _keySender = new KeySender(this);

    _settingsFile = QDir::currentPath() + "/config.ini";
    _settings = new QSettings(_settingsFile, QSettings::IniFormat);

    loadSettings();

    connect(ui->btnBind, &QPushButton::clicked, this, &MainWindow::onBindClicked);
    connect(_udpListener, &UDPListener::keyReceived, _keySender, &KeySender::sendKeyPress);

    ui->statusbar->showMessage("Disconnected: Not listening.");

    _setDialog = new SetKeyDialog(this);

    QList<QPushButton *> mButtonList = ui->tabButtons->findChildren<QPushButton *>();
    qDebug() << mButtonList.size();

    for (const auto *mButton : mButtonList) {

        qDebug() << "   " << mButton->objectName();
        connect(mButton, &QPushButton::clicked, _setDialog, &SetKeyDialog::onSetClicked);
    }

    connect(_setDialog, &SetKeyDialog::setKey, this, &MainWindow::onKeySet);
    aboutQt();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::onBindClicked()
{
    if (_isBinded) {
        _udpListener->unBind();
        _isBinded = false;
        ui->statusbar->showMessage("Disconnected: Not listening.");
        return;
    }

    if (_udpListener->bind(QHostAddress::Any, _port)) {
        ui->statusbar->showMessage("Connected: Listening on port " + QString::number(_port));
        _isBinded = true;
        ui->btnBind->setText("Disconnect");
    } else {
        ui->statusbar->showMessage("Disconnected: Bind on port " + QString::number(_port) + " unsuccessful!");
        _isBinded = false;
    }
}

void MainWindow::onKeySet(QStringList iStringList)
{
    QString mLabelName = QString("lb").append(iStringList.at(0).mid(3));

    QLabel *mLabel = ui->tabButtons->findChild<QLabel *>(mLabelName);
    mLabel->setText(iStringList.at(1));
    // Save to settings
    _settings->setValue(mLabelName, iStringList.at(1));
    _settings->sync();
}

void MainWindow::loadSettings()
{
    foreach (QString mSettingKey, _settings->allKeys()) {

        const QString mText = _settings->value(mSettingKey, "").toString();
        if (mText != "") {
            // Check if its a valid value.
            const int mKeyValue = QMetaEnum::fromType<Qt::Key>().keyToValue(mText.toStdString().c_str());
            if (mKeyValue != -1) ui->tabButtons->findChild<QLabel *>(mSettingKey)->setText(mText);
        }
    }
}

void MainWindow::saveSettings()
{

    // qDebug() << _settingsFile;
    //_settings.setValue("oooo", "AAAAA");
    //_settings.sync();
}

void MainWindow::aboutQt()
{
    // Taken from src/widgets/dialogs/qmessagebox.cpp

    //: Leave this text untranslated or include a verbatim copy of it below
    //: and note that it is the authoritative version in case of doubt.
    const QString translatedTextAboutQtText
        = tr("<p>Qt is a C++ toolkit for cross-platform application "
             "development.</p>"
             "<p>Qt provides single-source portability across all major desktop "
             "operating systems. It is also available for embedded Linux and other "
             "embedded and mobile operating systems.</p>"
             "<p>Qt is available under multiple licensing options designed "
             "to accommodate the needs of our various users.</p>"
             "<p>Qt licensed under our commercial license agreement is appropriate "
             "for development of proprietary/commercial software where you do not "
             "want to share any source code with third parties or otherwise cannot "
             "comply with the terms of GNU (L)GPL.</p>"
             "<p>Qt licensed under GNU (L)GPL is appropriate for the "
             "development of Qt&nbsp;applications provided you can comply with the terms "
             "and conditions of the respective licenses.</p>"
             "<p>Please see <a href=\"http://%2/\">%2</a> "
             "for an overview of Qt licensing.</p>"
             "<p>Copyright (C) %1 The Qt Company Ltd and other "
             "contributors.</p>"
             "<p>Qt and the Qt logo are trademarks of The Qt Company Ltd.</p>"
             "<p>Qt is The Qt Company Ltd product developed as an open source "
             "project. See <a href=\"http://%3/\">%3</a> for more information.</p>")
              .arg(QStringLiteral("2020"), QStringLiteral("qt.io/licensing"), QStringLiteral("qt.io"));
    ui->tbAbout->setText(translatedTextAboutQtText);
}
