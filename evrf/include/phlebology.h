#ifndef PHLEBOLOGY_H
#define PHLEBOLOGY_H

#include <QPushButton>
#include <QLabel>
#include <QMainWindow>

#include <include/endoveinous.h>
#include <include/param.h>
#include <include/dataio.h>
#include <include/accessoryscan.h>

namespace Ui {
class Phlebology;
}

class Phlebology : public QMainWindow
{
    Q_OBJECT

public:
    explicit Phlebology(QWidget *parent, Param *param, dataio *dio);
    ~Phlebology();
    // void set_patient_dir(QString *dir);

private:
    Ui::Phlebology *ui;
    QPushButton *bendoveinous, *btranscutaneous, *bCancel;
    QLabel *lendovenous, *ltranscutaneous;
    Endoveinous *endoveinous;
    AccessoryScan *accessoryscan;
    QString *patient_dir;
    Param *param;
    // int id;
    // QString get_directoty_name();
    dataio *dio;

private slots:
    void handle_Trt_Endoveinous();
    void handle_Trt_Trancutaneous();
    void handle_Trt_BCancel();
};

#endif // PHLEBOLOGY_H
