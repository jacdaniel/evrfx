#ifndef MAINMENU_H
#define MAINMENU_H

#include <QPushButton>
#include <QLabel>
#include <QMainWindow>


#include "include/phlebology.h"
#include "include/proctology.h"
#include <include/param.h>
#include <./include/accessoryscan.h>

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent, Param *param);
    ~MainMenu();
    void set_patient_dir(QString *dir);

private:
    Ui::MainMenu *ui;
    QPushButton *bphlebology, *bproctology, *bCancel;
    QLabel *lphlebology, *lproctology;
    Phlebology *phlebology;
    Proctology *proctology;
    AccessoryScan *accessoryscan;
    QString *patient_dir;
    Param *param;


private slots:
    void handle_Trt_Phlebology();
    void handle_Trt_proctology();
    void handle_Trt_BCancel();
};

#endif // MAINMENU_H
