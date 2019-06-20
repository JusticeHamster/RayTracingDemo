#include "object_list_delegate.hpp"
#include "object_list_model.hpp"
#include "object_list_frame.hpp"

#include "tools/loader.hpp"
#include "object/cube.hpp"
#include "object/line.hpp"
#include "object/sphere.hpp"
#include "object/tetrahedron.hpp"

#include <QPainter>

static loader &ldr = loader::instance;

void object_list_delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() != 0) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }
    model &selected = ldr.get_running_scene().get_model(index.row());
    frame->set_name(selected.get_name());
    frame->set_pos(selected.get_position());
    if (selected.object_count() == 1) {
        auto shape = selected.get_shape();
        switch(shape->type_id()) {
        case 0: {
            frame->set_name("cube(extend)");
            frame->set_custom(dynamic_cast<cube *>(shape.get())->get_extend());
            break;
        }
        case 1: {
            frame->set_name("line(start))");
            frame->set_custom(dynamic_cast<line *>(shape.get())->start_point());
            break;
        }
        case 3: {
            frame->set_name("sphere(center)");
            frame->set_custom(dynamic_cast<sphere *>(shape.get())->get_center());
            break;
        }
        case 4: {
            frame->set_name("tetrahedron");
            break;
        }
        default: break;
        }
    }
    frame->resize(option.rect.width(), option.rect.height());
    if (option.state & QStyle::State_Selected) {
        frame->set_selected(true);
    } else {
        frame->set_selected(false);
    }
    QPixmap pixmap = frame->grab();
    painter->drawPixmap(option.rect, pixmap);
}

object_list_delegate::object_list_delegate(object_list_model *lmodel, QObject *parent): QStyledItemDelegate(parent), lmodel(lmodel)
{
    frame = new object_list_frame;
}

object_list_delegate::~object_list_delegate()
{
    if (frame) {
        frame->deleteLater();
        frame = nullptr;
    }
}
