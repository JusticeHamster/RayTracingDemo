#ifndef OBJECT_LIST_FRAME_HPP
#define OBJECT_LIST_FRAME_HPP

#include <QFrame>
#include <QModelIndex>
#include <string>
#include <vector>
#include <tuple>

#include "glm/glm.hpp"

namespace Ui {
class object_list_frame;
}

class object_list_frame : public QFrame
{
    Q_OBJECT

public:
    explicit object_list_frame(QWidget *parent = nullptr);
    ~object_list_frame();

    void set_selected(bool selected);
    void set_pos(glm::vec3 pos);
    void set_custom(glm::vec3 custom);
    void set_name(std::string name);

private:
    Ui::object_list_frame *ui;

    std::string save;
};

#endif // OBJECT_LIST_FRAME_HPP
