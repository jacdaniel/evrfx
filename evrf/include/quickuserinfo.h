#ifndef QUICKUSERINFO_H
#define QUICKUSERINFO_H

#include "wkeyboard.h"
#include "./include/param.h"

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QMainWindow>

namespace Ui {
class QuickUserInfo;
}

class QuickUserInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuickUserInfo(QWidget *parent = nullptr);
    explicit QuickUserInfo(QWidget *parent, Param *param, int id, void *ppatient);
    ~QuickUserInfo();
    void Trt_CallBack(char key);
    static void Trt_CallBack0(void *parent, char key);
    void init_text_field(void *_p);

    QLabel *LTitle, **ledit;
    QLineEdit **lineedit;
    QTextEdit **textedit;
    WKeyboard *pKeyboard;
    void *patient;

private:
    Ui::QuickUserInfo *ui;
    QLabel *lab_info;
    QPushButton *bquit;
    QString *seditvalue;
    // QString directory;
    Param *param;
    int id;
    void *userinfo;
    int select;
    bool eventFilter(QObject* object, QEvent* event);
    void validESelection(int sel);

private slots:
    void handle_Trt_Exit()    ;
};

#endif // QUICKUSERINFO_H
