#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <vector>
#include <QFileDialog>
#include "../include/metrics-calculator.h"
#include <QProcess>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void ParseAndDisplay(int argc, char const *argv[]);
    void Reset();

private slots:
    void on_chooseFileBtn_clicked();

private:
    Ui::Widget *ui;
    ParserHalstead parser;
    int num_of_operators_rows = 0;
    int num_of_operands_rows = 0;
};
#endif
