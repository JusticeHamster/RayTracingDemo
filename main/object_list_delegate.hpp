#ifndef OBJECT_LIST_DELEGATE_HPP
#define OBJECT_LIST_DELEGATE_HPP

#include <QStyledItemDelegate>

class object_list_model;

class object_list_delegate : public QStyledItemDelegate
{
    Q_OBJECT
private:
    object_list_model *model;
protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
public:
    explicit object_list_delegate(object_list_model *model, QObject *parent = nullptr);
};

#endif // OBJECT_LIST_DELEGATE_HPP
