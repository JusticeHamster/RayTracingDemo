#ifndef OBJECT_LIST_MODEL_HPP
#define OBJECT_LIST_MODEL_HPP

#include <QAbstractListModel>

class object_list_model : public QAbstractListModel
{
    Q_OBJECT
private:
    void load_data();
    void save_data();
public:
    explicit object_list_model(QObject *parent = nullptr);
    ~object_list_model();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // OBJECT_LIST_MODEL_HPP