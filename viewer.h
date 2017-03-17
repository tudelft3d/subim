#ifndef VIEWER_H
#define VIEWER_H

#include <QGLViewer/qglviewer.h>
#include "subim_main.h"

class Viewer : public QGLViewer
{
public:
    void draw_cube(float, float, float);
    void set_param(float, float, float, int, int, int);
    float x_, y_, z_;
    int sx, sy, sz;

protected :
  virtual void draw();
  virtual void init();
  virtual QString helpString() const;
};

#endif // VIEWER_H
