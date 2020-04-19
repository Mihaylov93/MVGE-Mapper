#pragma once

#include <QDialog>
#include <QMap>
class SetKeyDialog : public QDialog {
    Q_OBJECT
public:
    explicit SetKeyDialog(QWidget *parent = nullptr);
    quint32 keyToNative(const Qt::Key &iKey);
    QMap<QString, QVariant> &accessMap();
signals:
    void setKey(QStringList);
public slots:
    void onSetClicked();
    void keyReleaseEvent(QKeyEvent *);

private:
    QString _btnObjName;
    // QMap<Qt::Key, QVariant> _qtKeysToNativeMap;
    QMap<QString, QVariant> _qtKeysToNativeMap;
};
