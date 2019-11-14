#include "include/protocol.h"
#include "include/config.h"
#include "include/util.h"
#include "ui_protocol.h"

#include <QLabel>

Protocol::Protocol(QWidget *parent, int treatment_type, int treatment) :
    QMainWindow(parent),
    ui(new Ui::Protocol)
{
    ui->setupUi(this);
    setGeometry(QRect(QPoint(0, 0), QSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)));
//     QFont *font = new QFont(TITLE_LABEL_FONT_NAME, TITLE_LABEL_FONT_SIZE-10, TITLE_LABEL_FONT_WEIGHT);
    // QRegion region( QRect( 0, 0, 68, 68 ), QRegion:: Ellipse ); // Création d'une ellipse de 50px de diamètre

    QPixmap *pix = new QPixmap(MAIN_SCREEN_IMAGE2);
    QLabel *lab = new QLabel(this);
    lab->setGeometry(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    lab->setPixmap(*pix);

    QPixmap *pix2 = NULL_PTR;
    if ( treatment_type == ENDOVENOUS)
    {
        if ( treatment == RUN_CR30i )
            pix2 = new QPixmap(PROTOCOL_ENDOVENOUS_CR30);
        else if ( treatment == RUN_CR45i )
            pix2 = new QPixmap(PROTOCOL_ENDOVENOUS_CR45);
    }
    else if ( treatment_type == TRANSCUTANEOUS )
    {
        pix2 = new QPixmap(PROTOCOL_TRANSCUTANEOUS);
    }
    else if ( treatment_type == PROCTOLOGY )
    {
        if ( treatment == RUN_HPR45i )
            pix2 = new QPixmap(PROTOCOL_PROCTOLOGY_HPR45i);
    }
    lab_info = new QLabel(this);
    lab_info->setGeometry(0, 10, 800, 350);
    if ( pix2 != NULL_PTR)
        lab_info->setPixmap(*pix2);

    BUTTONIMAGE_CREATE(bquit, CANCEL_IMAGE, 720, 400, 75, 75, handle_Trt_Exit())
}

Protocol::~Protocol()
{
    delete ui;
}


void Protocol::handle_Trt_Exit()
{
    close();
}
