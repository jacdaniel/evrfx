#ifndef ACCESSORYSCAN_H
#define ACCESSORYSCAN_H

#include <QLineEdit>
#include <QPushButton>
#include <QMainWindow>
#include <QComboBox>

#include <./include/param.h>
#include <include/dataio.h>
#include <./include/endoveinous.h>

namespace Ui {
class AccessoryScan;
}

class AccessoryScan : public QMainWindow
{
    Q_OBJECT

public:
    explicit AccessoryScan(QWidget *parent = nullptr);
    // explicit AccessoryScan(QWidget *parent, int type);
    explicit AccessoryScan(QWidget *parent, int type, Param*param, dataio *dio);
    ~AccessoryScan();

private:
    Ui::AccessoryScan *ui;
    QLineEdit *le_tagid, *le_usenbre, *le_treatment;
     QComboBox *cbpatient;
    QPushButton *bcancel, *bcr30, *bcr40i, *bcr45i, *bhpr45i, *bfistula;
    Endoveinous *endovenous;
    int treatment_type;
    QString *patient_dir;
    QComboBox *cbprobe, *cbuse;
    QLabel *lcr30, *lcr40i, *lcr45i, *ltitle, *lhpr45i, *lfistula;
    Param *param;
    dataio *dio;
    int id;

private slots:
    void handle_Trt_Cancel();
    void handle_Trt_CR30();
    void handle_Trt_CR40i();
    void handle_Trt_CR45i();
    void handle_Trt_HPR45i();
    void handle_Trt_Fistula();
};

#endif // ACCESSORYSCAN_H
