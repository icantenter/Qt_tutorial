#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QVector>
#include <QLabel>
#include <QTime>
#include <QTimer>
#include <QTextStream>
#include <QFile>
#include <QDir>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QTimer *timer;
    QLabel *current_task;
    QTime task_begin;
    QDate current_date;
    void init_buttons();
    void init_time();
    void on_task_buttons_clicked();
    void onTimeOut();
    void update_date();
    void file_append_routine();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:

private slots:

private:
    Ui::MainWindow *ui;


};

namespace Pd
{

typedef struct
{
    QString task_name;
    QTime task_begin, task_end;

} ROUTINE;
enum Tag
{
    TaskTag = 0,
    JumpTag,
};
};

#endif // MAINWINDOW_H
