
#include <QLabel>
#include <QStandardItemModel>
#include <QMessageBox>

#include <string.h>
#include <stdio.h>

#include <fileio.h>
#include "include/config.h"
#include "include/util.h"
#include "./include/patient.h"
#include "./include/database.h"
#include "include/patientlist.h"
#include "./include/treatmentdetail.h"
#include "ui_patientlist.h"

PatientList::PatientList(QWidget *parent, Param *param) :
    QMainWindow(parent),
    ui(new Ui::PatientList)
{
    ui->setupUi(this);
    // setWindowModality(Qt::ApplicationModal);


    this->param = param;
    // this->List.clear();
    this->model = NULL_PTR;

    QPixmap *pix = new QPixmap(MAIN_SCREEN_IMAGE2);
    QLabel *lab = new QLabel(this);
    lab->setGeometry(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    lab->setPixmap(*pix);

    tablepatient = new QTableView();
    tablepatient->setParent(this);
    tablepatient->setGeometry(50, 70, 600+55, 310);
    tablepatient->show();

    // tablepatient->setModel(model);

    tablepatient->verticalHeader()->hide();
    tablepatient->setSelectionBehavior(QAbstractItemView::SelectRows);
    tablepatient->setColumnWidth(0, 250);
    tablepatient->setColumnWidth(1, 250);
    tablepatient->setColumnWidth(2, 250);
    // tablepatient->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tablepatient->setFont(QFont("Times",20));
    tablepatient->setSelectionMode(QAbstractItemView::SingleSelection);
    // tablepatient->setDisabled(true);
    // tablepatient->(Qt::ItemIsEditable);
    // tablepatient->setTabKeyNavigation(true);
    tablepatient->horizontalHeader()->hide();
    // QScrollBar *b = tablepatient->verticalScrollBar();
    // b->setMaximum(100);
    tablepatient->setColumnWidth(0, tablepatient->width());
    // tablepatient->resizeColumnsToContents();


    BUTTONIMAGE_CREATE(bdatabase, DATABASE_IMAGE,   10, 400, 75, 75, handle_Trt_dbupload())
    BUTTONIMAGE_CREATE(bsuppress, ERASE_IMAGE,      90, 400, 75, 75, handle_Trt_Suppress())

    BUTTONIMAGE_CREATE(bok,       VALID_IMAGE,     600, 400, 75, 75, handle_Trt_Ok())
    BUTTONIMAGE_CREATE(bcancel,   CANCEL_IMAGE,    720, 400, 75, 75, handle_Trt_Cancel())

    BUTTONIMAGE_CREATE(bup,       ARROWUP_IMAGE,   690+20,  70, 75, 75, handle_Trt_Up())
    BUTTONIMAGE_CREATE(bdown,     ARROWDOWN_IMAGE, 690+20, 300, 75, 75, handle_Trt_Down())

    this->page_size = 10;
    this->idx_page = 0;
    this->user_db_nbre = database_user_nbre(USER_DATABASE_FILENAME);
    this->page_nbre = (this->user_db_nbre - 1) / this->page_size + 1;
    init();
    data_display(this->user_db_nbre, this->page_size, this->idx_page);
}

PatientList::~PatientList()
{
    delete ui;
}

void PatientList::init()
{

}


static void data_display_get_index(long idx_page, long page_nbre, long db_size, long page_size, long *idx, long *nbre)
{
    *idx = idx_page * page_size;
    *nbre = page_size;
    if ( idx_page >= page_nbre -1 )
    {
        *nbre = db_size - idx_page * page_size;
    }
}


const char *CATETHER_TYPE[][10] = {
    {"", "CR45i", "CR40i", "CR30i"},
    {"TRANS."},
    {"HPR45i"}
};

void PatientList::data_display(long db_size, long page_size, long idx_page)
{
    long idx1, nbre;

    data_display_get_index(idx_page, this->page_nbre, db_size, page_size, &idx1, &nbre);
    USER_DATABASE_PATIENT *data = (USER_DATABASE_PATIENT*)calloc(nbre, sizeof(USER_DATABASE_PATIENT));
    USER_DATABASE_PATIENT *p = NULL_PTR;
    database_user_read(USER_DATABASE_FILENAME, idx1, nbre, data);

    DELETE(this->model);
    this->model = new QStandardItemModel(9, 4, this); //2 Rows and 3 Columns
    QStandardItem *item  = NULL_PTR;
    for (unsigned int i=0; i<nbre; i++)
    {
        p = &data[i];

        item = new QStandardItem(get_date_yyyy_mm_dd_from_compactdate(p->date));
        this->model->setItem(i,0,item);

        item = new QStandardItem(QString(p->name));
        this->model->setItem(i,1,item);

        item = new QStandardItem(QString(p->ceap));
        this->model->setItem(i,2,item);

        item = new QStandardItem(QString(CATETHER_TYPE[p->treatment_type][p->treatment]));
        this->model->setItem(i,3,item);
    }
    tablepatient->setModel(this->model);
    tablepatient->setColumnWidth(0, 150);
    tablepatient->setColumnWidth(1, 250);
    tablepatient->setColumnWidth(2, 100);
    tablepatient->setColumnWidth(3, 150);
    tablepatient->selectRow(0);
    FREE(data)
}

// Trt
void PatientList::handle_Trt_Edit()
{
    /*
    int id =
    patientcreate = new PatientCreate();
    patientcreate->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    patientcreate->setGeometry(QRect(QPoint(0, 0), this->size()));
    patientcreate->setParent(this);
    patientcreate->show();
    */
}

void PatientList::handle_Trt_Suppress()
{
    int reply = QMessageBox::question(this, "Erase", "Erase database ?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        remove(USER_DATABASE_FILENAME);
        this->idx_page = 0;
        this->user_db_nbre = 0;
        this->page_nbre = 1;
        data_display(0, 10, 0);
    }
}

void PatientList::handle_Trt_Cancel()
{
    close();
    // delete this;
}

static int get_selected_index(long idx, long page_size, long idx_page, long user_db_nbre)
{
    long ret;
    ret = page_size*idx_page + idx;
    if ( ret >= user_db_nbre )
    {
        ret = -1;
    }
    return ret;
}

void PatientList::handle_Trt_Ok()
{
    // close();

    QModelIndexList selectedList = tablepatient->selectionModel()->selectedRows();
    int idx = 0;
    if ( selectedList.count() == 1 )
    {
        idx = selectedList.at(0).row();
    }
    int db_idx = get_selected_index(idx, this->page_size, this->idx_page, user_db_nbre );
    if ( db_idx < 0 ) return;
    USER_DATABASE_PATIENT data;
    database_user_read((char*)USER_DATABASE_FILENAME, db_idx, 1, &data);
    TreatmentDetail *t = new TreatmentDetail(NULL, this->param, &data);
    t->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    t->setGeometry(QRect(QPoint(0, 0), this->size()));
    t->setParent(this);
    t->show();
}

void PatientList::handle_Trt_Up()
{
    if ( this->idx_page )
    {
        this->idx_page--;
        data_display(this->user_db_nbre, this->page_size, this->idx_page);
    }
}

void PatientList::handle_Trt_Down()
{
    if ( this->idx_page < this->page_nbre - 1 )
    {
        this->idx_page++;
        data_display(this->user_db_nbre, this->page_size, this->idx_page);
    }
}


/*
void PatientList::QPaintEvent(const QRegion &paintRegion)
{

}
*/

void PatientList::handle_Trt_dbupload()
{
    // dio->button_beep();

    QMessageBox::StandardButton reply = QMessageBox::question(this, "upload", "Do you really want to upload database ?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::No)
    {
        return;
    }

    QString dst_filename = get_usb_drive(MEDIA_ROOT_FILENAME);
    if ( dst_filename.isEmpty() || dst_filename.isNull() )
    {
        QMessageBox::question(this, "Upload", "There is no usb key ?", QMessageBox::Ok);
        return;
    }

    dst_filename = QString("\"") + dst_filename + QString("/dbm.tar.gz") + QString("\"");
    QString cmd = QString("tar zcvf ") + dst_filename + QString(" db/dbm.bin");
    int ret = exec_cmd(cmd);
}







