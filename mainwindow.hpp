#pragma once

#include <QMainWindow>
#include <QSettings>
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
class SetKeyDialog;
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onBindClicked();
    void onKeySet(QStringList iStringList);

private:
    Ui::MainWindow *ui;
    UDPListener *_udpListener;
    KeySender *_keySender;
    quint16 _port = 3000;
    bool _isBinded = false;
    QMap<QString, QHostAddress> _ifacesMap;
    QString _settingsFile;
    SetKeyDialog *_setDialog = nullptr;
    QSettings *_settings;
    void initInterfaces();
    void loadSettings();
    void saveSettings();
    void aboutQt();
};
