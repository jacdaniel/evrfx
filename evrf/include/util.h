#ifndef UTIL
#define UTIL

#include <QString>

#define NULL_PTR nullptr

#define FREE(ptr){if ( (ptr) != NULL) { free(ptr); (ptr) = NULL; } }

#define DELETE(ptr){if ( (ptr) != NULL_PTR) { delete ptr; (ptr) = NULL_PTR; } }

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))


#define BUTTONIMAGE_CREATE(but, filename, x0, y0, nx, ny, trt_action) { \
    but = new QPushButton(QIcon(filename), "", this); \
    but->setGeometry(x0, y0, nx, ny); \
    but->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint); \
    but->setIconSize(QSize(nx, ny)); \
    connect(but, SIGNAL (released()), this, SLOT (trt_action)); }

#define BUTTONIMAGE_CREATE_V2(but, filename, x0, y0, nx, ny, trt_action, lab, txt, font, lx0, ly0, lnx, lny) { \
    BUTTONIMAGE_CREATE(but, filename, x0, y0, nx, ny, trt_action) \
    lab = new QLabel(txt); \
    lab->setGeometry(lx0, ly0, lnx, lny); \
    lab->setFont(font); \
    lab->setParent(but); }

#define BUTTONIMAGE_CREATE_PARENT(but, parent, filename, x0, y0, nx, ny, trt_action) { \
    but = new QPushButton(parent); \
    but->setGeometry(x0, y0, nx, ny); \
    but->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint); \
    but->setIcon(QIcon(filename)); \
    but->setIconSize(QSize(nx, ny)); \
    connect(but, SIGNAL (released()), this, SLOT (trt_action)); }

#define BUTTONCREATEx(but, lab, name, font, x0, y0, width, height, ico, trt) { \
    but = new QPushButton(QIcon(ico), "", this);  }


#define BUTTONCREATE(but, lab, name, font, x0, y0, width, height, ico, trt) { \
    but = new QPushButton(QIcon(ico), "", this); \
    but->setGeometry(x0,y0,width,height); \
    but->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint); \
    but->setIcon(QIcon(ico)); \
    bproctology->setIconSize(QSize(width, height)); \
    connect(but, SIGNAL (released()), this, SLOT (trt)); \
    lab = new QLabel(name); \
    lab->setGeometry(128, 50, 300, 50); \
    lab->setFont(*font); \
    lab->setParent(but); }

bool file_exist(char *filename);
void char_return_suppress(char *p);

void hsv2rgb(double h, double s, double v, double *r, double *g, double *b);

void seconds_to_hhmmss(int sec, int*hh, int *mm, int *ss);

long get_compact_date_yyyymmdd();
long get_compact_time_hhmm();

QString get_date_yyyy_mm_dd_from_compactdate(long d);
QString get_time_hh_mm_from_compactdate(long d);

#endif // UTIL

