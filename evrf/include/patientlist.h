#ifndef PATIENTLIST_H
#define PATIENTLIST_H

#include <QTableView>
#include <QPushButton>
#include <QMainWindow>
#include <QStandardItemModel>

#include <include/mainmenu.h>
#include <include/param.h>


namespace Ui {
class PatientList;
}

class PatientList : public QMainWindow
{
    Q_OBJECT

public:
    explicit PatientList(QWidget *parent, Param *param);
    ~PatientList();
    void QPaintEvent(const QRegion &paintRegion);

    void init();
    void data_display(long db_size, long page_size, long idx_page);
    QTableView *tablepatient;

private:
    QPushButton *bcancel, *bok, *bedit, *bsuppress, *bup, *bdown, *bdatabase;

    Ui::PatientList *ui;
    MainMenu *pmainmenu;
    Param *param;
    QStandardItemModel *model;    

    long page_size, user_db_nbre, idx_page, page_nbre;

private slots:
    void handle_Trt_Edit();
    void handle_Trt_Suppress();
    void handle_Trt_Cancel();
    void handle_Trt_Ok();
    void handle_Trt_Up();
    void handle_Trt_Down();
    void handle_Trt_dbupload();
};

#endif // PATIENTLIST_H
