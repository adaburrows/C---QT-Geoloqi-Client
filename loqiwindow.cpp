#include "loqiwindow.h"

LoqiWindow::LoqiWindow(QWidget *parent)
    : QMainWindow(parent)
{
    settings = new QSettings("ModernTwinPowers", "geoeater");
    authdialog = new AuthDialog();
    connect(authdialog->saveSettingsButton,SIGNAL(clicked()),this,SLOT(authSave()));
    readSettings();
    editMenu = menuBar()->addMenu("Edit");
    editAuthKey = new QAction(tr("Edit Auth Key"),this);
    connect(editAuthKey,SIGNAL(triggered()),this,SLOT(showAuthDialog()));
    editMenu->addAction(editAuthKey);
    loqi = new QGeoloqi();
}

LoqiWindow::~LoqiWindow()
{

}

void LoqiWindow::readSettings()
{
    if(!settings->contains("authkey")){
        authdialog->show();
    }
    else
    {
        permanent_token = settings->value("authkey").toString();
        authdialog->authEdit->setText(permanent_token);
    }
}

void LoqiWindow::writeSettings()
{

}

void LoqiWindow::authSave()
{
    permanent_token = authdialog->authEdit->text();
    settings->setValue("authkey",permanent_token);
    authdialog->hide();
}
void LoqiWindow::showAuthDialog()
{
    authdialog->show();
}

void LoqiWindow::doStuff()
{
    loqi->getAuthToken(QString("jburrows"),QString("hehe"));
    loqi->setToken(QString(permanent_token));
    loqi->getUsername();
    loqi->getProfile();
    loqi->getLastLocation();
    loqi->getHistory();
}
