// #include "configwindow.h"
#include "ui_configwindow.h"

#include <QLabel>
#include <QDir>
#include <QMessageBox>


#include <config.h>
#include <util.h>
#include <fileio.h>
#include <configwindow.h>
#include <mainwindow.h>

ConfigWindow::ConfigWindow(QWidget *parent, Param *param, dataio *dio) :
    QMainWindow(parent),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);

    this->param = param;
    this->dio = dio;

    // QPixmap *pix = new QPixmap(CONFIG_SCREEN_IMAGE);
    QPixmap *pix = new QPixmap(MAIN_SCREEN_IMAGE2);
    QLabel *lab = new QLabel(this);
    lab->setGeometry(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    lab->setPixmap(*pix);

    QFont *font = new QFont(TITLE_LABEL_FONT_NAME, TITLE_LABEL_FONT_SIZE, TITLE_LABEL_FONT_WEIGHT);

    this->LTitle = new QLabel(lab);
    this->LTitle->setGeometry(0,0,MAIN_WINDOW_WIDTH,50);
    this->LTitle->setText(QString(param->get_label(IDX_CONFIGURATION)));
    this->LTitle->setFont(*font);

    llogolanguage = new QLabel(this);
    llogolanguage->setGeometry(200, 100, 75, 75);
    QPixmap *pix2 = new QPixmap(LOGO_LANGUAGE);
    llogolanguage->setPixmap(*pix2);


    this->cblanguage = new QComboBox(this);
    this->cblanguage->setGeometry(295, 105, 200, 50);
    this->cblanguage->setFont(QFont(TITLE_LABEL_FONT_NAME, 15, TITLE_LABEL_FONT_WEIGHT));
    this->cblanguage->addItem(QString("English"));
    // this->cblanguage->addItem(QString("Français"));
    this->cblanguage->addItem(QString::fromUtf8("Français"));
    this->cblanguage->addItem(QString("Deutsch"));
    this->cblanguage->addItem(QString::fromUtf8("Português"));

    // BUTTONIMAGE_CREATE_PARENT(buserinfo, gbhelpmenu,      "./data/user_info.jpg", 5, 170, 60, 60, handle_Trt_UserInfo())

    BUTTONIMAGE_CREATE(bpatient, PATIENT75_IMAGE, 200, 200, 75, 75, handle_trt_Bpatient())
    BUTTONIMAGE_CREATE(bupgrade, UPGRADE_IMAGE,   200, 300, 75, 75, handle_trt_upgrade())

    // BUTTONIMAGE_CREATE(bok, VALID_IMAGE, 640, 400, 75, 75, handle_trt_Bok())
    BUTTONIMAGE_CREATE(bCancel, CANCEL_IMAGE, 720, 400, 75, 75, handle_trt_Bok())

    init();
}

ConfigWindow::~ConfigWindow()
{
    delete ui;
}

void ConfigWindow::init()
{
    if ( !file_exist(FILE_PARAM) )
        return ;

    FILE *pFile = NULL_PTR;
    pFile = fopen(FILE_PARAM, "r");
    fgets(this->label_filename, 255, pFile);
    this->label_filename[strlen(this->label_filename)-1] = '\0';
    fclose(pFile);

    if ( strcmp(this->label_filename, FILE_TXT_EN) == 0 )
        this->cblanguage->setCurrentIndex(IDX_FILE_TXT_EN);
    else if ( strcmp(this->label_filename, FILE_TXT_FR) == 0 )
        this->cblanguage->setCurrentIndex(IDX_FILE_TXT_FR);
    else if ( strcmp(this->label_filename, FILE_TXT_NL) == 0 )
        this->cblanguage->setCurrentIndex(IDX_FILE_TXT_NL);
    else if ( strcmp(this->label_filename, FILE_TXT_PT) == 0 )
        this->cblanguage->setCurrentIndex(IDX_FILE_TXT_PT);
    else
        this->cblanguage->setCurrentIndex(IDX_FILE_TXT_EN);
}


void ConfigWindow::handle_Trt_BCancel()
{
    close();
    // delete this;
}

void ConfigWindow::handle_trt_Bok()
{
    int idx = this->cblanguage->currentIndex();
    char *txt = NULL_PTR, txt2[255];
    FILE *pFile = NULL_PTR;
    switch ( idx )
    {
      case IDX_FILE_TXT_EN : txt = (char*)FILE_TXT_EN; break;
      case IDX_FILE_TXT_FR : txt = (char*)FILE_TXT_FR; break;
      case IDX_FILE_TXT_NL : txt = (char*)FILE_TXT_NL; break;
      case IDX_FILE_TXT_PT : txt = (char*)FILE_TXT_PT; break;
      default: txt = (char*)FILE_TXT_EN; break;
    }
    strcpy(txt2, txt);
    strcat(txt2, "\n");
    pFile = fopen(FILE_PARAM, "wb");
    fputs(txt2, pFile);
    fclose(pFile);

    MainWindow* p = (MainWindow*)this->parent();
    p->init();

    close();
}

void ConfigWindow::handle_trt_upgrade()
{
    dio->button_beep();
    QString filename = get_usb_file(MEDIA_ROOT_FILENAME, SCRIPT_UPDATE_FILENAME);

    if ( filename.isNull() || filename.isEmpty() )
    {        
        filename = get_usb_file(MEDIA_ROOT_DESKTOP_FILENAME, SCRIPT_UPDATE_FILENAME);

        if ( filename.isNull() || filename.isEmpty() )
        {
            QMessageBox::question(this, "Update", "There is no update key ?", QMessageBox::Ok);
        return;
        }
    }

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Update", "Do you really want to update the software ?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        exec_sh_cmd(filename);
        QApplication::quit();
    }
}

void ConfigWindow::handle_trt_Bpatient()
{    
    patientlist = new PatientList(NULL_PTR, param);
    patientlist->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    patientlist->setGeometry(QRect(QPoint(0, 0), this->size()));
    patientlist->setParent(this);
    // patientlist->setWindowModality(Qt::ApplicationModal);
    patientlist->show();    
}

