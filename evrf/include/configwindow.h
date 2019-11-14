#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>

#include <include/dataio.h>
#include "./include/patientlist.h"
#include "./include/param.h"

namespace Ui {
class ConfigWindow;
}

class ConfigWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigWindow(QWidget *parent, Param *param, dataio *dio);
    ~ConfigWindow();

private:
    Ui::ConfigWindow *ui;
    QLabel *LTitle, *llanguage;
    QPushButton *bCancel, *bok, *bpatient, *bupgrade;
    QComboBox *cblanguage;
    QLabel *llogolanguage;

    Param *param;
    dataio *dio;
    PatientList *patientlist;
    void init();
    char label_filename[255];
    // char* get_update_masterfile();

private slots:
    void handle_Trt_BCancel();
    void handle_trt_Bok();
    void handle_trt_Bpatient();
    void handle_trt_upgrade();
};

#endif // CONFIGWINDOW_H
