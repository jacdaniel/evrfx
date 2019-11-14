#ifndef DPATIENT_LIST_H
#define DPATIENT_LIST_H

#include <QDialog>

namespace Ui {
class Dpatient_list;
}

class Dpatient_list : public QDialog
{
    Q_OBJECT

public:
    explicit Dpatient_list(QWidget *parent = 0);
    ~Dpatient_list();

private:
    Ui::Dpatient_list *ui;
};

#endif // DPATIENT_LIST_H
