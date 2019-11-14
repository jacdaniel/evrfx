
#include "include/config.h"
#include "include/rfidreader.h"
#include "ui_rfidreader.h"



RFIDReader::RFIDReader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RFIDReader)
{
    ui->setupUi(this);

    QPixmap *pix = new QPixmap(LOGO_RFID);
    lrfidlogo = new QLabel(this);
    lrfidlogo->setGeometry(10, 10, 200, 200);
    lrfidlogo->setPixmap(*pix);

}

RFIDReader::~RFIDReader()
{
    delete ui;
}
