#include "../include/widget.h"
#include "../ui/ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::ParseAndDisplay(int argc, char const *argv[])
{
    auto ans = parser.parse(argc, argv);
}

void Widget::on_chooseFileBtn_clicked()
{
    std::string file_name = QFileDialog::getOpenFileName(this, "Выберите файл", "/home/timofey/Uni/BSUIR/Metrology/Task1", "Available extensions (*.cpp)").toStdString();
    char const *argv[5];
    argv[0] = std::string("").c_str();
    argv[1] = file_name.c_str();
    argv[2] = std::string("--").c_str();
    argv[3] = std::string("-isystem").c_str();
    argv[4] = std::string("/usr/include/clang/12/include").c_str();
    ParseAndDisplay(5, argv);
}