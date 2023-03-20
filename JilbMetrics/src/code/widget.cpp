#include "../include/widget.h"
#include "../ui/ui_widget.h"
#include <iostream>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::ParseAndDisplay(int argc, char const *argv[], QString code)
{

    unsigned long long CL, CLI;
    double cl;
    std::tie(CL, cl, CLI) = parser.parse(argc, argv);
    ui->CL_label->setText("Количество условных операторов: " + QString::number(CL));
    ui->cl_label->setText("Насыщенность: " + QString::number(cl));
    ui->CLI_label->setText("Максимальный уровень вложенности: " + QString::number(CLI));
}

void Widget::Reset()
{
    ui->CL_label->clear();
    ui->cl_label->clear();
    ui->CLI_label->clear();
}

void Widget::on_chooseFileBtn_clicked()
{
    Reset();
    std::string file_name = QFileDialog::getOpenFileName(this, "Выберите файл", "/home/timofey/Uni/BSUIR/Metrology/Tasks/test_files", "Available extensions (*.cpp)").toStdString();

    QProcess process;
    process.start("g++", QStringList() << QString::fromStdString(file_name));
    process.waitForFinished();

    if (process.exitCode() == 1)
    {
        QMessageBox::warning(this, "ERROR", "File is corrupted and cannot be compiled!");
        return;
    }
    QFile code_file(QString::fromStdString(file_name));
    code_file.open(QIODevice::ReadOnly);
    QString code = code_file.readAll();
    code_file.close();

    char const *argv[6];
    argv[0] = std::string("./JilbMetrics").c_str();
    argv[1] = file_name.c_str();
    argv[2] = std::string("--").c_str();
    argv[3] = std::string("-std=c++17").c_str();
    argv[4] = std::string("-isystem").c_str();
    argv[5] = std::string("/usr/include/clang/12/include").c_str();
    ParseAndDisplay(6, argv, code);
}