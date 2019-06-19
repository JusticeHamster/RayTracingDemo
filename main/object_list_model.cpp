#include "object_list_model.hpp"
#include "object_list_delegate.hpp"

#include <algorithm>

#include <QDebug>
#include <QSize>
#include <QDir>

#include <fstream>
#include <QMutexLocker>

#include "tools/loader.hpp"

static loader &ldr = loader::instance;

// reference: https://stackoverflow.com/questions/2409504/using-c-filestreams-fstream-how-can-you-determine-the-size-of-a-file
inline std::streampos get_file_size(const char *path)
{
    std::streampos fsize = 0;
    std::ifstream save_file(path, std::ios::binary);

    fsize = save_file.tellg();
    save_file.seekg(0, std::ios::end);
    fsize = save_file.tellg() - fsize;
    save_file.close();

    return fsize;
}

void object_list_model::load_data()
{
    QMutexLocker locker(&load_lock);
    loading = true;
    scene &scn = ldr.get_running_scene();
    auto fsize = get_file_size("object_list.data");
    if (fsize == 0) {
        qDebug(R"("object_list.data" file not found.)");
        loading = false;
        return;
    }
    std::ifstream save_file("object_list.data", std::ios::binary);
    buffer buf(static_cast<uint64_t>(fsize));
    save_file.read(reinterpret_cast<char *>(&buf[0]), fsize);
    save_file.close();
    qDebug() << "load:" << buf.size() << "bytes.";
    scn.deserialize(buf);
    qDebug("loaded.");
    loading = false;
}

void object_list_model::save_data()
{
    QMutexLocker locker(&load_lock);
    scene &scn = ldr.get_running_scene();
    auto buf = scn.serialize();
    qDebug() << "serialization:" << buf.size() << "bytes.";
    if (buf.size() == 0) {
        return;
    }
    std::ofstream save_file("object_list.data", std::ios::binary | std::ios::out | std::ios::trunc);
    save_file.write(reinterpret_cast<const char *>(&buf[0]), static_cast<long long>(buf.size()));
    save_file.close();
    qDebug("saved.");
}

bool object_list_model::loaded() const
{
    return !loading;
}

object_list_model::object_list_model(QObject *parent): QAbstractListModel(parent)
{
    load_data();
}

object_list_model::~object_list_model()
{

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
