#ifndef LOQIWINDOW_H
#define LOQIWINDOW_H

#include <QtGui/QMainWindow>

class LoqiWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoqiWindow(QWidget *parent = 0);
    ~LoqiWindow();
};

#endif // LOQIWINDOW_H
