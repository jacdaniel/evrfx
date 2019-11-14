
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "include/quickuserinfo.h"
#include "include/config.h"
#include "include/util.h"
#include "ui_quickuserinfo.h"
#include <./include/patient.h>

QuickUserInfo::QuickUserInfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuickUserInfo)
{
    ui->setupUi(this);
}

QuickUserInfo::QuickUserInfo(QWidget *parent, Param *param, int id, void *ppatient) :
    QMainWindow(parent),
    ui(new Ui::QuickUserInfo)
{
    ui->setupUi(this);
    this->param = param;
    this->patient = ppatient;

    setGeometry(QRect(QPoint(0, 0), QSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)));
    QPixmap *pix = new QPixmap(MAIN_SCREEN_IMAGE2);
    QLabel *lab = new QLabel(this);
    lab->setGeometry(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    lab->setPixmap(*pix);
    this->id = id;
    this->select = 0;
    QFont lineeditfont = QFont(TITLE_LABEL_FONT_NAME, 14, TITLE_LABEL_FONT_WEIGHT);
    QFont *editlabelfont = new QFont(TITLE_LABEL_FONT_NAME, 14, TITLE_LABEL_FONT_WEIGHT);
    this->lineedit = new QLineEdit*[3];
    this->textedit = new QTextEdit*[3];
    this->ledit = new QLabel*[4];
    this->seditvalue = new QString[4];

    for (int i=0; i<3; i++)
    {
        lineedit[i] = new QLineEdit();
        lineedit[i]->setReadOnly(true);
        lineedit[i]->setVisible(true);
        lineedit[i]->setParent(this);
        lineedit[i]->setStyleSheet("QLineEdit { background: rgb(255, 255, 100);}");
        lineedit[i]->setFont(lineeditfont);
        // connect(lineedit[i], SIGNAL (clicked()), this, SLOT (handle_Trt_EditSelect()));
        lineedit[i]->installEventFilter(this);
        ledit[i] = new QLabel(this);
        ledit[i]->setFont(*editlabelfont);
    }

    textedit[0] = new QTextEdit();
    textedit[0]->setReadOnly(true);
    textedit[0]->setVisible(true);
    textedit[0]->setParent(this);
    textedit[0]->setStyleSheet("QLineEdit { background: rgb(255, 255, 100);}");
    textedit[0]->setFont(lineeditfont);
    // connect(lineedit[i], SIGNAL (clicked()), this, SLOT (handle_Trt_EditSelect()));
    textedit[0]->installEventFilter(this);

    // textedit[0]->setTextColor(QColor(255,255,0));
    // textedit[0]->setTextBackgroundColor(QColor(255,255,0));
    // QPalette pa = textedit[0]->palette();
    // pa.setColor(QPalette::Base, QColor(255,255,0));
    // textedit[0]->setPalette(pa);
    textedit[0]->setStyleSheet("background-color: red;");

    ledit[3] = new QLabel(this);
    ledit[3]->setFont(*editlabelfont);

    ledit[0]->setGeometry(5, 4, 100, 35);
    ledit[0]->setText((QString)param->get_label(IDX_NAME));
    lineedit[0]->setGeometry(110, 4, 350, 35);

    ledit[1]->setGeometry(5, 50, 100, 35);
    ledit[1]->setText((QString)param->get_label(IDX_AGE));
    lineedit[1]->setGeometry(110, 50, 45, 35);

    ledit[2]->setGeometry(200, 50, 100, 35);
    ledit[2]->setText((QString)param->get_label(IDX_CEAP));
    lineedit[2]->setGeometry(270, 50, 190, 35);

    ledit[3]->setGeometry(5, 100, 100, 35);
    ledit[3]->setText((QString)param->get_label(IDX_REMARK));


    textedit[0]->setGeometry(110, 100, 500, 130);

    this->pKeyboard = new WKeyboard();
    this->pKeyboard->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    // this->pKeyboard->setGeometry(QRect(QPoint(0, 200), QRect(QPoint(0, 200))));
    this->pKeyboard->setGeometry(0,240,800*3/4,250);
    // this->pKeyboard->setStyleSheet("background-color: black;");
    this->pKeyboard->setParent(this);
    this->pKeyboard->setCallBack(Trt_CallBack0);
    this->pKeyboard->show();

    // QString filename = this->directory + "00000000/" + "userinfo.txt";
    // this->userinfo = user_info_init((char*)filename.toStdString().c_str());

    // char filename[500];
    // userinfo_get_filename(param->get_base_directory(), p->idx, filename);
    // this->userinfo = user_info_init(filename);

    init_text_field(this->patient);
    validESelection(select);
    BUTTONIMAGE_CREATE(bquit, CANCEL_IMAGE, 720, 400, 75, 75, handle_Trt_Exit())
}

QuickUserInfo::~QuickUserInfo()
{
    delete ui;
}


void QuickUserInfo::init_text_field(void *_p)
{
    PATIENT *p = (PATIENT*)_p;
    char tmp [10];
    tmp[0] = 0;
    if ( p == NULL ) return;
    this->seditvalue[0] = QString(p->name);
    // this->seditvalue[1] = QString(p->age);
    if ( p->age > 0 )
    {
        sprintf(tmp, "%d", p->age);
    }
    else
    {
        tmp[0] = 0;
    }
    this->seditvalue[1] = QString(tmp);
    this->seditvalue[2] = QString(p->ceap);
    this->seditvalue[3] = QString(p->remark);

    lineedit[0]->setText(seditvalue[0]);
    lineedit[1]->setText(seditvalue[1]);
    lineedit[2]->setText(seditvalue[2]);
    textedit[0]->setText(seditvalue[3]);
}


void QuickUserInfo::Trt_CallBack(char key)
{
    if ( ( key >= '0' && key<='z' && key != KEY_RET) || key == '\n' )
        seditvalue[select] += key;
    else
    {
        if ( key == KEY_RET )
            seditvalue[select].remove(seditvalue[select].length()-1,1);
    }

    if ( select < 3 )
        lineedit[select]->setText(seditvalue[select]);
    else
        textedit[0]->setText(seditvalue[select]);
}

void QuickUserInfo::Trt_CallBack0(void *parent, char key)
{
    ((QuickUserInfo*)parent)->Trt_CallBack(key);
}

void QuickUserInfo::validESelection(int sel)
{
    QString str_sel = "QLineEdit { background-color: rgb(255, 255, 0);}";
    QString str_nosel = "QLineEdit { background-color: rgb(255, 255, 255);}";
    for (int i=0; i<3; i++)
        lineedit[i]->setStyleSheet(str_nosel);
    textedit[0]->setStyleSheet(str_nosel);
    if ( sel < 3 )
        lineedit[sel]->setStyleSheet(str_sel);
    else
        textedit[0]->setStyleSheet("background-color: yellow;");
}

bool QuickUserInfo::eventFilter(QObject* object, QEvent* event)
{
    if ( event->type() == QEvent::FocusIn )
    {
        select = 3;
        for (int i=0; i<3; i++)
            if ( object == this->lineedit[i] ) select = i;
        validESelection(select);
    }

    return false;
}

void QuickUserInfo::handle_Trt_Exit()
{
    PATIENT *pp = (PATIENT*)this->patient;
    strcpy(pp->name, (char*)this->seditvalue[0].toStdString().c_str());
    pp->age = atoi((char*)this->seditvalue[1].toStdString().c_str());
    strcpy(pp->ceap, (char*)this->seditvalue[2].toStdString().c_str());
    strcpy(pp->remark, (char*)this->seditvalue[3].toStdString().c_str());
    close();
}


