#include <math.h>
#include <stdio.h>
#include <malloc.h>

// #include <QtWidgets>
#include <QTimer>
#include <QFile>
#include <QDate>
#include <QTime>
// #include <QMediaPlayer>

#include "include/config.h"
#include "include/util.h"
#include "include/endoveinous.h"
#include "include/patientlist.h"
#include "./include/database.h"
#include "./include/patient.h"
#include "ui_endoveinous.h"


#define FONT_TIMER "Helvetica", 20, QFont::Bold
#define STYLE_SHEET_TIMER "QLabel { background-color : none; color : #7F0000; }"

#define FONT_ENERGY "Helvetica", 20, QFont::Bold
#define STYLE_SHEET_ENERGY "QLabel { background-color : none; color : #00007F; }"

#define FONT_TITLE "Helvetica", 22, QFont::Bold
#define STYLE_SHEET_TITLE "QLabel { background-color : none; color : #00007F; }"


Endoveinous::Endoveinous(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Endoveinous)
{
    ui->setupUi(this);

    setGeometry(QRect(QPoint(0, 0), QSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)));
//     QFont *font = new QFont(TITLE_LABEL_FONT_NAME, TITLE_LABEL_FONT_SIZE-10, TITLE_LABEL_FONT_WEIGHT);
    QRegion region( QRect( 0, 0, 68, 68 ), QRegion:: Ellipse ); // Création d'une ellipse de 50px de diamètre

    QPixmap *pix = new QPixmap(MAIN_SCREEN_IMAGE2);
    lab = new QLabel(this);
    lab->setGeometry(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    lab->setPixmap(*pix);
}

Endoveinous::Endoveinous(QWidget *parent, int type, int treatment, Param *param, dataio *dio, int id) :
    QMainWindow(parent),
    ui(new Ui::Endoveinous)
{
    ui->setupUi(this);
    this->param = param;
    // this->dio = new dataio();
    this->dio = dio;
    this->id = id;

    setGeometry(QRect(QPoint(0, 0), QSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)));
    // QFont *font = new QFont(TITLE_LABEL_FONT_NAME, TITLE_LABEL_FONT_SIZE-10, TITLE_LABEL_FONT_WEIGHT);
    // QRegion region( QRect( 0, 0, 68, 68 ), QRegion:: Ellipse ); // Création d'une ellipse de 50px de diamètre

    QPixmap *pix = new QPixmap(MAIN_SCREEN_IMAGE2);
    QLabel *lab = new QLabel(this);
    lab->setGeometry(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    lab->setPixmap(*pix);

    raz_variables();

    font_timer = new QFont(FONT_TIMER);
    font_energy = new QFont(FONT_ENERGY);
    font_title = new QFont(FONT_TITLE);

    this->treatment_type = type;
    this->treatment = treatment;
    this->care = care_init(type, treatment);

    init_title(font_title);
    // set_title(ARRAY_MAINTITLE[this->treatment_type][this->treatment]);
    set_title((QString)care->protocol_name);


    /*
    lcatheterstatus = new QLabel(this);
    lcatheterstatus->setGeometry(230, 400, 64, 64);
    lpadstatus = new QLabel(this);
    lpadstatus->setGeometry(550, 400, 64, 64);
    */

    init_catheter_status(230, 400, 64, 64);
    init_pad_status(550, 400, 64, 64);

    BUTTONIMAGE_CREATE(bquit, CANCEL_IMAGE, 720, 400, 75, 75, handle_Trt_Exit())

    timer = new QTimer(this);
    timer->start(100);
//    connect(timer, &QTimer::timeout, this, &Endoveinous::showTime);
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));

//    manual_preset = 0;
//    power = array_init_power[this->treatment];
    veindiameter = 1;
    onoff = 0;
    catheter_status = 0;
    pad_status = 1;
    face_legs = 0;
    cycle_count = 0;
    progress = 0;
    cycle_cpt = 0;
    // init_gpio();
    init();

    this->patient = calloc(1, sizeof(PATIENT));

//    char filename[1000];
    // userinfo_get_filename(param->get_base_directory(), 0, filename);
    // this->userinfo = user_info_init(filename);

//     QMediaPlayer *player = new QMediaPlayer(this);
//    // ...
//    player->setMedia(QUrl::fromLocalFile("/home/linux/jack/fc/build-evrf-Desktop-Debug/data/beep.mp3"));
//    player->setVolume(50);
//    player->play();

#ifndef _GPIO_
    debug_pad = debug_cath = 0;

    debug_pad_on = new QPushButton(this);
    debug_pad_on->setGeometry(625, 0, 75, 50);
    debug_pad_on->setText("pad off");
    debug_pad_on->setVisible(true);
    connect(debug_pad_on, SIGNAL (released()), this, SLOT (trt_debug_pad_on()));

    debug_cath_on = new QPushButton(this);
    debug_cath_on->setGeometry(550, 0, 75, 50);
    debug_cath_on->setText("cath off");
    debug_cath_on->setVisible(true);
    connect(debug_cath_on, SIGNAL (released()), this, SLOT (trt_debug_cath_on()));
#endif

#if !defined(_GPIO_) || ( defined(_GPIO_) && ( _GPIO_PEDAL_ == 0 ) )
    debug_pedal = 0;
    debug_pedal_on = new QPushButton(this);
    debug_pedal_on->setGeometry(700, 0, 75, 50);
    debug_pedal_on->setText("pedal off");
    debug_pedal_on->setVisible(true);
    connect(debug_pedal_on, SIGNAL (released()), this, SLOT (trt_debug_pedal_on()));
