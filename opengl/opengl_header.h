#ifndef OPENGL_H
#define OPENGL_H

#ifdef __APPLE__ // 苹果比较特殊
    #include <OpenGL/glu.h>
#else // 其它的默认
    #include <GL/glu.h>
#endif

#endif // OPENGL_H
