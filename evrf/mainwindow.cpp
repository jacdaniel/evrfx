#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QDir>
#include <QFileInfo>
#include <QtDebug>


/*
 * #include <QSql>
#include <QSqlQuery>
*/

#include <stdio.h>

#include <include/param.h>
#include <include/dataio.h>
#include "include/config.h"
#include "include/util.h"
#include "./src/powerqualibration.h"
#include "include/patientlist.h"
#include "src/autocheck.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->dio = new dataio();

    this->setWindowFlags(WINDOW_STYLE);
    setGeometry(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);

    // param = NULL_PTR;
    param = new Param((char*)PARAM_FILENAME);

    QPixmap *pix = new QPixmap(MAIN_SCREEN_IMAGE);
    QLabel *lab = new QLabel(this);
    lab->setGeometry(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    lab->setPixmap(*pix);

    QFont *font = new QFont(TITLE_LABEL_FONT_NAME, TITLE_LABEL_FONT_SIZE, TITLE_LABEL_FONT_WEIGHT);

    BUTTONIMAGE_CREATE_V2(bphlebology, BTN_PHLEBOLOGY,   0, 200, MAIN_WINDOW_WIDTH-400, 150, handle_Trt_Phlebology(), lphlebology, param->get_label(IDX_PHLEBOLOGY), *font, 128, 50, 300, 50)
    BUTTONIMAGE_CREATE_V2(bproctology, BTN_PROCTOLOGY, 400, 200, MAIN_WINDOW_WIDTH-400, 150, handle_Trt_proctology(), lproctology, param->get_label(IDX_PROCTOLOGY), *font,  60, 50, 300, 50)

    // BUTTONIMAGE_CREATE(bdebug, SHUTDOWN_IMAGE, 0, 0, 75, 75, handle_Trt_BDebug())

    // BUTTONIMAGE_CREATE(bPatient,      PATIENT_IMAGE,      10, 100, 400, 128, handle_Trt_Patient())
    // BUTTONIMAGE_CREATE(bDirectAccess, DIRECTACCESS_IMAGE, 10, 250, 400, 128, handle_Trt_DirectAccess())

    // QFont *font = new QFont(TITLE_LABEL_FONT_NAME, TITLE_LABEL_FONT_SIZE, TITLE_LABEL_FONT_WEIGHT);

    /*
    lPatient = new QLabel("Patient");
    lPatient->setGeometry(128, 50, 200, 50);
    QFont f = lPatient->font();
    f.setPointSize(35);
    f.setBold(true);
    lPatient->setFont(*font);
    lPatient->setParent(bPatient);

    lDirectaccess = new QLabel("Direct");
    lDirectaccess->setGeometry(128, 50, 200, 50);
    f = lDirectaccess->font();
    f.setPointSize(35);
    f.setBold(true);
    lDirectaccess->setFont(*font);
    lDirectaccess->setParent(bDirectAccess);
    */

    BUTTONIMAGE_CREATE(bexit,   SHUTDOWN_IMAGE, 720, 400, 75, 75, handle_Trt_Exit())
    BUTTONIMAGE_CREATE(bConfig, CONFIG_IMAGE,   600, 400, 75, 75, handle_Trt_BConfig())

#ifdef DEBUG_POWER_QUALIBRATION
    BUTTONIMAGE_CREATE(bPowerQualibration, CONFIG_IMAGE,   0, 0, 75, 75, handle_Trt_BPowerQualibration())
#endif

    lversion = new QLabel("version 1.01k", this);
    lversion->setGeometry(5, MAIN_WINDOW_HEIGHT-20, 150, 15);
    init();
    test2();

    /*
    autocheck *au = new autocheck();
    au->setParent(this);
    au->setVisible(true);
    au->setModal(true);
    au->setGeometry(QRect(QPoint(0, 0), this->size()));
    au->show();
    */



    // autotest();
    // test();
}

MainWindow::~MainWindow()
{
    // delete lPatient;
    // delete bPatient;
    // delete bDirectAccess;
    // delete lDirectaccess;
    delete ui;
}

void MainWindow::init()
{
    DELETE(this->param);
    param = new Param((char*)PARAM_FILENAME);

    this->lphlebology->setText(param->get_label(IDX_PHLEBOLOGY));
    this->lproctology->setText(param->get_label(IDX_PROCTOLOGY));
}



