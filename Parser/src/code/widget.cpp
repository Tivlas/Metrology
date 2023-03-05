#include "../include/widget.h"
#include "../ui/ui_widget.h"
#include <iostream>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->operatorsTable->setHorizontalHeaderLabels(QStringList()
                                                  << "Оператор"
                                                  << "f1j");
    ui->operandsTable->setHorizontalHeaderLabels(QStringList()
                                                 << "Операнд"
                                                 << "f2i");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::ParseAndDisplay(int argc, char const *argv[])
{

    std::vector<std::pair<std::string, int>> operators;
    std::vector<std::pair<std::string, int>> operands;
    int n1, n2, N1, N2, n, N, V;
    std::tie(operators, operands, n1, n2, N1, N2, n, N, V) = parser.parse(argc, argv);

    for (const auto &i : operators)
    {
        QTableWidgetItem *item1 = new QTableWidgetItem(QString::fromStdString(i.first));
        QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(i.second));
        ui->operatorsTable->insertRow(num_of_operators_rows);
        ui->operatorsTable->setItem(num_of_operators_rows, 0, item1);
        ui->operatorsTable->setItem(num_of_operators_rows, 1, item2);
        num_of_operators_rows++;
    }

    for (const auto &i : operands)
    {
        QTableWidgetItem *item1 = new QTableWidgetItem(QString::fromStdString(i.first));
        QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(i.second));
        ui->operandsTable->insertRow(num_of_operands_rows);
        ui->operandsTable->setItem(num_of_operands_rows, 0, item1);
        ui->operandsTable->setItem(num_of_operands_rows, 1, item2);
        num_of_operands_rows++;
    }
}

void Widget::on_chooseFileBtn_clicked()
{
    std::string file_name = QFileDialog::getOpenFileName(this, "Выберите файл", "/home/timofey/Uni/BSUIR/Metrology/Task1", "Available extensions (*.cpp)").toStdString();
    char const *argv[6];
    argv[0] = std::string("./Parser").c_str();
    argv[1] = file_name.c_str();
    argv[2] = std::string("--").c_str();
    argv[3] = std::string("-std=c++17").c_str();
    argv[4] = std::string("-isystem").c_str();
    argv[5] = std::string("/usr/include/clang/12/include").c_str();
    ParseAndDisplay(6, argv);
}