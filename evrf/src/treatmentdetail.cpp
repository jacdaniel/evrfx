
#include <QRect>
#include <QLabel>
#include <QLabel>
#include <QFont>
#include <QPixmap>

#include <./include/util.h>
#include "./include/patient.h"
#include <./include/config.h>
#include "./include/treatmentdetail.h"
#include "ui_treatmentdetail.h"

TreatmentDetail::TreatmentDetail(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TreatmentDetail)
{
    ui->setupUi(this);
}

TreatmentDetail::TreatmentDetail(QWidget *parent, Param *param, void *_db) :
    QMainWindow(parent),
    ui(new Ui::TreatmentDetail)
{
    ui->setupUi(this);
    this->param = param;

    setGeometry(QRect(QPoint(0, 0), QSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)));
    // QFont *font = new QFont(TITLE_LABEL_FONT_NAME, TITLE_LABEL_FONT_SIZE-10, TITLE_LABEL_FONT_WEIGHT);
    // QRegion region( QRect( 0, 0, 68, 68 ), QRegion:: Ellipse ); // Création d'une ellipse de 50px de diamètre

    QPixmap *pix = new QPixmap(MAIN_SCREEN_IMAGE2);
    QLabel *lab = new QLabel(this);
    lab->setGeometry(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    lab->setPixmap(*pix);
    pdb = _db;
    init();
    display(pdb);
}

TreatmentDetail::~TreatmentDetail()
{
    delete ui;
}

void TreatmentDetail::init()
{
    QFont lineeditfont = QFont(TITLE_LABEL_FONT_NAME, 14, TITLE_LABEL_FONT_WEIGHT);
    QFont font_title = QFont("Helvetica", 22, QFont::Bold);

    ltitle = new QLabel(this);
    ltitle->setGeometry(200, 5, 500, 50);
    ltitle->setStyleSheet("QLabel { background-color : none; color : #00007F; }");
    ltitle->setFont(font_title);
    ltitle->setText((QString)param->get_label(IDX_DETAILS));

    textedit = new QTextEdit();
    textedit->setReadOnly(true);
    textedit->setVisible(true);
    textedit->setParent(this);
    textedit->setFont(lineeditfont);
    textedit->installEventFilter(this);
    textedit->setGeometry(110, 100, MAIN_WINDOW_WIDTH-2*110, 350);
    textedit->setStyleSheet("background-color: rgb(240, 240, 255);");
    textedit->setTextColor(QColor(0, 0, 128));
    BUTTONIMAGE_CREATE(bquit,   CANCEL_IMAGE,    720, 400, 75, 75, handle_Trt_Quit())
}

extern const char *CATETHER_TYPE[][10];

void TreatmentDetail::display(void *_db)
{
  char line[10000], tmp[1000];
  int hh, mm, ss;
  USER_DATABASE_PATIENT *p = (USER_DATABASE_PATIENT*)_db;
  if ( p == NULL ) return;
  sprintf(line, "%s: %s - %s\n", param->get_label(IDX_DATE), get_date_yyyy_mm_dd_from_compactdate(p->date).toStdString().c_str(), get_time_hh_mm_from_compactdate(p->time).toStdString().c_str());
  sprintf(tmp, "%s: %s\n", param->get_label(IDX_NAME), p->name); strcat(line, tmp);
  sprintf(tmp, "%s: %d\n", param->get_label(IDX_AGE), p->age); strcat(line, tmp);
  sprintf(tmp, "%s: %s\n", param->get_label(IDX_CEAP), p->ceap); strcat(line, tmp);
  sprintf(tmp, "%s: %s\n", param->get_label(IDX_CATHETER), CATETHER_TYPE[p->treatment_type][p->treatment]); strcat(line, tmp);
  sprintf(tmp, "%s: %s\n\n", param->get_label(IDX_REMARK), p->remark); strcat(line, tmp);
  seconds_to_hhmmss(p->treatment_time / 10, &hh, &mm, &ss);
  sprintf(tmp, "%s: %.2d:%.2d:%.2d\n\n", param->get_label(IDX_TIME), hh, mm, ss); strcat(line, tmp);
  if ( p->treatment_type == RUN_CR30i || p->treatment == RUN_CR40i || p->treatment == RUN_CR45i || p->treatment == RUN_HPR45i)
  {
      sprintf(tmp, "%s: %d J\n\n", param->get_label(IDX_ENERGY), p->energy); strcat(line, tmp);
  }
  if ( p->pad_connectivity == 0 )
  {
      sprintf(tmp, "%s: %s\n\n", param->get_label(IDX_PAD), param->get_label(IDX_OFF)); strcat(line, tmp);
  }
  else
  {
      sprintf(tmp, "%s: %s\n\n", param->get_label(IDX_PAD), param->get_label(IDX_ON)); strcat(line, tmp);
  }

  textedit->setText(QString(line));
}

void TreatmentDetail::handle_Trt_Quit()
{
    close();
    // delete this;
}

