
#include <QLabel>
#include <QFont>

#include <stdio.h>

#include <util.h>
#include <config.h>
#include <dataio.h>

#include "powerqualibration.h"
#include "ui_powerqualibration.h"

PowerQualibration::PowerQualibration(QWidget *parent, dataio *dio) :
    QMainWindow(parent),
    ui(new Ui::PowerQualibration)
{
    ui->setupUi(this);

    this->dio = dio;
    read_type = 0;
    // this->id = id;

    setGeometry(QRect(QPoint(0, 0), QSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)));
    QPixmap *pix = new QPixmap(MAIN_SCREEN_IMAGE2);
    QLabel *lab = new QLabel(this);
    lab->setGeometry(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    lab->setPixmap(*pix);

    // QFont *font = new QFont(TITLE_LABEL_FONT_NAME, TITLE_LABEL_FONT_SIZE, TITLE_LABEL_FONT_WEIGHT);


    BUTTONIMAGE_CREATE(bpowerdec, MINUS_IMAGE, 300, 100, 75, 75, handle_Trt_powerDec())
    BUTTONIMAGE_CREATE(bpowerinc, PLUS_IMAGE, 380, 100, 75, 75, handle_Trt_PowerInc())

    BUTTONIMAGE_CREATE(breadtype_dec, MINUS_IMAGE, 0, 400, 75, 75, handle_Trt_readtypeDec())
    BUTTONIMAGE_CREATE(breadtype_inc, PLUS_IMAGE, 75, 400, 75, 75, handle_Trt_readtypeInc())

    BUTTONIMAGE_CREATE(bCancel, CANCEL_IMAGE, 720, 400, 75, 75, handle_Trt_BCancel())


    QFont *font = new QFont(TITLE_LABEL_FONT_NAME, TITLE_LABEL_FONT_SIZE-5, TITLE_LABEL_FONT_WEIGHT);

    lpower = new QLabel("0");
    lpower->setGeometry(150, 30, 500, 50);
    lpower->setFont(*font);
    lpower->setVisible(true);
    lpower->setStyleSheet("border: none");
    lpower->setParent(this);

    lpowerread = new QLabel("0");
    lpowerread->setGeometry(150, 300, 500, 50);
    lpowerread->setFont(*font);
    lpowerread->setVisible(true);
    lpowerread->setStyleSheet("border: none");
    lpowerread->setParent(this);


    lreadtype = new QLabel("0");
    lreadtype->setGeometry(160, 420, 500, 50);
    lreadtype->setFont(*font);
    lreadtype->setVisible(true);
    lreadtype->setStyleSheet("border: none");
    lreadtype->setParent(this);

    bonoff = new QPushButton(this);
    // bonoff->setGeometry(x0, y0, 128, 64);
    // bonoff->setIconSize(QSize(128, 64));
    bonoff->setGeometry(500, 300, 64, 64);
    bonoff->setIconSize(QSize(64, 64));
    bonoff->setIcon(QIcon(BTN_OFF3));
    // bonoff->setMask(region);
    connect(bonoff, SIGNAL (released()), this, SLOT (handle_Trt_OnOFF()));

    catheter_status_enable(0);
    idx_power = 0;
    startstop = 0;
    display();
    read_type_display(this->read_type);


    timer = new QTimer(this);
    timer->start(1000);
//    connect(timer, &QTimer::timeout, this, &Endoveinous::showTime);
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
}

PowerQualibration::~PowerQualibration()
{
    delete ui;
}


const static int AUTOTEST_DIGITAl_POTENTIOMETER_VALUE[] =
{
  // 255, 245, 244, 237, 232, 225, 219, 212, 205, 198, 190, 182, 173, 162, 153, 144, 132, 122, 111, 96, 84, 67, 53, 33, 17, 0
    255, //  0
    250, //  1
    245, //  2
    240, //  3
    235, //  4
    230, //  5
    225, //  6
    225, //  7
    220, //  8
    218, //  9
    215, // 10
    210, // 11
    205, // 12
    200, // 13
    195, // 14
    190, // 15
    185, // 16
    180, // 17
    175, // 18
    170, // 19
    165, // 20
    155, // 21
    150, // 22
    145, // 23
    140, // 24
    130, // 25
    130  // 25 bis
};

void PowerQualibration::handle_Trt_PowerInc()
{
    if ( idx_power < 25 )
    {
        dio->button_beep();
        idx_power++;
        ht_program(1, AUTOTEST_DIGITAl_POTENTIOMETER_VALUE[idx_power]);
        display();
    }


}

void PowerQualibration::handle_Trt_powerDec()
{
    if ( idx_power > 0 )
    {
        dio->button_beep();
        idx_power--;
        ht_program(1, AUTOTEST_DIGITAl_POTENTIOMETER_VALUE[idx_power]);
        display();
    }
}

void PowerQualibration::handle_Trt_BCancel()
{
    ht_program(0, 0);
    dio->button_beep();
    close();
    // delete this;
}


void PowerQualibration::display()
{
    char txt[100];

    sprintf(txt, "power: %d w [ %d ]", idx_power, AUTOTEST_DIGITAl_POTENTIOMETER_VALUE[idx_power]);
    lpower->setText(QString(txt));

    int ret16 = get_adc(this->read_type);
    int ret8 = ret16 >> 8;
    sprintf(txt, "read: %d  [ %d ]", ret8, ret16);
    lpowerread->setText(QString(txt));

}

void PowerQualibration::read_type_display(int type)
{
    char txt[100];
    sprintf(txt, "config. %d", type);
    lreadtype->setText(QString(txt));
}

void PowerQualibration::handle_Trt_OnOFF()
{
    if ( startstop == 0 )
    {
        startstop = 1;
        ht_program(1, AUTOTEST_DIGITAl_POTENTIOMETER_VALUE[idx_power]);
    }
    else
    {
        startstop = 0;
        ht_program(0, 0);
    }

    QIcon *ii = NULL_PTR;
    if ( startstop == 0 )
        ii = new QIcon(BTN_OFF3);
    else
        ii = new QIcon(BTN_ON3);

    bonoff->setIcon(*ii);
}

void PowerQualibration::handle_Trt_readtypeDec()
{
    if ( this->read_type != 0 )
    {
        this->read_type--;
        read_type_display(this->read_type);
    }
}

void PowerQualibration::handle_Trt_readtypeInc()
{
    if ( this->read_type < 1 )
    {
        this->read_type++;
        read_type_display(this->read_type);
    }
}



void PowerQualibration::showTime()
{
    display();
}

int PowerQualibration::get_adc(int type)
{
    int ret = 0;

    switch ( type )
    {
      case 0: ret = dio->spi_read(0); break;
      case 1: ret = dio->spi_read_v2(0); break;
    default : ret = dio->spi_read(0); break;
    }
    return ret;
}



void PowerQualibration::catheter_status_enable(int val)
{
#ifdef _GPIO_
    if ( val == 1 )
    {
        delay(50);
    }
    dio->set_mc_sturing(val);
    if ( val == 0 )
    {
       delay(50);
    }
#else
    printf("Program HT\n");
#endif
}


void PowerQualibration::ht_program(int type, int val)
{
#ifdef _GPIO_
    dio->set_hf_en(0);
    if ( type == 0 )
    {
        dio->spi_pot_write(255);
        dio->set_hv_en(0);
        dio->set_hf_en(0);
        // dio-> spi_pot_write(255);
        delay(10);
    }
    else
    {
        dio->spi_pot_write(val);
        delay(1);
        dio->set_hv_en(1);
        delay(1);
    }
#else
    printf("Program HT\n");
#endif
}
