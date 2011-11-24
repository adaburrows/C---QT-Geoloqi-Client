#ifndef APITESTBUTTONS_H
#define APITESTBUTTONS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class ApiTestButtons : public QWidget
{
    Q_OBJECT
public:
    explicit ApiTestButtons(QWidget *parent = 0);
    QVBoxLayout *buttonLayout;
    //QPushButton *getAuthTokenButton;
    QPushButton *getUsernameButton;
    QPushButton *getProfileButton;
    QPushButton *getLastLocationButton;
    QPushButton *getHistoryButton;
    QPushButton *getPlacesButton;
signals:

public slots:

};

#endif // APITESTBUTTONS_H
