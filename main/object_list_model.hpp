#ifndef OBJECT_LIST_MODEL_HPP
#define OBJECT_LIST_MODEL_HPP

#include <QAbstractListModel>
#include <QMutex>
#include <functional>

#include "mainwindow.hpp"

class object_list_model : public QAbstractListModel
{
    Q_OBJECT
private:
    model *selected = nullptr;
    bool loading = true;

    QMutex load_lock;
public:
    std::optional<std::reference_wrapper<MainWindow> > parent;
    std::function<buffer(MainWindow &)> serialize;
    std::function<void(MainWindow &, buffer &)> deserialize;

    explicit object_list_model(QObject *parent = nullptr);
    ~object_list_model();

    void load_data();
    void save_data();
    bool loaded() const;

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    void set_selected(model &m);
    void rotate(float angle);
    void remove_selected();
};

#endif // OBJECT_LIST_MODEL_HPP