#endif




    /*
    debug_pedal_off = new QPushButton(this);
    debug_pedal_off->setGeometry(0, 370, 75, 50);
    debug_pedal_off->setText("pedal off");
    debug_pedal_off->setVisible(true);
    connect(debug_pedal_off, SIGNAL (released()), this, SLOT (trt_debug_pedal_off()));
*/

    // test0();

    // std::vector<QString> a = patient_get_directory_list(param->get_base_directory());
}

Endoveinous::~Endoveinous()
{
//    delete lcdclock;
//    delete timer;
    delete ui;
}

void Endoveinous::raz_variables()
{
    bmanual = NULL_PTR;
    bpreset = NULL_PTR;
    veindiameter_inc = NULL_PTR;
    veindiameter_dec = NULL_PTR;
    power_inc = NULL_PTR;
    power_dec = NULL_PTR;
    bonoff = NULL_PTR;
    ichecked = NULL_PTR;
    iunchecked = NULL_PTR;
    lveindiameter = NULL_PTR;
    lpower = NULL_PTR;
    lcatheterstatus = NULL_PTR;
    lmanual = NULL_PTR;
    lpreset = NULL_PTR;
    bdelay_dec = NULL_PTR;
    bdelay_inc = NULL_PTR;
    bpulsewidth_inc = NULL_PTR;
    bpulsewidth_dec = NULL_PTR;
    ldelay = NULL_PTR;
    lpulsewidth = NULL_PTR;
    gbvein_diameter = NULL_PTR;
    lenergy0= NULL_PTR;
    pbpower = NULL_PTR;
    ltimer0 = NULL_PTR;
    lcdclock = NULL_PTR;
    llogoclock = NULL_PTR;
    llogoenergy = NULL_PTR;
    font_timer = NULL_PTR;
    font_energy = NULL_PTR;
    font_title = NULL_PTR;
    pix_catheter_disconnected = NULL_PTR;
    pix_catheter_connected = NULL_PTR;
    pix_pad_disconnected = NULL_PTR;
    pix_pad_connected = NULL_PTR;
    // patient = NULL_PTR;
    lcdpedal = NULL_PTR;
}


// INIT

void Endoveinous::init_timer()
{
    timer = new QTimer(this);
    timer->start(100);
//    connect(timer, &QTimer::timeout, this, &Endoveinous::showTime);
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
}

// Title
void Endoveinous::init_title(QFont *font)
{
    ltitle = new QLabel(this);
    ltitle->setGeometry(200, 5, 500, 50);
    ltitle->setStyleSheet(STYLE_SHEET_TITLE);
    ltitle->setFont(*font);
}

void Endoveinous::set_title(QString title)
{
    if ( ltitle == NULL_PTR )
        return;
    ltitle->setText(title);
}

void Endoveinous::init_catheter_status(int x0, int y0, int width, int height)
{
    lcatheterstatus = new QLabel(this);
    lcatheterstatus->setGeometry(x0, y0, width, height);
    this->pix_catheter_disconnected = new QPixmap(LOGO_CATHETER_DISCONNECTED);
    this->pix_catheter_connected = new QPixmap(LOGO_CATHETER_CONNECTED);
}

void Endoveinous::init_pad_status(int x0, int y0, int width, int height)
{
    lpadstatus = new QLabel(this);
    lpadstatus->setGeometry(x0, y0, width, height);
    this->pix_pad_disconnected = new QPixmap(LOGO_PAD_DISCONNECTED);
    this->pix_pad_connected = new QPixmap(LOGO_PAD_CONNECTED);
}


void Endoveinous::init_timer0(int x0, int y0, QFont *font, QWidget *parent)
{
    /*
    ltimer = new QLabel(this);
    ltimer->setGeometry(x0, y0, 100, 20);
    ltimer->setFont(font);
    ltimer->setText(QString("Timer"));
    */

    /*
    lcdclock = new QLCDNumber(parent);
    lcdclock->setSegmentStyle(QLCDNumber::Flat);
    lcdclock->setGeometry(x0, y0+20, 100, 50);
    lcdclock->setStyleSheet("background-color: black; color: blue;");
    lcdclock->setAttribute(Qt::WA_NoBackground, true);
    // lcdclock->setAttribute(Qt::WA_, true);
    lcdclock->setAttribute(Qt::WA_NoSystemBackground, true);
    */

    llogoclock = new QLabel(this);
    llogoclock->setGeometry(x0, y0, 64, 64);
    // but->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    llogoclock->setPixmap(QPixmap(LOGO_CLOCK));
    // connect(but, SIGNAL (released()), this, SLOT (trt_action));

    ltimer0 = new QLabel(this);
    ltimer0->setGeometry(x0, y0+65, 100, 50);
    ltimer0->setFont(*font);
    ltimer0->setStyleSheet(STYLE_SHEET_TIMER);
    // ltimer0->setText(QString("00:00"));
    time_display(0);
}

void Endoveinous::init_energy(int x0, int y0, QFont *font)
{

    llogoenergy = new QLabel(this);
    llogoenergy->setGeometry(x0, y0, 64, 64);
    // but->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    llogoenergy->setPixmap(QPixmap(LOGO_ENERGY));

    // lenergy = new QLabel(this);
    // lenergy->setGeometry(x0, y0, 100, 25);
    // lenergy->setFont(font);
    // lenergy->setText(QString("Energy"));

    /*
    lcdenergy= new QLCDNumber(this);
    lcdenergy->setSegmentStyle(QLCDNumber::Filled);
    lcdenergy->setGeometry(5, 145, 120, 50);
    lcdenergy->setStyleSheet("background-color: green; color: white;");
    lcdenergy->display("10000");
    */

    lenergy0 = new QLabel(this);
    lenergy0->setGeometry(x0, y0+70, 100, 20);
    lenergy0->setFont(*font);
    lenergy0->setStyleSheet(STYLE_SHEET_ENERGY);
    lenergy0->setText(QString("0 J"));
}

