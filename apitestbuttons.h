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
    QPushButton *getAuthTokenButton;
    QPushButton *setClientIdButton;
    QPushButton *setClientSecretButton;
    QPushButton *getTokenButton;
    QPushButton *setTokenButton;;
    QPushButton *getUsernameButton;
    QPushButton *getProfileButton;
    QPushButton *getLastLocationButton;
    QPushButton *getHistoryButton;
signals:

public slots:

};

#endif // APITESTBUTTONS_H
