#include "authdialog.h"

AuthDialog::AuthDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle("Configure Auth Key");
    authLabel = new QLabel("perm auth key goes here");
    authEdit = new QLineEdit;
    editLayout = new QHBoxLayout;
    editLayout->addWidget(authLabel);
    editLayout->addWidget(authEdit);
    saveSettingsButton = new QPushButton("save");
    dialogLayout = new QVBoxLayout;
    dialogLayout->addLayout(editLayout);
    dialogLayout->addWidget(saveSettingsButton);
    setLayout(dialogLayout);
}

