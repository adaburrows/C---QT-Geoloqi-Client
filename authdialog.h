#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

class AuthDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AuthDialog(QWidget *parent = 0);
    QLabel *authLabel;
    QLineEdit *authEdit;
    QHBoxLayout *editLayout;
    QVBoxLayout *dialogLayout;
    QPushButton *saveSettingsButton;
signals:

public slots:

};

#endif // AUTHDIALOG_H
