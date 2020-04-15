#include "mainwindow.hpp"
#include "./ui_mainwindow.h"
#include "udplistener.hpp"
#include "keysender.hpp"

#include "setkeydialog.hpp"

#include <QNetworkInterface>
#include <QDebug>
#include <QKeyEvent>
#include <QEvent>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _udpListener = new UDPListener(this);
    _keySender = new KeySender(this);

    connect(ui->btnBind, &QPushButton::clicked, this, &MainWindow::onBindClicked);
    connect(_udpListener, &UDPListener::keyReceived, _keySender, &KeySender::sendKeyPress);

    ui->statusbar->showMessage("Disconnected: Not listening.");

    SetKeyDialog* kd = new SetKeyDialog(this);
}

MainWindow::~MainWindow()
{
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
