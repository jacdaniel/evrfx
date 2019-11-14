
#include <QString>
#include <QLabel>
#include <qdiriterator.h>


#include <config.h>
#include <util.h>
#include <accessoryscan.h>
#include "ui_accessoryscan.h"

// test git

AccessoryScan::AccessoryScan(QWidget *parent, int type, Param *param, dataio *dio) :
    QMainWindow(parent),
    ui(new Ui::AccessoryScan)
{
    ui->setupUi(this);
    this->param = param;
    this->dio = dio;
    this->id = 0;

    setGeometry(QRect(QPoint(0, 0), QSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)));

    QPixmap *pix = new QPixmap(MAIN_SCREEN_IMAGE2);
    QLabel *lab = new QLabel(this);
    lab->setGeometry(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    lab->setPixmap(*pix);

    this->treatment_type = type;

    QFont font = QFont(TITLE_LABEL_FONT_NAME, TITLE_LABEL_FONT_SIZE-10, TITLE_LABEL_FONT_WEIGHT);

    if ( type == ENDOVENOUS )
    {
        ltitle = new QLabel(param->get_label(IDX_ENDOVENOUS), this);
        ltitle->setGeometry(20, 5, 500, 50);
        ltitle->setFont(font);
        BUTTONIMAGE_CREATE_V2(bcr30, BTN_CR30,   150,  50, 400, 100, handle_Trt_CR30(), lcr30,  "CR30KAB",  font, 250, 10, 300, 50);
        BUTTONIMAGE_CREATE_V2(bcr40i, BTN_CR40i, 150, 200, 400, 100, handle_Trt_CR40i(), lcr40i, "CR40i", font, 250, 10, 300, 50);
        BUTTONIMAGE_CREATE_V2(bcr45i, BTN_CR45i, 150, 350, 400, 100, handle_Trt_CR45i(), lcr45i, "CR45i", font, 250, 10, 300, 50);
    }
    else if ( type == PROCTOLOGY )
    {
        ltitle = new QLabel(param->get_label(IDX_PROCTOLOGY), this);
        ltitle->setGeometry(20, 5, 500, 50);
        ltitle->setFont(font);
        BUTTONIMAGE_CREATE_V2(bhpr45i,  BTN_HPR45i,   150, 200, 400, 100, handle_Trt_HPR45i(),  lhpr45i,  "HPR45i",  font, 250, 10, 300, 50);
        BUTTONIMAGE_CREATE_V2(bfistula, BTN_HPR45i,   150, 200, 400, 100, handle_Trt_Fistula(), lfistula,  "Fistula",  font, 250, 10, 300, 50);
        bfistula->setVisible(false);
    }


    bcancel = new QPushButton(QIcon(CANCEL_IMAGE), "", this);
    bcancel->setGeometry(350+350, 400, 75, 75);
    bcancel->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    bcancel->setIcon(QIcon(CANCEL_IMAGE));
    bcancel->setIconSize(QSize(75, 75));
    connect(bcancel, SIGNAL (released()), this, SLOT (handle_Trt_Cancel()));

    // this->idmax = init_cbpatient();
}

AccessoryScan::~AccessoryScan()
{
    delete ui;
}


void AccessoryScan::handle_Trt_Cancel()
{
    dio->button_beep();
    close();
    delete this;
}

void AccessoryScan::handle_Trt_CR30()
{
    dio->button_beep();
    // this->id = get_id();
    endovenous = new Endoveinous(NULL_PTR, treatment_type, RUN_CR30i, param, this->dio, this->id);
    // endovenous = new Endoveinous();
    endovenous->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    endovenous->setGeometry(QRect(QPoint(0, 0), this->size()));
    endovenous->setParent(this);
    endovenous->show();
}

void AccessoryScan::handle_Trt_CR40i()
{
    dio->button_beep();
    // this->id = get_id();
    endovenous = new Endoveinous(NULL_PTR, treatment_type, RUN_CR40i, param, this->dio, this->id);
    // endovenous = new Endoveinous();
    endovenous->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    endovenous->setGeometry(QRect(QPoint(0, 0), this->size()));
    endovenous->setParent(this);
    endovenous->show();
}

void AccessoryScan::handle_Trt_CR45i()
{
    dio->button_beep();
    // this->id = get_id();
    endovenous = new Endoveinous(NULL_PTR, treatment_type, RUN_CR45i, param, this->dio, this->id);
    // endovenous = new Endoveinous();
    endovenous->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    endovenous->setGeometry(QRect(QPoint(0, 0), this->size()));
    endovenous->setParent(this);
    endovenous->show();
}


void AccessoryScan::handle_Trt_HPR45i()
{
    dio->button_beep();
    // this->id = get_id();
    endovenous = new Endoveinous(NULL_PTR, treatment_type, RUN_HPR45i, param, this->dio, this->id);
    // endovenous = new Endoveinous();
    endovenous->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    endovenous->setGeometry(QRect(QPoint(0, 0), this->size()));
    endovenous->setParent(this);
    endovenous->show();
}

void AccessoryScan::handle_Trt_Fistula()
{
    dio->button_beep();
    // this->id = get_id();
    endovenous = new Endoveinous(NULL_PTR, treatment_type, RUN_FISTULA, param, this->dio, this->id);
    // endovenous = new Endoveinous();
    endovenous->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    endovenous->setGeometry(QRect(QPoint(0, 0), this->size()));
    endovenous->setParent(this);
    endovenous->show();
}
