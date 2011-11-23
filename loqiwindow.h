#ifndef LOQIWINDOW_H
#define LOQIWINDOW_H

#include <QtGui/QMainWindow>
#include <QSettings>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QString>
#include "authdialog.h"
#include "qgeoloqi.h"

class LoqiWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoqiWindow(QWidget *parent = 0);
    ~LoqiWindow();
    void readSettings();
    void writeSettings();
    void doStuff();
    AuthDialog *authdialog;
    QSettings *settings;
    QMenu *editMenu;
    QAction *editAuthKey;
    QString permanent_token;

public slots:
    void authSave();
    void showAuthDialog();

private:
    QGeoloqi* loqi;
};

#endif // LOQIWINDOW_H
