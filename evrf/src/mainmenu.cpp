
#include <QPushButton>
#include <QLabel>

#include "include/util.h"
#include "include/param.h"
#include "include/config.h"

#include "include/mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent, Param *param) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    this->param = param;

    setGeometry(QRect(QPoint(0, 0), QSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)));

    QPixmap *pix = new QPixmap(MAIN_SCREEN_IMAGE2);
    QLabel *lab = new QLabel(this);
    lab->setGeometry(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    lab->setPixmap(*pix);

    QFont *font = new QFont(TITLE_LABEL_FONT_NAME, TITLE_LABEL_FONT_SIZE, TITLE_LABEL_FONT_WEIGHT);

    BUTTONIMAGE_CREATE_V2(bphlebology, BTN_PHLEBOLOGY, 100, 100, MAIN_WINDOW_WIDTH-200, 150, handle_Trt_Phlebology(), lphlebology, param->get_label(IDX_PHLEBOLOGY), *font, 128, 50, 300, 50)
    BUTTONIMAGE_CREATE_V2(bproctology, BTN_PROCTOLOGY, 100, 300, MAIN_WINDOW_WIDTH-200, 150, handle_Trt_proctology(), lphlebology, param->get_label(IDX_PROCTOLOGY), *font, 128, 50, 300, 50)
    BUTTONIMAGE_CREATE(bCancel, CANCEL_IMAGE, 720, 400, 75, 75, handle_Trt_BCancel())
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::set_patient_dir(QString *dir)
{
    this->patient_dir = dir;
}


void MainMenu::handle_Trt_Phlebology()
{
    /*
    phlebology = new Phlebology(NULL_PTR, param);
    phlebology->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    phlebology->setGeometry(QRect(QPoint(0, 0), this->size()));
    phlebology->setParent(this);
    phlebology->show();
    */
}

void MainMenu::handle_Trt_proctology()
{
    /*
    accessoryscan = new AccessoryScan(NULL_PTR, PROCTOLOGY, param);
    accessoryscan->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    accessoryscan->setGeometry(QRect(QPoint(0, 0), this->size()));
    accessoryscan->setParent(this);
    accessoryscan->show();
    */
}

void MainMenu::handle_Trt_BCancel()
{
    delete this;
}
