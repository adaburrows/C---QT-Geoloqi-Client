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
    loqi->setToken(permanent_token);
    outPut = new QTextEdit();
    //outPut->
    setCentralWidget(outPut);
    testButtons = new ApiTestButtons();
    testButtonDock = new QDockWidget(tr("test buttons"));
    testButtonDock->setWidget(testButtons);
    testButtonDock->setAllowedAreas(Qt::LeftDockWidgetArea
                                    | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea,testButtonDock);

    connect(testButtons->getUsernameButton, SIGNAL(clicked()), this, SLOT(onGetUsername()));

}

LoqiWindow::~LoqiWindow()
{
    delete authdialog;
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
    doStuff();
}
void LoqiWindow::showAuthDialog()
{
    authdialog->show();
}

void LoqiWindow::doStuff()
{
    loqi->setToken(QString(permanent_token));
/*
    loqi->getAuthToken(QString("jburrows"),QString("hehe"));
    loqi->getProfile();
    loqi->getLastLocation();
    loqi->getHistory();
*/
}

void LoqiWindow::onGetUsername() {
    QGeoloqiReply* reply = loqi->getUsername();
    connect(reply, SIGNAL(dataReady(QVariant, QGeoloqiReply*)), this, SLOT(appendText(QVariant,QGeoloqiReply*)));
}

void LoqiWindow::appendText(QVariant text, QGeoloqiReply* reply) {
    outPut->append(QString(loqi->encodeJson(text)));
    //reply->deleteLater();
}
