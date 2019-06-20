#include "object_list_model.hpp"
#include "object_list_delegate.hpp"

#include <algorithm>

#include <QDebug>
#include <QSize>
#include <QDir>

#include <fstream>
#include <QMutexLocker>

#include "tools/loader.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
    if (parent && deserialize) {
        deserialize(parent->get(), buf);
    }
    scn.deserialize(buf);
    qDebug("loaded.");
    loading = false;
}

void object_list_model::save_data()
{
    QMutexLocker locker(&load_lock);
    scene &scn = ldr.get_running_scene();
    auto buf = scn.serialize();
    if (parent && serialize) {
        buffer t = serialize(parent->get());
        buf.insert(buf.end(), t.begin(), t.end());
    }
    qDebug() << "serialization:" << buf.size() << "bytes.";
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

}

object_list_model::~object_list_model()
{

}

int object_list_model::rowCount(const QModelIndex &parent) const
{
    return ldr.get_running_scene().object_count();
}

QVariant object_list_model::data(const QModelIndex &index, int role) const
{
    const model &m = ldr.get_running_scene().get_model(index.row());
    switch(role) {
    case Qt::UserRole:
        return m.get_id();
    case Qt::DisplayRole:
        return m.get_name().c_str();
    case Qt::SizeHintRole:
        return QSize(0, 100);
    }
    return QVariant();
}

void object_list_model::set_selected(model &m)
{
    selected = &m;
}

void object_list_model::rotate(float angle)
{
    if (selected == nullptr)
        return;

    glm::mat4 r(1.f);
    selected->transform(glm::rotate(r, angle * shape::PI / 180.f, glm::vec3(0, 1, 0)));
}

void object_list_model::remove_selected()
{
    ldr.get_running_scene().remove_model(selected);
}
