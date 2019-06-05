#include "tester.hpp"
#include "object/sphere.hpp"
#include "object/cube.hpp"
#include "object/ray.hpp"
#include "tools/image.hpp"
#include "object/model.hpp"
#include <QDebug>
#include "glm/glm.hpp"

tester::tester()
{

}

void tester::test_all()
{
    // glm::vec3 center(0,0,0);
    // float radius = 2;
    // sphere sphere(center, radius, 30, 30);
    image img(100,100);
    ray r(glm::vec3(3,4,5),
          glm::vec3(-1,-1,-1),
          glm::vec3(100,100,100),img,glm::vec2(0, 0), 1, 0);
    // auto t = sphere.intersect(r);
    // qDebug()<<t << r.point(t).x<<r.point(t).y<<r.point(t).z;
    // // 5.51399 -0.183505 0.816495 1.8165

    cube c(glm::vec3(0.5,0.5,0),
           glm::vec3(0.5,-0.5,0),
           glm::vec3(0,0,1),
           glm::vec3(2,2,2),
           glm::vec3(0,0,0));
    model m({}, glm::vec3(0,0,0),glm::vec3(0,0,0),false,glm::vec3(0,0,0));
    c.set_parent(&m);
    auto t = c.intersect(r);
    qDebug()<<t << r.point(t).x<<r.point(t).y<<r.point(t).z;
}