void Endoveinous::init_power(int x0, int y0, QFont font)
{
    gbpower = new QGroupBox(this);
    gbpower->setGeometry(x0, y0, 250, 115+10);
    gbpower->setVisible(true);
    gbpower->setStyleSheet(GROUPBOX_RUN_STYLE);

    lpowertile = new QLabel(gbpower);
    lpowertile->setGeometry(5, 5, 200, 30);
    lpowertile->setFont(font);
    lpowertile->setStyleSheet("border: none");
    lpowertile->setText((QString)param->get_label(IDX_POWER));

    BUTTONIMAGE_CREATE_PARENT(power_dec, gbpower, MINUS_IMAGE,  5, 40, PLUSMINUS_SIZE, PLUSMINUS_SIZE, handle_Trt_PowerDec())
    BUTTONIMAGE_CREATE_PARENT(power_inc, gbpower, PLUS_IMAGE, 160, 40, PLUSMINUS_SIZE, PLUSMINUS_SIZE, handle_Trt_PowerInc())

    lpower = new QLabel(gbpower);
    lpower->setGeometry(90, 35+30, 60, 30);
    lpower->setFont(font);
    lpower->setStyleSheet("border: none");
}

void Endoveinous::init_onoff(int x0, int y0)
{
    bonoff = new QPushButton(this);
    // bonoff->setGeometry(x0, y0, 128, 64);
    // bonoff->setIconSize(QSize(128, 64));
    bonoff->setGeometry(x0, y0, 64, 64);
    bonoff->setIconSize(QSize(64, 64));
    bonoff->setIcon(QIcon(BTN_ON3));
    // bonoff->setMask(region);
    connect(bonoff, SIGNAL (released()), this, SLOT (handle_Trt_OnOFF()));
}

void Endoveinous::init_vein_diameter(int x0, int y0, QFont *font)
{
    gbvein_diameter = new QGroupBox(this);
    gbvein_diameter->setGeometry(x0, y0, 300, 130);
    gbvein_diameter->setVisible(true);
    gbvein_diameter->setStyleSheet(GROUPBOX_RUN_STYLE);
    // gbvein_diameter->setStyleSheet("border: 10px solid; color: black");

    lveindiametertitle = new QLabel("Vein diameter", gbvein_diameter);
    lveindiametertitle->setGeometry(50, 5, 300, 30);
    lveindiametertitle->setFont(*font);
    lveindiametertitle->setStyleSheet("border: none");

    BUTTONIMAGE_CREATE_PARENT(veindiameter_dec, gbvein_diameter, MINUS_IMAGE,   5, 40, PLUSMINUS_SIZE, PLUSMINUS_SIZE, handle_Trt_VeinDiameterDec())
    BUTTONIMAGE_CREATE_PARENT(veindiameter_inc, gbvein_diameter, PLUS_IMAGE, 220, 40, PLUSMINUS_SIZE, PLUSMINUS_SIZE, handle_Trt_VeinDiameterInc())

    lveindiameter = new QLabel(gbvein_diameter);
    lveindiameter->setFont(*font);
    lveindiameter->setGeometry(90, 58, 130, 30);
    lveindiameter->setStyleSheet("border: none");
}

void Endoveinous::init_pedalcounter(int x0, int y0, QFont *font)
{
    qgbdedal = new QGroupBox(this);
    qgbdedal->setGeometry(x0, y0, 110, 110);
    qgbdedal->setVisible(true);
    // qgbdedal->setStyleSheet("border: 1px solid #FF00005D");
    qgbdedal->setStyleSheet("border: none");

    lcdpedal= new QLCDNumber(qgbdedal);
    lcdpedal->setSegmentStyle(QLCDNumber::Filled);
    lcdpedal->setGeometry(5, 5, 100, 50);
    lcdpedal->setStyleSheet("background-color: FFE0E0FF; color: black;");
}


void Endoveinous::init_manual_preset(int x0, int y0, QFont *font)
{
    ichecked = new QIcon(LOGO_CHECKED);
    iunchecked = new QIcon(LOGO_UNCHECKED);

    gbmanual_preset = new QGroupBox(this);
    gbmanual_preset->setGeometry(x0, y0, 200, 115);
    gbmanual_preset->setVisible(true);
    // gbmanual_preset->setStyleSheet("border: 1px solid #FF00005D");
    gbmanual_preset->setStyleSheet(GROUPBOX_RUN_STYLE);

    bmanual = new QPushButton(gbmanual_preset);
    bmanual->setGeometry(5, 5, 50, 50);
    bmanual->setIconSize(QSize(50, 50));
    bmanual->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    connect(bmanual, SIGNAL (released()), this, SLOT (handle_Trt_Manual()));
    lmanual = new QLabel((QString)param->get_label(IDX_MANUAL), gbmanual_preset);
    lmanual->setGeometry(60, 5, 300, 30);
    lmanual->setFont(*font);
    lmanual->setStyleSheet("border: none");

    bpreset = new QPushButton(gbmanual_preset);
    bpreset->setGeometry(5, 60, 50, 50);
    bpreset->setIconSize(QSize(50, 50));
    bpreset->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    connect(bpreset, SIGNAL (released()), this, SLOT (handle_Trt_Preset()));
    lpreset = new QLabel((QString)param->get_label(IDX_PRESET), gbmanual_preset);
    lpreset->setGeometry(60, 65, 300, 30);
    lpreset->setFont(*font);
    lpreset->setStyleSheet("border: none");
}

