#include "autocheck.h"
#include "ui_autocheck.h"

#include <QFont>

#include <math.h>

#include <./include/util.h>
#include <include/config.h>

#define STYLE_SHEET_TITLE "QLabel { background-color : none; color : #007F00; }"
#define FONT_TITLE "Helvetica", 22, QFont::Bold

const static int AUTOCHECK_DIGITAl_POTENTIOMETER_VALUE[] =
{
  // 255, 245, 244, 237, 232, 225, 219, 212, 205, 198, 190, 182, 173, 162, 153, 144, 132, 122, 111, 96, 84, 67, 53, 33, 17, 0
    255,
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

#define IDX_POWER_MAX 26

autocheck::autocheck(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::autocheck)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #FFFFF;");

    QFont font = QFont(FONT_TITLE);
    ltitle = new QLabel(this);
    ltitle->setGeometry(300, 5, 500, 50);
    ltitle->setStyleSheet(STYLE_SHEET_TITLE);
    ltitle->setFont(font);
    ltitle->setText(QString("Checking"));
    // ltitle->setText("<h2><i>Checking</i>"  "<font color=red>Device</font></h2>");

    pbar = new QProgressBar(this);
    pbar->setGeometry(200, 100, 400, 50);
    pbar->setMinimum(0);
    pbar->setMaximum(100);
    pbar->setValue(0);
    pbar->setFormat("");
    pbar->setStyleSheet("QProgressBar::chunk{background-color:rgb(200,0,0)}");
    pbar->setAlignment(Qt::AlignCenter);

    timer = new QTimer(this);
    timer->start(400);
//    connect(timer, &QTimer::timeout, this, &Endoveinous::showTime);
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    cpt= 0;
    idx_power = 0;
    power_write(idx_power);
}

autocheck::~autocheck()
{
    delete ui;
}

int autocheck::power_read(int idx)
{
    return 1;
}

void autocheck::power_write(int idx)
{

}


void autocheck::showTime()
{
    if ( idx_power < IDX_POWER_MAX )
    {
        int ret_power = power_read(idx_power);
        idx_power++;
        power_write(idx_power);

        char text[100];
        int val = (int)MIN(100.0, floor(100.0*idx_power/26));
        pbar->setValue(val);
        pbar->setTextVisible(true);
        sprintf(text, "checking %d %%", val);
        pbar->setFormat(QString(text));
    }
    else
    {
        delete timer;
        // delete this;
        close();
    }

    /*
    cpt++;
    if ( cpt %4 )
    {
        ltitle->setVisible(true);
    }
    else
    {
        ltitle->setVisible(false);
    }

    if ( cpt <= 50 )
    {
        char text[100];
        int val = (int)floor(100.0*cpt/50);
        pbar->setValue(val);
        pbar->setTextVisible(true);
        sprintf(text, "checking %d %%", val);
        pbar->setFormat(QString(text));
    }

    if ( cpt >= 75 )
    {
        delete timer;
        // delete this;
        close();
    }
    */
}

