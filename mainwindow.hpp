#pragma once

#include <QMainWindow>
#include <QMap>
class QHostAddress;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

//#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <winuser.h>

class UDPListener;
class KeySender;
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onBindClicked();

private:
    Ui::MainWindow *ui;
    UDPListener *_udpListener;
    KeySender *_keySender;
    quint16 _port = 3000;
    bool _isBinded = false;
    QMap<QString, QHostAddress> _ifacesMap;
    void initInterfaces();
};
