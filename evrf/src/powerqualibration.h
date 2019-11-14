#ifndef POWERQUALIBRATION_H
#define POWERQUALIBRATION_H

#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <dataio.h>
#include <QMainWindow>

namespace Ui {
class PowerQualibration;
}

class PowerQualibration : public QMainWindow
{
    Q_OBJECT

public:
    explicit PowerQualibration(QWidget *parent, dataio *dio);
    ~PowerQualibration();

private:
    Ui::PowerQualibration *ui;

    dataio *dio;
    QPushButton *bpowerinc, *bpowerdec, *bCancel, *bonoff, *breadtype_inc, *breadtype_dec;
    QLabel *lpower, *lpowerread, *lreadtype;
    int idx_power, startstop, read_type;

    void display();
    void read_type_display(int type);
    void catheter_status_enable(int val);
    void ht_program(int type, int val);
    int get_adc(int type);


    QTimer *timer;

private slots:
    void handle_Trt_PowerInc();
    void handle_Trt_powerDec();
    void handle_Trt_BCancel();
    void showTime();
    void handle_Trt_OnOFF();
    void handle_Trt_readtypeDec();
    void handle_Trt_readtypeInc();


};

#endif // POWERQUALIBRATION_H