void MainWindow::handle_Trt_BConfig()
{
    dio->button_beep();
    pConfigWindow = new ConfigWindow(NULL_PTR, param, this->dio);
    pConfigWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    pConfigWindow->setGeometry(QRect(QPoint(0, 0), this->size()));
    // pConfigWindow->setStyleSheet("background-color: black;");
    pConfigWindow->setParent(this);
    pConfigWindow->show();
}

void MainWindow::handle_Trt_Phlebology()
{
    dio->button_beep();
    phlebology = new Phlebology(NULL_PTR, param, dio);
    phlebology->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    phlebology->setGeometry(QRect(QPoint(0, 0), this->size()));
    phlebology->setParent(this);
    phlebology->show();
}

void MainWindow::handle_Trt_proctology()
{
    dio->button_beep();
    accessoryscan = new AccessoryScan(NULL_PTR, PROCTOLOGY, param, dio);
    accessoryscan->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    accessoryscan->setGeometry(QRect(QPoint(0, 0), this->size()));
    accessoryscan->setParent(this);
    accessoryscan->show();
}

void MainWindow::handle_Trt_BDebug()
{
    /*
  dio = new dataio();
  dio->set_hf_en(1);
  */
}

void MainWindow::handle_Trt_Exit()
{
    dio->button_beep();
    this->close();
    // delete this;
}




// *********************************************************
// auto test
// *********************************************************

const int AUTOTEST_DIGITAl_POTENTIOMETER_VALUE[] =
{
255, 245, 244, 237, 232, 225, 219, 212, 205, 198, 190, 182, 173, 162, 153, 144, 132, 122, 111, 96, 84, 67, 53, 33, 17, 0
};


void MainWindow::ht_program(int type, int val)
{
#ifdef _GPIO_
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
        dio->set_hf_en(1);
        delay(1);
    }
#else
    printf("Program HT\n");
#endif
}

void MainWindow::catheter_status_enable(int val)
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

void MainWindow::autotest()
{
    catheter_status_enable(0);
    FILE *pFile = fopen("./autotest.txt", "w");

    ht_program(1, 0);
    for (int i=0; i<25; i++)
    {
        ht_program(1, AUTOTEST_DIGITAl_POTENTIOMETER_VALUE[i]);
        int ret = dio->spi_read(0);
        fprintf(pFile, "%d %d\n", AUTOTEST_DIGITAl_POTENTIOMETER_VALUE[i], ret);
    }
    ht_program(0, 0);
    fclose(pFile);
}


void MainWindow::test()
{
    /*
    foreach (const QStorageInfo &storage, QStorageInfo::mountedVolumes()) {

       qDebug() << storage.rootPath();
       if (storage.isReadOnly())
           qDebug() << "isReadOnly:" << storage.isReadOnly();

       qDebug() << "name:" << storage.name();
       qDebug() << "fileSystemType:" << storage.fileSystemType();
       qDebug() << "size:" << storage.bytesTotal()/1000/1000 << "MB";
       qDebug() << "availableSize:" << storage.bytesAvailable()/1000/1000 << "MB";
    }
    */

    // QDir *q;// new QDir();
    // QFileInfoList l = q->drives();



      // foreach( QFileInfo drive, QDir::drives() )
      // {
          // qDebug() << "Drive: " << drive.absolutePath();

/*             QDir dir = drive.dir();
             dir.setFilter( QDir::Dirs );

             foreach( QFileInfo rootDirs, dir.entryInfoList() )
               qDebug() << "  " << rootDirs.fileName();
*/
      // }

    // system("/home/linux/fc/build-evrf_update-Desktop-Debug/evrf_update");
    // dio->button_beep();
    // this->close();
    // delete this;
}




// ==========================================================================================

static int array_spi_test[] = {1,1,0,1, 1,1,0,0, 1,1,1,1, 0,0,0,1};

static int test2_spi_ht_read()
{
    int out = 0x00;


    for (int i=0; i<16; i++)
    {
        if ( array_spi_test[i] == 1 )
        {
            out++;
        }
        else
        {

        }

        if ( i != 15 )
            out = out<<1;
    }

    return out;

}

void MainWindow::test2()
{
    int i = test2_spi_ht_read();
    printf("%d\n", i);
}


void MainWindow::handle_Trt_BPowerQualibration()
{
    PowerQualibration *p = new PowerQualibration(NULL_PTR, this->dio);
    p->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    p->setGeometry(QRect(QPoint(0, 0), this->size()));
    // pConfigWindow->setStyleSheet("background-color: black;");
    p->setParent(this);
    p->show();
}
