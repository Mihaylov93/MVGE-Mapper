#pragma once

#include <QDialog>

class SetKeyDialog : public QDialog {
    Q_OBJECT
public:
    explicit SetKeyDialog(QWidget *parent = nullptr);
signals:
    void setKey(QStringList);
public slots:
    void onSetClicked();
    void keyReleaseEvent(QKeyEvent *);

private:
    QString _btnObjName;
};
