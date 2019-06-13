#include "object_list_model.hpp"
#include "object_list_delegate.hpp"

#include <QDebug>
#include <QSize>

#include "tools/loader.hpp"

static loader &ldr = loader::instance;

void object_list_model::load_data()
{

}

void object_list_model::save_data()
{

}

object_list_model::object_list_model(QObject *parent): QAbstractListModel(parent)
{
    if (QSqlDatabase::contains("objectList")) {
        database = QSqlDatabase::database("objectList");
    } else {
        database = QSqlDatabase::addDatabase("QSQLITE", "objectList");
    }
    database.setDatabaseName("objectList.db");
    if (!database.open()) {
        qDebug() << "failed to connect database objectList" << database.lastError();
    }
    load_data();
}

object_list_model::~object_list_model()
{
    save_data();
    database.close();
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
