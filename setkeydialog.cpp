#include "setkeydialog.hpp"

SetKeyDialog::SetKeyDialog(QWidget *parent) : QDialog(parent)
{
    this->setModal(true);
    this->show();
}
