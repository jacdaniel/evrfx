#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

#include "include/configwindow.h"
// #include "include/patientcreate.h"
#include "include/patientlist.h"
#include "include/param.h"
#include "include/phlebology.h"
#include <./include/accessoryscan.h>
#include "./include/dataio.h"
#include "include/mainmenu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();
    void autotest();
    void ht_program(int type, int val);
    void catheter_status_enable(int val);
    void test();
    void test2();

private:
    Ui::MainWindow *ui;
    QPushButton *bConfig, /**bPatient, *bDirectAccess,*/ *bdebug, *bexit, *bphlebology, *bproctology, *bPowerQualibration;
    ConfigWindow *pConfigWindow;
    PatientList *patientlist;
    MainMenu *pMainMenu;
    QLabel *lphlebology, *lproctology, *lversion; //*lPatient, *lDirectaccess;
    Param *param;
    Phlebology *phlebology;
    AccessoryScan *accessoryscan;
    dataio *dio;

private slots:
    void handle_Trt_BConfig();
    // void handle_Trt_Patient();
    // void handle_Trt_DirectAccess();
    void handle_Trt_Phlebology();
    void handle_Trt_proctology();

    void handle_Trt_BDebug();
    void handle_Trt_Exit();

    void handle_Trt_BPowerQualibration();

};

#endif // MAINWINDOW_H
