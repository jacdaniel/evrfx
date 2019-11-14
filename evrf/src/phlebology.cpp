
#include <QLabel>
#include <QDir>
#include "include/config.h"

#include <include/util.h>
#include "include/phlebology.h"
#include "ui_phlebology.h"

Phlebology::Phlebology(QWidget *parent, Param *param, dataio *dio) :
    QMainWindow(parent),
    ui(new Ui::Phlebology)
{
    ui->setupUi(this);
    this->param = param;
    this->dio = dio;
    // this->id = id;

    setGeometry(QRect(QPoint(0, 0), QSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)));

    QPixmap *pix = new QPixmap(MAIN_SCREEN_IMAGE2);
    QLabel *lab = new QLabel(this);
    lab->setGeometry(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    lab->setPixmap(*pix);

    QFont *font = new QFont(TITLE_LABEL_FONT_NAME, TITLE_LABEL_FONT_SIZE, TITLE_LABEL_FONT_WEIGHT);

    BUTTONIMAGE_CREATE_V2(bendoveinous, BTN_ENDOVENOUS, 100, 100, MAIN_WINDOW_WIDTH-200, 150, handle_Trt_Endoveinous(), lendovenous, param->get_label(IDX_ENDOVENOUS), *font, 128, 50, 300, 50)
    BUTTONIMAGE_CREATE_V2(btranscutaneous, BTN_TRANSCUTANEOUS, 100, 250, MAIN_WINDOW_WIDTH-200, 150, handle_Trt_Trancutaneous(), ltranscutaneous, param->get_label(IDX_TRANSCUTANEOUS), *font, 128, 50, 310, 50)
    BUTTONIMAGE_CREATE(bCancel, CANCEL_IMAGE, 720, 400, 75, 75, handle_Trt_BCancel())

}

Phlebology::~Phlebology()
{
    delete ui;
}

/*
QString Phlebology::get_directoty_name()
{
    return QDir::currentPath() + "/patient/";
}
*/

/*
void Phlebology::set_patient_dir(QString *dir)
{
    this->patient_dir = dir;
}
*/

void Phlebology::handle_Trt_Endoveinous()
{
    /*
    endoveinous = new Endoveinous();
    endoveinous->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    endoveinous->setGeometry(QRect(QPoint(0, 0), this->size()));
    endoveinous->setParent(this);
    endoveinous->show();
    */
    dio->button_beep();
    accessoryscan = new AccessoryScan(NULL_PTR, ENDOVENOUS, param, this->dio);
    accessoryscan->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    accessoryscan->setGeometry(QRect(QPoint(0, 0), this->size()));
    accessoryscan->setParent(this);
    accessoryscan->show();
}

void Phlebology::handle_Trt_Trancutaneous()
{
    dio->button_beep();
    endoveinous = new Endoveinous(NULL_PTR, TRANSCUTANEOUS, 0, param, this->dio, -1);
    endoveinous->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    endoveinous->setGeometry(QRect(QPoint(0, 0), this->size()));
    endoveinous->setParent(this);
    endoveinous->show();
    // endoveinous->set_protocole_type(TRANSCUTANEOUS);
}

void Phlebology::handle_Trt_BCancel()
{
    dio->button_beep();
    delete this;
}
