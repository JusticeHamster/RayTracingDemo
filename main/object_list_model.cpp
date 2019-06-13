#include "object_list_model.hpp"
#include "object_list_delegate.hpp"

#include <algorithm>

#include <QDebug>
#include <QSize>
#include <QDir>

#include <fstream>

#include "tools/loader.hpp"

static loader &ldr = loader::instance;

void object_list_model::load_data()
{
    scene &scn = ldr.get_running_scene();
    scn.deserialize(buf);
}

void object_list_model::save_data()
{
    scene &scn = ldr.get_running_scene();
    std::ofstream save_file("object_list.data");
    save_file << scn.serialize();
}

object_list_model::object_list_model(QObject *parent): QAbstractListModel(parent)
{
    load_data();
}

object_list_model::~object_list_model()
{
    save_data();
}

int object_list_model::rowCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant object_list_model::data(const QModelIndex &index, int role) const
{
    switch(role) {
    case Qt::UserRole:
        return QVariant();
    case Qt::DisplayRole:
        return QVariant();
    case Qt::SizeHintRole:
        return QSize(0, 100);
    }
    return QVariant();
}
