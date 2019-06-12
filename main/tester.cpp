#include "tester.hpp"
#include "object/sphere.hpp"
#include "object/cube.hpp"
#include "object/ray.hpp"
#include "tools/image.hpp"
#include "object/model.hpp"
#include <QDebug>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

tester::tester()
{

}

void tester::test_all()
{
    glm::vec3 center(1,2,3);
    float radius = 2;
    sphere s(center, radius, 30, 30);
    s.hello();

    glm::mat4 trans(1.0f);
//    glm::mat4 trans = glm::translate(t0, glm::vec3(11.0f,12.0f,13.0f));
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
//    trans = glm::transpose(trans);
    glm::vec4 t1(center, 1);
    glm::vec4 t2 = t1;
    t2.x += radius;
    t1 = t1*trans;
    t2 = t2*trans;
    center = t1;
    glm::vec4 t = t2-t1;
    t *= t;
    radius = glm::sqrt(t.x + t.y + t.z);
    sphere s2(center, radius, 30, 30);
    s2.hello();
//    s.hello();
//    image img(100,100);
//    ray r(glm::vec3(3,4,5),
//          glm::vec3(-1,-1,-1),
//          glm::vec3(100,100,100),img,glm::vec2(0, 0), 1, 0);
    // auto t = sphere.intersect(r);
    // qDebug()<<t << r.point(t).x<<r.point(t).y<<r.point(t).z;
    // // 5.51399 -0.183505 0.816495 1.8165

//    cube c(glm::vec3(1,0,0),
//           glm::vec3(0,1,0),
//           glm::vec3(0,0,1),
//           glm::vec3(2,2,2),
//           glm::vec3(3,2,1));
//    model m({}, glm::vec3(0,0,0),glm::vec3(0,0,0),false,glm::vec3(0,0,0));
//    c.set_parent(&m);
//    auto t = c.ray_intersect(r);
//    qDebug()<<t << r.point(t).x<<r.point(t).y<<r.point(t).z;
}
