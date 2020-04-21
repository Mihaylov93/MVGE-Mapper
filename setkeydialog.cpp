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

quint32 SetKeyDialog::keyToNative(const Qt::Key& iKey)
{
    return _qtKeysToNativeMap.value(QString::number(iKey)).toUInt();
}

QMap<QString, QVariant>& SetKeyDialog::accessMap()
{
    return _qtKeysToNativeMap;
}

void SetKeyDialog::onSetClicked()
{
    _btnObjName = sender()->objectName();
    this->show();
}

void SetKeyDialog::keyReleaseEvent(QKeyEvent* iKeyEvent)
{
    const QString mKey(QMetaEnum::fromType<Qt::Key>().valueToKey(iKeyEvent->key()));
    QStringList mStringList;
    mStringList << _btnObjName << mKey;

    qDebug() << mStringList;
    qDebug() << iKeyEvent->key();
#if defined(Q_OS_LINUX)
    qDebug() << "nativeScanCode: " << iKeyEvent->nativeScanCode();
    const quint32 mNativeKey = iKeyEvent->nativeScanCode();
#endif
#if defined(Q_OS_WIN)
    qDebug() << "nativeVirtual: " << iKeyEvent->nativeVirtualKey();
    const quint32 mNativeKey = iKeyEvent->nativeVirtualKey();
#endif

    _qtKeysToNativeMap.insert(QString::number(Qt::Key(iKeyEvent->key())), mNativeKey);
    emit setKey(mStringList);
    this->hide();
}
