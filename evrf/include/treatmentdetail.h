#ifndef TREATMENTDETAIL_H
#define TREATMENTDETAIL_H

#include <./include/param.h>

#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QMainWindow>

namespace Ui {
class TreatmentDetail;
}

class TreatmentDetail : public QMainWindow
{
    Q_OBJECT

public:
    explicit TreatmentDetail(QWidget *parent = 0);
    explicit TreatmentDetail(QWidget *parent, Param *param, void *_db);



    ~TreatmentDetail();

private:
    Ui::TreatmentDetail *ui;
    QPushButton *bquit;
    QTextEdit *textedit;
    QLabel *ltitle;
    Param *param;
    void *pdb;
    void init();
    void display(void *db);

private slots:
        void handle_Trt_Quit();
};

#endif // TREATMENTDETAIL_H