void Endoveinous::init_progressbar(int x0, int y0, QString lab, QFont *font)
{
    gbprogressbar = new QGroupBox(this);
    gbprogressbar->setGeometry(x0, y0, 250, 115+10);
    gbprogressbar->setVisible(true);
    gbprogressbar->setStyleSheet(GROUPBOX_RUN_STYLE);

    lprogressbartitle = new QLabel(gbprogressbar);
    lprogressbartitle->setGeometry(5, 5, 200, 30);
    lprogressbartitle->setFont(*font);
    lprogressbartitle->setStyleSheet("border: none");
    lprogressbartitle->setText(lab);

    pbpower = new QProgressBar(gbprogressbar);
    pbpower->setGeometry(5, 45, 240, 50);
    pbpower->setMinimum(0);
    pbpower->setMaximum(100);
    pbpower->setValue(0);
    pbpower->setFormat("");
    pbpower->setStyleSheet("QProgressBar::chunk{background-color:rgb(200,0,0)}");
}

void Endoveinous::init_facelegs(int x0, int y0, QFont *font)
{
    ichecked = new QIcon(LOGO_CHECKED);
    iunchecked = new QIcon(LOGO_UNCHECKED);

    gbfacelegs = new QGroupBox(this);
    gbfacelegs->setGeometry(x0, y0, 250, 115+10);
    gbfacelegs->setVisible(true);
    gbfacelegs->setStyleSheet(GROUPBOX_RUN_STYLE);

    bface = new QPushButton(gbfacelegs);
    bface->setGeometry(5, 5, 50, 50);
    bface->setIconSize(QSize(50, 50));
    bface->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);


    connect(bface, SIGNAL (released()), this, SLOT (handle_Trt_Face()));
    lface = new QLabel("Face", gbfacelegs);
    lface->setGeometry(60, 5, 300, 30);
    lface->setFont(*font);
    lface->setStyleSheet("border: none");

    bleg = new QPushButton(gbfacelegs);
    bleg->setGeometry(5, 60, 50, 50);
    bleg->setIconSize(QSize(50, 50));
    bleg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    connect(bleg, SIGNAL (released()), this, SLOT (handle_Trt_Leg()));
    lleg = new QLabel("Legs", gbfacelegs);
    lleg->setGeometry(60, 65, 300, 35);
    lleg->setFont(*font);
    lleg->setStyleSheet("Border: none");

    llogopulse = new QLabel(this);
    llogopulse->setGeometry(x0+255, y0, 250, 125);
    QPixmap *pix = new QPixmap(LOGO_PULSE);
    llogopulse->setPixmap(*pix);
}

void Endoveinous::init_pulsewidth(int x0, int y0, QFont *font)
{
    gbpulsewidth = new QGroupBox(this);
    gbpulsewidth->setGeometry(x0, y0, 250, 115+10);
    gbpulsewidth->setVisible(true);
    gbpulsewidth->setStyleSheet(GROUPBOX_RUN_STYLE);

    lpulsewidth_title = new QLabel(gbpulsewidth);
    lpulsewidth_title->setGeometry(5, 5, 200, 30);
    lpulsewidth_title->setFont(*font);
    lpulsewidth_title->setStyleSheet("border: none");
    lpulsewidth_title->setText((QString)param->get_label(IDX_PULSEWIDTH));


    BUTTONIMAGE_CREATE_PARENT(bpulsewidth_dec, gbpulsewidth, MINUS_IMAGE,  5, 40, PLUSMINUS_SIZE, PLUSMINUS_SIZE, handle_Trt_PulseWidthDec())
    BUTTONIMAGE_CREATE_PARENT(bpulsewidth_inc, gbpulsewidth, PLUS_IMAGE, 160, 40, PLUSMINUS_SIZE, PLUSMINUS_SIZE, handle_Trt_PulseWidthInc())

    lpulsewidth = new QLabel(gbpulsewidth);
    lpulsewidth->setGeometry(90, 35+30, 60, 30);
    lpulsewidth->setFont(*font);
    lpulsewidth->setStyleSheet("border: none");
}

void Endoveinous::init_delay(int x0, int y0, QFont *font)
{
    gbdelay = new QGroupBox(this);
    gbdelay->setGeometry(x0, y0, 250, 115+10);
    gbdelay->setVisible(true);
    gbdelay->setStyleSheet(GROUPBOX_RUN_STYLE);

    ldelay_title = new QLabel(gbdelay);
    ldelay_title->setGeometry(5, 5, 200, 30);
    ldelay_title->setFont(*font);
    ldelay_title->setStyleSheet("border: none");
    ldelay_title->setText((QString)param->get_label(IDX_DELAY));

    BUTTONIMAGE_CREATE_PARENT(bdelay_dec, gbdelay, MINUS_IMAGE,  5, 40, PLUSMINUS_SIZE, PLUSMINUS_SIZE, handle_Trt_DelayDec())
    BUTTONIMAGE_CREATE_PARENT(bdelay_inc, gbdelay, PLUS_IMAGE, 160, 40, PLUSMINUS_SIZE, PLUSMINUS_SIZE, handle_Trt_DelayInc())

    ldelay = new QLabel(gbdelay);
    ldelay->setGeometry(90, 35+30, 60, 30);
    ldelay->setFont(*font);
    ldelay->setStyleSheet("border: none");
}


