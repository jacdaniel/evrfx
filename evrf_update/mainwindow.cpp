
#include <QDir>
#include <QLabel>
#include <QPixmap>
#include <QTimer>

#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    setGeometry(0, 0, 800, 480);

    QPixmap *pix = new QPixmap("./data/window_main.jpg");
    QLabel *lab = new QLabel(this);
    lab->setGeometry(0, 0, 800, 480);
    lab->setPixmap(*pix);

    cpt_timer = 0;
    timer = new QTimer(this);
    timer->start(100);
//    connect(timer, &QTimer::timeout, this, &Endoveinous::showTime);
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


char* MainWindow::get_update_masterfile()
{
    char *out = nullptr;
    FILE *pFile = nullptr;
    QDir currentDir("/media/linux");
    currentDir.setFilter(QDir::Dirs);
    QStringList entries = currentDir.entryList();
    for( QStringList::ConstIterator entry=entries.begin(); entry!=entries.end(); ++entry )
    {
        //std::cout << *entry << std::endl;
        QString dirname = *entry;
        if(dirname != tr(".") && dirname != tr(".."))
        {
            QString f = "/media/linux/" + dirname + "/evrf_update/update_run.sh";
            pFile = fopen(f.toStdString().c_str(), "r");
            if ( pFile )
            {
                fclose(pFile);
                out = (char*)calloc(1000, sizeof(char));
                sprintf(out, "/media/linux/%s/evrf_update/update_run.sh", dirname.toStdString().c_str());
            }
         }
     }
    return out;
}

void MainWindow::update_run()
{
    char cmd[1000];
    // char *src_file = "/home/linux/fc/test_src/";
    // char *dst_file = "/home/linux/fc/test_dst/";
    // char cmd[1000];
    // sprintf(cmd, "cp %s*.* %s.", src_file, dst_file);


    // char *cmd = "sh /home/linux/fc/test_src/update_run.sh";
    // system(cmd);

    /*
    char *f = get_update_masterfile();
    if ( f )
    {
        sprintf(cmd, "sh \"%s\"", f);
        system(cmd);
        // chdir(cmd);
        // system("sh update_run.sh");
    }
    */
}


void MainWindow::showTime()
{
    cpt_timer++;
    if( cpt_timer >= 50 )
    {
        update_run();
        // this->close();
        system("reboot");
        // ((MainWindow*)this->parent())->close();
    }
}
