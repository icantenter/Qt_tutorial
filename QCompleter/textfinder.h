#ifndef TEXTFINDER_H
#define TEXTFINDER_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QCompleter>
QT_BEGIN_NAMESPACE
namespace Ui { class textfinder; }
QT_END_NAMESPACE

class textfinder : public QWidget
{
    Q_OBJECT
public:
    textfinder(QWidget *parent = nullptr);
    ~textfinder();

private slots:
    void on_findButton_clicked();
    void loadTextFile();
    void loadCompleter();

private:
    Ui::textfinder *ui;
    QStringList list;
};
#endif // TEXTFINDER_H
