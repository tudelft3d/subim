#include "viewer.h"

using namespace std;

extern float x_in, y_in, z_in;
extern int sz_x, sz_y, sz_z;
float scale = 1000, scale2 = 100;

void Viewer::draw_cube(float x0, float y0, float z0)
{
//    glBegin(GL_QUADS);
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f , 1.0f);

    // front
    glVertex3f( x0/scale,           y0/scale,           (z0+0.5*scale2)/scale   );
    glVertex3f( ((x0+100))/scale,   y0/scale,           (z0+0.5*scale2)/scale   );
    glVertex3f( ((x0+100))/scale,   (y0+100)/scale,     (z0+0.5*scale2)/scale   );
    glVertex3f( x0/scale,           (y0+100)/scale,     (z0+0.5*scale2)/scale   );
    // back
    glVertex3f( x0/scale,           y0/scale,           z0/scale         );
    glVertex3f( ((x0+100))/scale,   y0/scale,           z0/scale         );
    glVertex3f( ((x0+100))/scale,   (y0+100)/scale,     z0/scale         );
    glVertex3f( x0/scale,           (y0+100)/scale,     z0/scale         );
    // right
    glVertex3f( (x0+100)/scale,     y0/scale,           (z0+0.5*scale2)/scale   );
    glVertex3f( (x0+100)/scale,     y0/scale,           z0/scale         );
    glVertex3f( (x0+100)/scale,     (y0+100)/scale,     z0/scale         );
    glVertex3f( (x0+100)/scale,     (y0+100)/scale,     (z0+0.5*scale2)/scale   );
    // left
    glVertex3f( x0/scale,           y0/scale,           (z0+0.5*scale2)/scale   );
    glVertex3f( x0/scale,           y0/scale,           z0/scale         );
    glVertex3f( x0/scale,           (y0+100)/scale,     z0/scale         );
    glVertex3f( x0/scale,           (y0+100)/scale,     (z0+0.5*scale2)/scale   );
    // top
    glVertex3f( x0/scale,           (y0+100)/scale,     (z0+0.5*scale2)/scale   );
    glVertex3f( (x0+100)/scale,     (y0+100)/scale,     (z0+0.5*scale2)/scale   );
    glVertex3f( (x0+100)/scale,     (y0+100)/scale,     z0/scale         );
    glVertex3f( x0/scale,           (y0+100)/scale,     z0/scale         );
    // bottom
    glVertex3f( x0/scale,           y0/scale,           (z0+0.5*scale2)/scale   );
    glVertex3f( (x0+100)/scale,     y0/scale,           (z0+0.5*scale2)/scale   );
    glVertex3f( (x0+100)/scale,     y0/scale,           z0/scale         );
    glVertex3f( x0/scale,           y0/scale,           z0/scale         );

    glEnd();

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
}


// Draws a spiral
void Viewer::draw()
{
//    int nbVox = my_SuBIM.sx * my_SuBIM.sy * my_SuBIM.sz;

    float x = x_,
          y = y_,
          z = z_;

//    std::cout << "\nDrawing my voxels: " << std::endl;
    for (int i=0; i<sx; ++i)
    {
        for (int j=0; j<sy; ++j)
        {
            for (int k=0; k<sz; ++k)
            {
                draw_cube( x, y, z );
                z += 0.5*scale2;
//                std::cout << "(" << x << ", " << y << ", " << z  << ")";
            }
//            std::cout << std::endl;
            y+=100;
            z = z_;
        }
//        std::cout << std::endl;
        x+=100;
        y = y_;
    }

//    draw_cube( x, y, z );
}

void Viewer::init()
{
    // Restore previous viewer state.
    restoreStateFromFile();
    setBackgroundColor(QColor(255,255,255));

    x_ = x_in;
    y_ = y_in;
    z_ = z_in;
    sx = sz_x;
    sy = sz_y;
    sz = sz_z;

    // Opens help window
    //  help();
}


QString Viewer::helpString() const
{
    QString text("<h2>S i m p l e V i e w e r</h2>");
    text += "Use the mouse to move the camera around the object. ";
    text += "You can respectively revolve around, zoom and translate with the three mouse buttons. ";
    text += "Left and middle buttons pressed together rotate around the camera view direction axis<br><br>";
    text += "Pressing <b>Alt</b> and one of the function keys (<b>F1</b>..<b>F12</b>) defines a camera keyFrame. ";
    text += "Simply press the function key again to restore it. Several keyFrames define a ";
    text += "camera path. Paths are saved when you quit the application and restored at next start.<br><br>";
    text += "Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, ";
    text += "<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save a snapshot. ";
    text += "See the <b>Keyboard</b> tab in this window for a complete shortcut list.<br><br>";
    text += "Double clicks automates single click actions: A left button double click aligns the closer axis with the camera (if close enough). ";
    text += "A middle button double click fits the zoom of the camera and the right button re-centers the scene.<br><br>";
    text += "A left button double click while holding right button pressed defines the camera <i>Revolve Around Point</i>. ";
    text += "See the <b>Mouse</b> tab and the documentation web pages for details.<br><br>";
    text += "Press <b>Escape</b> to exit the viewer.";
    return text;
}