// ============================================================
//
// ============================================================
void Endoveinous::init()
{
    // patient = new PATIENT0();
    // read_user_info(patient);

    if ( this->treatment_type == ENDOVENOUS)
    {
        init_endovenous();
        power_display(care->val[care_power]);
        onoff_display(onoff);
        catheterstatus_display(catheter_status);
        padstatus_display(pad_status);
        manual_preset_display(care->val[care_manualpreset]);
    }
    else if ( this->treatment_type == TRANSCUTANEOUS )
    {
        init_transcutaneous();
        setFace_Legs(face_legs);
    }
    else if ( this->treatment_type == PROCTOLOGY )
    {
        init_proctology();
        onoff_display(onoff);
    }
}


void Endoveinous::init_endovenous()
{
    QFont *font = new QFont(TITLE_LABEL_FONT_NAME, TITLE_LABEL_FONT_SIZE-10, TITLE_LABEL_FONT_WEIGHT);
    QFont font2 = QFont(TITLE_LABEL_FONT_NAME, 15, TITLE_LABEL_FONT_WEIGHT);

    init_energy(5, 150, font_energy);
    init_timer0(5, 20, font_timer, this);

    switch ( this->treatment )
    {
      case RUN_CR45i:
        init_manual_preset(150, 60, font);
        init_vein_diameter(360, 60, font);
        helpmenu_init(725, 70);
        init_power(150, 200, *font);
        init_progressbar(410, 200, (QString)param->get_label(IDX_PEDAL), font);

        set_manual_preset(care->val[care_manualpreset]);
        veindiameter_display(veindiameter);
        init_onoff(350, 400);
        break;
      case RUN_CR40i:
        helpmenu_init(725, 70);
        init_power(150, 150, *font);
        init_progressbar(410, 150, (QString)param->get_label(IDX_PEDAL), font);
        init_onoff(350, 400);
        break;
      case RUN_CR30i:
        helpmenu_init(725, 70);
        init_power(150, 150, *font);
        init_progressbar(410, 150, (QString)param->get_label(IDX_PEDAL), font);
        init_onoff(350, 400);
        break;
    }

}



// ===================================================================
//
// ===================================================================
Care *Endoveinous::care_init(int type, int treatment)
{
    Care *care = new Care();
    for (int i=0; i<CARE_NBRE; i++)
        care->val[i] = PROTOCOLES[type][treatment][i];
    care->protocol_name = this->param->get_label(ARRAY_PROTOCOL_NAME[type][treatment]);

    if ( type == TRANSCUTANEOUS && treatment == RUN_TRANSCUTANEOUS )
    {
        transcutaneous_faceleg_param_ini(care, care->val[care_faceleg]);
    }
    return care;
}






void Endoveinous::transcutaneous_faceleg_param_ini(Care *care, int type)
{
    if ( care == NULL_PTR )
        return;
    care->val[care_power] = ARRAY_TRANSCUTANEOUS_POWER[type];
    care->val[care_powermin] = ARRAY_TRANSCUTANEOUS_POWER_MIN[type];
    care->val[care_powermax] = ARRAY_TRANSCUTANEOUS_POWER_MAX[type];
    care->val[care_pulsewidth] = ARRAY_TRANSCUTANEOUS_PULSEWIDTH[type];
    care->val[care_pulsewidth_min] = ARRAY_TRANSCUTANEOUS_PULSEWIDTH_MIN[type];
    care->val[care_pulsewidth_max] = ARRAY_TRANSCUTANEOUS_PULSEWIDTH_MAX[type];
    care->val[care_delay] = ARRAY_TRANSCUTANEOUS_DELAY[type];
    care->val[care_delay_min] = ARRAY_TRANSCUTANEOUS_DELAY_MIN[type];
    care->val[care_delay_max] = ARRAY_TRANSCUTANEOUS_DELAY_MAX[type];
}

Care *Endoveinous::care_release(Care *care)
{
    if ( care != NULL_PTR )
        delete care;
    return NULL_PTR;
}

void Endoveinous::set_patient_dir(QString *dir)
{
    this->patient_dir = dir;
}

void Endoveinous::helpmenu_init(int x0, int y0)
{
    int h = 245;
    if ( this->id < 0)
        h = 175;
    gbhelpmenu = new QGroupBox(this);
    gbhelpmenu->setGeometry(x0, y0, 70, h);
    gbhelpmenu->setVisible(true);
    gbhelpmenu->setStyleSheet(GROUPBOX_RUN_STYLE);

    BUTTONIMAGE_CREATE_PARENT(bquikuserguide, gbhelpmenu, "./data/book.jpg",      5,   5, 60, 60, handle_Trt_QuickUserInfo())
    BUTTONIMAGE_CREATE_PARENT(bprotocol, gbhelpmenu,      "./data/doctor.jpg",    5,  85, 60, 60, handle_Trt_Protocol())
    if ( this->id >= 0 )
    {
      BUTTONIMAGE_CREATE_PARENT(buserinfo, gbhelpmenu,      "./data/user_info.jpg", 5, 170, 60, 60, handle_Trt_UserInfo())
    }
}


void Endoveinous::init_transcutaneous()
{
    QFont *font = new QFont(TITLE_LABEL_FONT_NAME, TITLE_LABEL_FONT_SIZE-10, TITLE_LABEL_FONT_WEIGHT);

    init_timer0(5, 20, font_timer, this);
    init_facelegs(150, 60, font);
    init_power(150, 180+10, *font);
    helpmenu_init(725, 70);
    init_pulsewidth(150, 300+20, font);
    init_delay(420, 300+20, font);
    init_pedalcounter(0, 150, font);
    init_onoff(5, 400);
    power_display(care->val[care_power]);
    pulsewidth_display(care->val[care_pulsewidth]);
    delay_display(care->val[care_delay]);
    onoff_display(this->onoff);
}


