#include "apitestbuttons.h"

ApiTestButtons::ApiTestButtons(QWidget *parent) :
    QWidget(parent)
{
    buttonLayout = new QVBoxLayout;
    //getAuthTokenButton = new QPushButton(tr("getAuthToken"));
    getUsernameButton = new QPushButton(tr("getUsername"));
    getProfileButton = new QPushButton(tr("getProfile"));
    getLastLocationButton = new QPushButton(tr("getLastLocation"));
    getHistoryButton = new QPushButton(tr("getHistory"));
    getPlacesButton = new QPushButton(tr("getPlaces"));
    //buttonLayout->addWidget(getAuthTokenButton);
    buttonLayout->addWidget(getUsernameButton);
    buttonLayout->addWidget(getProfileButton);
    buttonLayout->addWidget(getLastLocationButton);
    buttonLayout->addWidget(getHistoryButton);
    buttonLayout->addWidget(getPlacesButton);
    setLayout(buttonLayout);
}
