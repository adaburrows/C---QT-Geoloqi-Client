#include "apitestbuttons.h"

ApiTestButtons::ApiTestButtons(QWidget *parent) :
    QWidget(parent)
{
    buttonLayout = new QVBoxLayout;
    getAuthTokenButton = new QPushButton(tr("getAuthToken"));
    setClientIdButton = new QPushButton(tr("setClientId"));
    setClientSecretButton = new QPushButton(tr("setClientSecret"));
    getTokenButton = new QPushButton(tr("getToken"));
    setTokenButton = new QPushButton(tr("setToken"));
    getUsernameButton = new QPushButton(tr("getUsername"));
    getProfileButton = new QPushButton(tr("setToken"));
    getLastLocationButton = new QPushButton(tr("getLastLocation"));
    getHistoryButton = new QPushButton(tr("getHistory"));
    buttonLayout->addWidget(getAuthTokenButton);
    buttonLayout->addWidget(setClientIdButton);
    buttonLayout->addWidget(setClientSecretButton);
    buttonLayout->addWidget(getTokenButton);
    buttonLayout->addWidget(setTokenButton);
    buttonLayout->addWidget(getUsernameButton);
    buttonLayout->addWidget(getProfileButton);
    buttonLayout->addWidget(getLastLocationButton);
    buttonLayout->addWidget(getHistoryButton);
    setLayout(buttonLayout);
}