void Endoveinous::set_manual_preset(int val)
{
    if ( bmanual == NULL_PTR || bpreset == NULL_PTR )
        return;
    bmanual->setIcon(*iunchecked);
    bpreset->setIcon(*iunchecked);
    if ( val == 0 )
        bmanual->setIcon(*ichecked);
    else if ( val == 1 )
        bpreset->setIcon(*ichecked);
}

void Endoveinous::manual_preset_display(int val)
{
    if ( gbvein_diameter == NULL_PTR )
        return;
    if ( val == 0 )
        // gbvein_diameter->setEnabled(false);
        gbvein_diameter->setVisible(false);
    else
        // gbvein_diameter->setEnabled(true);
        gbvein_diameter->setVisible(true);
}

void Endoveinous::setFace_Legs(int val)
{
    if ( bface == NULL_PTR || bleg == NULL_PTR )
        return;
    bface->setIcon(*iunchecked);
    bleg->setIcon(*iunchecked);
    if ( val == 0 )
        bface->setIcon(*ichecked);
    else if ( val == 1 )
        bleg->setIcon(*ichecked);
}


void Endoveinous::init_proctology()
{
    QFont *font = new QFont(TITLE_LABEL_FONT_NAME, TITLE_LABEL_FONT_SIZE-10, TITLE_LABEL_FONT_WEIGHT);
    init_lcdpower_proctology(350, 140);
    switch ( this->treatment )
    {
      case RUN_HPR45i:
        helpmenu_init(725, 70);
        init_power(150, 200, *font);
        init_progressbar(410, 200, (QString)param->get_label(IDX_ENERGY), font);
        init_onoff(350, 400);
        init_catheter_status(230, 400, 64, 64);
        init_pad_status(550, 400, 64, 64);
        init_timer0(5, 20, font_timer, this);
        power_display(care->val[care_power]);
        break;
      case RUN_FISTULA:
        helpmenu_init(725, 70);
        init_power(150, 200, *font);
        init_progressbar(410, 200, (QString)param->get_label(IDX_ENERGY), font);
        init_onoff(350, 400);
        init_timer0(5, 20, font_timer, this);
        init_catheter_status(230, 400, 64, 64);
        init_pad_status(550, 400, 64, 64);
        power_display(care->val[care_power]);
        break;
    }
}


void Endoveinous::init_lcdpower_proctology(int x0, int y0)
{
    /*
    lcdenergy= new QLCDNumber(this);
    lcdenergy->setSegmentStyle(QLCDNumber::Filled);
    lcdenergy->setGeometry(x0, y0, 200, 100);
    lcdenergy->setStyleSheet("background-color: green; color: white;");
    lcdenergy->display("10000");
    lcdenergy->setFont(QFont(TITLE_LABEL_FONT_NAME, TITLE_LABEL_FONT_SIZE+30, TITLE_LABEL_FONT_WEIGHT));
    */

    QFont font2 = QFont(TITLE_LABEL_FONT_NAME, 35, TITLE_LABEL_FONT_WEIGHT);
    lenergy0 = new QLabel(this);
    lenergy0->setGeometry(x0, y0, 200, 40);
    lenergy0->setFont(font2);
    lenergy0->setStyleSheet("{color: #0000FF}");
    lenergy0->setText(QString("0 J"));
}


void Endoveinous::veindiameter_display(int val)
{
    if ( lveindiameter == NULL_PTR )
        return;
    lveindiameter->setText(QString(ARRAY_VEIN_DIAMETER[val]));
}

void Endoveinous::power_display(int val)
{
    QString str = QString::number(val) + QString("W");
    lpower->setText(str);

}

void Endoveinous::pulsewidth_display(int val)
{
    if ( lpulsewidth == NULL_PTR )
        return;
    QString str = QString::number(val/10) + QString(".") + QString::number(val%10) + QString("s");
    lpulsewidth->setText(str);
}

void Endoveinous::delay_display(int val)
{
    if ( ldelay == NULL_PTR )
        return;
    QString str = QString::number(val/10) + QString(".") + QString::number(val%10) + QString("s");
    ldelay->setText(str);
}




void Endoveinous::onoff_display(int val)
{
    QIcon *ii = NULL_PTR;
    if ( val == 0 )
        ii = new QIcon(BTN_OFF3);
    else
        ii = new QIcon(BTN_ON3);

    bonoff->setIcon(*ii);
}


void Endoveinous::catheterstatus_display(int val)
{
    if ( this->lcatheterstatus == NULL_PTR )
        return;
    if ( val == 0 )
       lcatheterstatus->setPixmap(*this->pix_catheter_disconnected);
    else
        lcatheterstatus->setPixmap(*this->pix_catheter_connected);
}

void Endoveinous::padstatus_display(int val)
{
    if ( this->lpadstatus == NULL_PTR )
        return;
    if ( val == 0 )
        lpadstatus->setPixmap(*this->pix_pad_disconnected);
    else
        lpadstatus->setPixmap(*this->pix_pad_connected);
}

void Endoveinous::cycle_count_display(int val)
{
    if ( lcdpedal == NULL_PTR ) return;
    lcdpedal->display(val);
}

/*
void Endoveinous::catheterstatus_display_off()
{
    if ( this->lcatheterstatus == NULL_PTR )
        return;
    if ( val == 0 )
       lcatheterstatus->setPixmap(*this->pix_catheter_disconnected);
    else
        lcatheterstatus->setPixmap(*this->pix_catheter_connected);
}
*/

