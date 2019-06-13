#include "object_list_delegate.hpp"
#include "object_list_model.hpp"

void object_list_delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
}

object_list_delegate::object_list_delegate(object_list_model *model, QObject *parent): QStyledItemDelegate(parent), model(model)
{

}
