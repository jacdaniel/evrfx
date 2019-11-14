#ifndef ENDOVEINOUS_H
#define ENDOVEINOUS_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLCDNumber>
#include <QProgressBar>
#include <QGroupBox>
#include <QString>

#include <QMainWindow>
#include "include/protocol.h"
#include "include/quickuserinfo.h"

#include "include/care.h"
#include <./include/param.h>
#include "include/rfidreader.h"
#include <./include/dataio.h>

/*
class ADDRESS
{
    QString no, zip, address, address2, town, country;
};

class PATIENT0
{
    int gender, age;
    QString name, firstname, ceap;
    ADDRESS address;
    QString remark;
};
*/


#define DELAY_BEEP_2S         80
#define DELAY_BEEP_END_CYCLE 400
#define DELAY_BEEP_500J      400
#define DELAY_BEEP_1500J     600

#define NEXT_BEEP_0J    0
#define NEXT_BEEP_500J  1
#define NEXT_BEEP_1000J 2
#define NEXT_BEEP_1500J 3


namespace Ui {

class Endoveinous;
}

class Endoveinous : public QMainWindow
{
    Q_OBJECT

public:
    explicit Endoveinous(QWidget *parent = nullptr);
    explicit Endoveinous(QWidget *parent, int type, int treatment, Param *param, dataio *dio, int id);
    ~Endoveinous();
    void set_patient_dir(QString *dir);

private:
    Ui::Endoveinous *ui;
    RFIDReader *rfidreader;
    QLCDNumber *lcdclock;
    QLCDNumber *lcdenergy, *lcdpedal;
    QProgressBar *pbpower;
    QPushButton *bmanual, *bpreset, *veindiameter_inc, *veindiameter_dec, *power_inc, *power_dec, *bonoff, *bquit,
    *buserinfo, *bprotocol, *bquikuserguide, *bpulsewidth_inc, *bpulsewidth_dec, *bdelay_inc, *bdelay_dec,
    *bface, *bleg;
    QTimer *timer;
    // QPixmap *pixchecked, *pixunchecked;
    QIcon *ichecked, *iunchecked;
    QLabel *lab, *lveindiameter, *lpower, *lpowertile, *lpadstatus, *lcatheterstatus, *lmanual, *lpreset, *lveindiametertitle,
    *lenergy, *ltimer, *ltitle, *lenergy0,
    *lpulsewidth_title, *lpulsewidth, *ldelay_title, *ldelay, *lface, *lleg, *lpedal, *lprogressbartitle,
    *llogopulse, *llogoclock, *llogoenergy;

    QGroupBox *gbmanual_preset, *gbvein_diameter, *gbpower, *gbprogressbar, *gbhelpmenu, *gbfacelegs, *gbpulsewidth, *gbdelay, *qgbdedal;

    int veindiameter, onoff, pad_status, catheter_status, treatment,
        face_legs, treatment_type, cycle_count, progress, total_time0, cycle_time, cycle_cpt;
    QString *patient_dir;
    Protocol *protocol;
    QuickUserInfo *quickuserguide;
    QFont *font_timer, *font_energy, *font_title;
    Param *param;
    dataio *dio;
    QPixmap *pix_catheter_disconnected, *pix_catheter_connected, *pix_pad_disconnected, *pix_pad_connected;

    // PATIENT0 *patient;
    // QString directory;
    int id;
    void *userinfo;

    void raz_variables();
    void init();
    void init_timer();
    void init_title(QFont *font);
    void init_catheter_status(int x0, int y0, int width, int height);
    void init_pad_status(int x0, int y0, int width, int height);
    void init_timer0(int x0, int y0, QFont *font, QWidget *parent);
    void init_energy(int x0, int y0, QFont *font);
    void init_power(int x0, int y0, QFont font);
    void init_onoff(int x0, int y0);
    void init_vein_diameter(int x0, int y0, QFont *font);
    void init_manual_preset(int x0, int y0, QFont *font);
    void init_progressbar(int x0, int y0, QString lab, QFont *font);
    void init_facelegs(int x0, int y0, QFont *font);
    void init_pulsewidth(int x0, int y0, QFont *font);
    void init_delay(int x0, int y0, QFont *font);
    void init_pedalcounter(int x0, int y0, QFont *font);


    void set_title(QString title);
    void set_manual_preset(int val);



    void init_endovenous();
    void init_transcutaneous();
    void init_proctology();

    void helpmenu_init(int x0, int y0);

    void manual_preset_display(int val);

    void veindiameter_display(int val);
    void power_display(int val);
    void onoff_display(int val);
    void catheterstatus_display(int val);
    void padstatus_display(int val);
    void pulsewidth_display(int val);
    void delay_display(int val);
    void setFace_Legs(int val);
    void set_protocole_type(int val);
    void catheter_status_enable(int val);
    void cycle_count_display(int val);

    void master_database_fill(void *_data);
    void master_database_write();
    void user_database_fill(void *_data);
    void user_database_write();



    void init_lcdpower_proctology(int x0, int y0);


    void *patient;

    Care *care;
    Care *care_init(int type, int treatment);
    Care *care_release(Care *care);
    void transcutaneous_faceleg_param_ini(Care *care, int type);

    // pseudo hardware communication
    // void init_gpio();

    // int gpio_get_pedal();
    // int gpio_set_power(int val);
    // int gpio_get_pad_status();
   //  int gpio_get_catheter_status();
    // int gpio_set_hf(int val);

    QPushButton *debug_pedal_on, *debug_pad_on, *debug_cath_on;//, *debug_pedal_off;
    QLabel *ltimer0;
    int debug_pedal, debug_pad, debug_cath, next_beep;



    double energy0;

    void time_display(int time_ms);
    void power_progressbar_display(int power);
    void energy_display(double energy);



    void timer_cr45i();
    void timer_cr40i();
    void timer_cr30i();
    void timer_transcutaneous();
    void timer_hpr45i();
    void timer_fistula();

    void ht_program(int type, int val);
    int pedal_read();
    int catheter_read();
    int pad_read();
    void valid_hf(int val);
    void set_buzzer(int val, int boost);
    void set_buzzer_delay(int boost, int d);


    // void read_user_info(PATIENT0 *p);
    // void test0();



private slots:
        void showTime();
        void handle_Trt_Manual();
        void handle_Trt_Preset();
        void handle_Trt_VeinDiameterDec();
        void handle_Trt_VeinDiameterInc();
        void handle_Trt_PowerDec();
        void handle_Trt_PowerInc();
        void handle_Trt_OnOFF();
        void handle_Trt_Exit();
        void handle_Trt_Face();
        void handle_Trt_Leg();
        void handle_Trt_PulseWidthDec();
        void handle_Trt_PulseWidthInc();
        void handle_Trt_DelayDec();
        void handle_Trt_DelayInc();
        void handle_Trt_QuickUserInfo();
        void handle_Trt_Protocol();
        void handle_Trt_UserInfo();

        void trt_debug_pedal_on();
        void trt_debug_pad_on();
        void trt_debug_cath_on();
        // void trt_debug_pedal_off();

};

#endif // ENDOVEINOUS_H
