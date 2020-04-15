#include "setkeydialog.hpp"
#include <QtDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QSizePolicy>
#include <QKeyEvent>
#include <QMetaEnum>
SetKeyDialog::SetKeyDialog(QWidget* parent) : QDialog(parent)
{
    this->setModal(true);
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    this->setWindowTitle("Set key");
    QVBoxLayout* mHLayout = new QVBoxLayout(this);
    QLabel* mLabel = new QLabel(this);
    QSizePolicy mPolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    mLabel->setSizePolicy(mPolicy);
    mLabel->show();
    mLabel->setText("Press key to set or cancel by [X]");
    mHLayout->addWidget(mLabel);

    this->setLayout(mHLayout);
}

void SetKeyDialog::onSetClicked()
{
    _btnObjName = sender()->objectName();
    // QPushButton* button = qobject_cast<QPushButton*>(sender());
    // qDebug() << button;
    this->show();
}

void SetKeyDialog::keyReleaseEvent(QKeyEvent* iKeyEvent)
{
    // qDebug() << iKeyEvent->key();
    const QString mKey(QMetaEnum::fromType<Qt::Key>().valueToKey(iKeyEvent->key()));
    QStringList mStringList;
    mStringList << _btnObjName << mKey;

    qDebug() << mStringList;
    emit setKey(mStringList);
    this->hide();
}