void Endoveinous::handle_Trt_Manual()
{
    dio->button_beep();
    if ( this->onoff == 1 ) return;
    // manual_preset = 0;
    care->val[care_manualpreset] = 0;
    set_manual_preset(care->val[care_manualpreset]);
    manual_preset_display(care->val[care_manualpreset]);
}

void Endoveinous::handle_Trt_Preset()
{
    dio->button_beep();
    if ( this->onoff == 1 ) return;
    //manual_preset = 1;
    care->val[care_manualpreset] = 1;
    set_manual_preset(care->val[care_manualpreset]);
    manual_preset_display(care->val[care_manualpreset]);
}

void Endoveinous::handle_Trt_Face()
{
    dio->button_beep();
    if ( this->onoff == 1 ) return;
    // manual_preset = 0;
    care->val[care_faceleg] = 0;
    setFace_Legs(care->val[care_faceleg]);
    transcutaneous_faceleg_param_ini(care, care->val[care_faceleg]);
    power_display(care->val[care_power]);
    pulsewidth_display(care->val[care_pulsewidth]);
    delay_display(care->val[care_delay]);
    // manual_preset_display(care->val[care_manualpreset]);
}

void Endoveinous::handle_Trt_Leg()
{
    dio->button_beep();
    if ( this->onoff == 1 ) return;
    //manual_preset = 1;
    care->val[care_faceleg] = 1;
    setFace_Legs(care->val[care_faceleg]);
    transcutaneous_faceleg_param_ini(care, care->val[care_faceleg]);
    power_display(care->val[care_power]);
    pulsewidth_display(care->val[care_pulsewidth]);
    delay_display(care->val[care_delay]);
        // manual_preset_display(care->val[care_manualpreset]);
}


void Endoveinous::handle_Trt_VeinDiameterDec()
{
    dio->button_beep();
    if ( this->onoff == 1 ) return;
    if ( veindiameter > 0 )
        veindiameter--;
    veindiameter_display(veindiameter);
}

void Endoveinous::handle_Trt_VeinDiameterInc()
{
    dio->button_beep();
    if ( this->onoff == 1 ) return;
    if ( veindiameter < 6 )
        veindiameter++;
    veindiameter_display(veindiameter);
}


void Endoveinous::handle_Trt_PowerDec()
{
    dio->button_beep();
    // if ( this->onoff == 1 ) return;
    if ( pedal_read() == 1 ) return;
//    if ( care->val[care_power] > care->val[care_powermin] )
        if ( care->val[care_power] > 0 )
        care->val[care_power]--;
    power_display(care->val[care_power]);
}


void Endoveinous::handle_Trt_PowerInc()
{
    dio->button_beep();
    // if ( this->onoff == 1 ) return;
    if ( pedal_read() == 1 ) return;
    if ( care->val[care_power] < care->val[care_powermax] )
        care->val[care_power]++;
    power_display(care->val[care_power]);
}

void Endoveinous::handle_Trt_OnOFF()
{
    dio->button_beep();
    if ( onoff == 0 )
    {
       onoff = 1;
       this->total_time0 = 0;
       time_display(this->total_time0);
       this->cycle_time = 0;
       power_progressbar_display(0);
       this->energy0 = 0.0;
       energy_display(0.0);
       this->cycle_cpt = 0;
       this->cycle_count = 0;
       cycle_count_display(this->cycle_count);
    }
    else
    {
       onoff = 0;
       master_database_write();
       user_database_write();
    }
    onoff_display(onoff);
    // close();
}

void Endoveinous::handle_Trt_PulseWidthDec()
{
    dio->button_beep();
    if ( care->val[care_pulsewidth] > care->val[care_pulsewidth_min])
    {
        care->val[care_pulsewidth]--;
        pulsewidth_display(care->val[care_pulsewidth]);
    }
}

void Endoveinous::handle_Trt_PulseWidthInc()
{
    dio->button_beep();
    if ( care->val[care_pulsewidth] < care->val[care_pulsewidth_max] )
    {
        care->val[care_pulsewidth]++;
        pulsewidth_display(care->val[care_pulsewidth]);
    }
}

void Endoveinous::handle_Trt_DelayDec()
{
    dio->button_beep();
    if ( care->val[care_delay] > care->val[care_delay_min] )
    {
        care->val[care_delay]--;
        delay_display(care->val[care_delay]);
    }
}

void Endoveinous::handle_Trt_DelayInc()
{
    dio->button_beep();
    if ( care->val[care_delay] < care->val[care_delay_max] )
    {
        care->val[care_delay]++;
        delay_display(care->val[care_delay]);
    }
}


// ================================================================================


void Endoveinous::handle_Trt_Exit()
{
    ht_program(0, 0);
    dio->button_beep();
    FREE(this->patient);
    delete this;
    // close();
}


void Endoveinous::handle_Trt_QuickUserInfo()
{
    /*
    quickuserguide = new QuickUserInfo(NULL_PTR);
    quickuserguide->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    quickuserguide->setGeometry(QRect(QPoint(0, 0), this->size()));
    quickuserguide->setParent(this);
    quickuserguide->show();
    */
}


void Endoveinous::handle_Trt_Protocol()
{
    dio->button_beep();
    protocol = new Protocol(NULL_PTR, this->treatment_type, this->treatment);
    protocol->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    protocol->setGeometry(QRect(QPoint(0, 0), this->size()));
    protocol->setParent(this);
    protocol->show();
}

