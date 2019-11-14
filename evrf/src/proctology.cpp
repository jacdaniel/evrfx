#include "include/proctology.h"
#include "ui_proctology.h"

Proctology::Proctology(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Proctology)
{
    ui->setupUi(this);
}

Proctology::~Proctology()
{
    delete ui;
}
