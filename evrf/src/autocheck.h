#ifndef AUTOCHECK_H
#define AUTOCHECK_H

#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QProgressBar>

namespace Ui {
class autocheck;
}

class autocheck : public QDialog
{
    Q_OBJECT

public:
    explicit autocheck(QWidget *parent = 0);
    ~autocheck();



private:
    Ui::autocheck *ui;
    QTimer *timer;
    QLabel *ltitle;
    QProgressBar *pbar;
    int idx_power;
    int cpt;

    int power_read(int idx);
    void power_write(int idx);


private slots:
    void showTime();

};

#endif // AUTOCHECK_H