void Endoveinous::handle_Trt_UserInfo()
{
    dio->button_beep();
    quickuserguide = new QuickUserInfo(NULL_PTR, this->param, this->id, this->patient);
    quickuserguide->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    quickuserguide->setGeometry(QRect(QPoint(0, 0), this->size()));
    quickuserguide->setParent(this);
    quickuserguide->show();
}


// ====================================================================
// pseudo hardware communication
/*
const int DIGITAl_POTENTIOMETER_VALUE[] =
{
    0, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105,
    115, 125, 135, 145, 155, 165, 175, 185, 195,
    205, 215, 225, 235, 245, 255
};
*/

/*
const int DIGITAl_POTENTIOMETER_VALUE[] =
{
0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 255, 255, 255
};
*/



/*
void Endoveinous::init_gpio()
{
    gpio_set_power(0);
    gpio_set_hf(0);
}

int Endoveinous::gpio_get_pedal()
{
    return 0;
}

int Endoveinous::gpio_set_power(int val)
{
    return 1;
}

int Endoveinous::gpio_get_pad_status()
{
    return 1;
}

int Endoveinous::gpio_get_catheter_status()
{
    return 1;
}

int Endoveinous::gpio_set_hf(int val)
{
    return 1;
}*/




// ================================================



void Endoveinous::time_display(int time_ms)
{
    if ( ltimer0 != NULL_PTR )
    {
        // QString str = QString::number(time_ms / 10) + QString(" s");
        // lcdclock->display(str);
        char tmp[10];
        int hh, mm, ss;
        seconds_to_hhmmss(time_ms / 10, &hh, &mm, &ss);
        // QString str = QString::number(mm) + QString(":") + QString::number(ss);
        sprintf(tmp, "%.2d:%.2d", mm, ss);
        QString str = QString(tmp);
        ltimer0->setText(str);
    }
    if ( this->lcdclock != NULL_PTR)
    {
        QString text =  QString::number(time_ms / 10);
        this->lcdclock->display(text);
    }
}

void Endoveinous::power_progressbar_display(int power)
{
    if ( pbpower == NULL_PTR ) return;
    pbpower->setValue(power);

    double r, g, b, h, s, v;
    h = (double)(1.0-power/100.0)*360.0/3.;
    s = 1;
    v = 1;
    hsv2rgb(h, s, v, &r, &g, &b);
    char str[200];
    sprintf(str, "QProgressBar::chunk{background-color:rgb(%d,%d,%d)}", (int)(250*r), (int)(250*g), (int)(250*b));
    pbpower->setStyleSheet(QString(str));
}

void Endoveinous::energy_display(double energy)
{
    if ( lenergy0 == NULL_PTR ) return;
    QString str = QString::number((int)floor(energy)) + QString(" J");
    lenergy0->setText(str);
}


// debug
void Endoveinous::trt_debug_pedal_on()
{
    if ( debug_pedal == 0 )
    {
        debug_pedal = 1;
        this->debug_pedal_on->setText("pedal on");
    }
    else
    {
        debug_pedal = 0;
        this->debug_pedal_on->setText("pedal off");
    }
}

void Endoveinous::trt_debug_pad_on()
{
    if ( debug_pad == 0 )
    {
        debug_pad = 1;
        this->debug_pad_on->setText("pad on");
    }
    else
    {
        debug_pad = 0;
        this->debug_pad_on->setText("pad off");
    }
}

void Endoveinous::trt_debug_cath_on()
{
    if ( debug_cath == 0 )
    {
        debug_cath = 1;
        this->debug_cath_on->setText("cath on");
    }
    else
    {
        debug_cath = 0;
        this->debug_cath_on->setText("cath off");
    }
}


// ==================================================
// write database

void Endoveinous::master_database_fill(void *_data)
{    
    MASTER_DATABASE_PATIENT *data = (MASTER_DATABASE_PATIENT*)_data;
    PATIENT *p = (PATIENT*)this->patient;
    if ( data == NULL_PTR ) return;

    strcpy(data->name, p->name);
    data->age = p->age;
    strcpy(data->ceap, p->ceap);
    strcpy(data->remark, p->remark);
    data->date = get_compact_date_yyyymmdd();
    data->time = get_compact_time_hhmm();

    data->treatment_type = this->treatment_type;
    data->treatment = this->treatment;
    data->energy = this->energy0;
    data->treatment_time = this->total_time0;
    data->vein_diameter = this->veindiameter;
    data->pad_connectivity = pad_read();
}

void Endoveinous::master_database_write()
{
    MASTER_DATABASE_PATIENT data;
    master_database_fill(&data);
    database_master_write((char*)MASTER_DATABASE_FILENAME, &data);
}


void Endoveinous::user_database_fill(void *_data)
{
    USER_DATABASE_PATIENT *data = (USER_DATABASE_PATIENT*)_data;
    PATIENT *p = (PATIENT*)this->patient;
    if ( data == NULL_PTR ) return;

    strcpy(data->name, p->name);
    data->age = p->age;
    strcpy(data->ceap, p->ceap);
    strcpy(data->remark, p->remark);
    data->date = get_compact_date_yyyymmdd();
    data->time = get_compact_time_hhmm();

    data->treatment_type = this->treatment_type;
    data->treatment = this->treatment;
    data->energy = this->energy0;
    data->treatment_time = this->total_time0;
    data->vein_diameter = this->veindiameter;
    data->pad_connectivity = pad_read();
}

void Endoveinous::user_database_write()
{    
    USER_DATABASE_PATIENT data;
    user_database_fill(&data);
    database_user_write((char*)USER_DATABASE_FILENAME, &data);
}


