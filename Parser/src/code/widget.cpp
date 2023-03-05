#include "../include/widget.h"
#include "../ui/ui_widget.h"
#include <iostream>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->operatorsTable->horizontalHeader()->setStretchLastSection(true);
    ui->operandsTable->horizontalHeader()->setStretchLastSection(true);
    ui->operatorsTable->verticalHeader()->setVisible(false);
    ui->operandsTable->verticalHeader()->setVisible(false);

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
        QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(num_of_operators_rows + 1));
        ui->operatorsTable->insertRow(num_of_operators_rows);
        ui->operatorsTable->setItem(num_of_operators_rows, 0, item0);
        ui->operatorsTable->setItem(num_of_operators_rows, 1, item1);
        ui->operatorsTable->setItem(num_of_operators_rows, 2, item2);
        num_of_operators_rows++;
    }

    for (const auto &i : operands)
    {
        QTableWidgetItem *item1 = new QTableWidgetItem(QString::fromStdString(i.first));
        QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(i.second));
        QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(num_of_operands_rows + 1));
        ui->operandsTable->insertRow(num_of_operands_rows);
        ui->operandsTable->setItem(num_of_operands_rows, 0, item0);
        ui->operandsTable->setItem(num_of_operands_rows, 1, item1);
        ui->operandsTable->setItem(num_of_operands_rows, 2, item2);
        num_of_operands_rows++;
    }

    QTableWidgetItem *item_n1 = new QTableWidgetItem(QString("n1 = ") + QString::number(n1));
    QTableWidgetItem *item_n2 = new QTableWidgetItem(QString("n2 = ") + QString::number(n2));
    QTableWidgetItem *item_N1 = new QTableWidgetItem(QString("N1 = ") + QString::number(N1));
    QTableWidgetItem *item_N2 = new QTableWidgetItem(QString("N2 = ") + QString::number(N2));

    ui->operatorsTable->insertRow(num_of_operators_rows);
    ui->operatorsTable->setItem(num_of_operators_rows, 0, item_n1);
    ui->operatorsTable->setItem(num_of_operators_rows, 2, item_N1);

    ui->operandsTable->insertRow(num_of_operands_rows);
    ui->operandsTable->setItem(num_of_operands_rows, 0, item_n2);
    ui->operandsTable->setItem(num_of_operands_rows, 2, item_N2);

    ui->operandsTable->resizeColumnsToContents();
    ui->operatorsTable->resizeColumnsToContents();

    ui->progDictLabel->setText(QString("Словарь программы n = " + QString::number(n1) + " + " + QString::number(n2) + " = " + QString::number(n)));
    ui->progLengthLabel->setText(QString("Длина программы N = " + QString::number(N1) + " + " + QString::number(N2) + " = " + QString::number(N)));
    ui->progVolumelabel->setText(QString("Объем программы V = " + QString::number(N) + "*log₂" + QString::number(n) + " = " + QString::number(V)));
}

void Widget::Reset()
{
    ui->operatorsTable->clear();
    ui->operandsTable->clear();
    num_of_operands_rows = 0;
    num_of_operators_rows = 0;
    ui->operatorsTable->setHorizontalHeaderLabels(QStringList()
                                                  << "Оператор"
                                                  << "f1j");
    ui->operandsTable->setHorizontalHeaderLabels(QStringList()
                                                 << "Операнд"
                                                 << "f2i");
    ui->progDictLabel->clear();
    ui->progLengthLabel->clear();
    ui->progVolumelabel->clear();
}

void Widget::on_chooseFileBtn_clicked()
{
    Reset();
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