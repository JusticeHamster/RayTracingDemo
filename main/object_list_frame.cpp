#include "object_list_frame.hpp"
#include "ui_object_list_frame.h"

object_list_frame::object_list_frame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::object_list_frame)
{
    ui->setupUi(this);
    save = styleSheet().toStdString();
}

object_list_frame::~object_list_frame()
{
    delete ui;
}

void object_list_frame::set_selected(bool selected)
{
    if (selected)
        setStyleSheet("background-color: rgb(255, 239, 213);");
    else
        setStyleSheet(save.c_str());
}

void object_list_frame::set_pos(glm::vec3 pos)
{
    ui->X->setValue(static_cast<double>(pos.x));
    ui->Y->setValue(static_cast<double>(pos.y));
    ui->Z->setValue(static_cast<double>(pos.z));
}

void object_list_frame::set_custom(glm::vec3 custom)
{
    ui->customSpinBox1->setValue(static_cast<double>(custom.x));
    ui->customSpinBox2->setValue(static_cast<double>(custom.y));
    ui->customSpinBox3->setValue(static_cast<double>(custom.z));
}

void object_list_frame::set_name(std::string name)
{
    ui->name->setText(name.c_str());
}
