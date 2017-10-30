#include "widget.h"
#include <QDebug>

const GLfloat GL_PI = 3.1415926;

Widget::Widget(QWidget *parent)
        : QGLWidget(parent)
{
    resize(300,300);
    xRotation = 0;
    yRotation = 0;
    zRotation = 0;
    scale = 1;
}

const double LARGE_SIDE = 1.6;

void Widget::fillCoordinateMatrix()
{
    double tmp[SIDES_NUM][VERTEX_NUM][VECTORS_NUM] = {
        {
            {1, 1, 1},
            {-1, 1, 1},
            {-1, -1, 1},
            {1, -1, 1}
        },{
            {LARGE_SIDE, LARGE_SIDE, -1},
            {LARGE_SIDE, -LARGE_SIDE, -1},
            {-LARGE_SIDE, -LARGE_SIDE, -1},
            {-LARGE_SIDE, LARGE_SIDE, -1}
        },{
            {-1, -1, 1},
            {-1, 1, 1},
            {-LARGE_SIDE, LARGE_SIDE, -1},
            {-LARGE_SIDE, -LARGE_SIDE, -1}
        },{
            {-LARGE_SIDE, -LARGE_SIDE, -1},
            {LARGE_SIDE, -LARGE_SIDE, -1},
            {1, -1, 1},
            {-1, -1, 1}
        },{
            {LARGE_SIDE, -LARGE_SIDE, -1},
            {LARGE_SIDE, LARGE_SIDE, -1},
            {1, 1, 1},
            {1, -1, 1}
        },{
            {-1, 1, 1},
            {1, 1, 1},
            {LARGE_SIDE, LARGE_SIDE, -1},
            {-LARGE_SIDE, LARGE_SIDE, -1}
        }
    };
    for (size_t i = 0; i < SIDES_NUM; i++) {
        for (size_t j = 0; j < VERTEX_NUM; j++) {
            for (size_t k = 0; k < VECTORS_NUM; k++) {
                Coordinates[i][j][k] = tmp[i][j][k];
            }
        }
    }
}

void Widget::initializeGL()
{
    qglClearColor(Qt::white);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    fillCoordinateMatrix();
}

void Widget::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nHeight, nHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void Widget::paintGL()
{
    drawPiramide();
}

void Widget::mousePressEvent(QMouseEvent* pe)
{
    mousePos = pe->pos();
}

void Widget::mouseMoveEvent(QMouseEvent* pe)
{
    xRotation += (pe->y() - mousePos.y()) * 1.1 * GL_PI / 180;
    zRotation += (pe->x() - mousePos.x()) * 1.1 * GL_PI / 180;

    updateGL();
}

void Widget::mouseReleaseEvent(QMouseEvent *pe)
{
}

void Widget::drawAxis()
{
    glLineWidth(3.0f);

    glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
    glBegin(GL_LINES);
        glVertex3f( 1.0f,  0.0f,  0.0f);
        glVertex3f(-1.0f,  0.0f,  0.0f);
    glEnd();

    QColor halfGreen(0, 128, 0, 255);
    qglColor(halfGreen);
    glBegin(GL_LINES);
        glVertex3f( 0.0f,  1.0f,  0.0f);
        glVertex3f( 0.0f, -1.0f,  0.0f);

        glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
        glVertex3f( 0.0f,  0.0f,  1.0f);
        glVertex3f( 0.0f,  0.0f, -1.0f);
    glEnd();
}

void Widget::wheelEvent(QWheelEvent* pe)
{
    if ((pe->delta()) > 0) {
        scale *= 1.1;
    } else if ((pe->delta())<0) {
        scale /= 1.1;
    }
    updateGL();
}

void Widget::drawPiramide() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(scale, scale, scale);
    glRotatef(xRotation, 1.0f, 0.0f, 0.0f);
    glRotatef(yRotation, 0.0f, 1.0f, 0.0f);
    glRotatef(zRotation, 0.0f, 0.0f, 1.0f);

    //drawAxis();

    QColor clr(0, 64, 128, 255);
    //QColor clr_lines(0, 0, 0, 255);
    qglColor(clr);

    currentScale = .3;
    qreal big_scale = currentScale * 1.6;

    for (size_t i = 0; i < SIDES_NUM; i++) {
        glBegin(GL_LINE_LOOP);
            for (size_t j = 0; j < VERTEX_NUM; j++) {
                glVertex3f(currentScale * Coordinates[i][j][0], currentScale * Coordinates[i][j][1],
                        currentScale * Coordinates[i][j][2]);
                qDebug() << "[" << i << ", " << j << "]\n";
                qDebug() << "{" << Coordinates[i][j][0] << ", " << Coordinates[i][j][1] << ", " << Coordinates[i][j][2] << "}\n";
            }
        glEnd();
    }
    /*if (1) {
        glBegin(GL_LINE_LOOP); //Top
            glVertex3f(currentScale, currentScale, currentScale);
            glVertex3f(-currentScale, currentScale, currentScale);
            glVertex3f(-currentScale, -currentScale, currentScale);
            glVertex3f(currentScale, -currentScale, currentScale);
        glEnd();
    }*/

    /*if (1) {
            glBegin(GL_POLYGON); //Top
                glVertex3f(currentScale, currentScale, currentScale);
                glVertex3f(-currentScale, currentScale, currentScale);
                glVertex3f(-currentScale, -currentScale, currentScale);
                glVertex3f(currentScale, -currentScale, currentScale);
            glEnd();
        }

        if (1) {
            glBegin(GL_POLYGON); //Bottom
                glVertex3f(big_scale, big_scale, -currentScale);
                glVertex3f(big_scale, -big_scale, -currentScale);
                glVertex3f(-big_scale, -big_scale, -currentScale);
                glVertex3f(-big_scale, big_scale, -currentScale);
            glEnd();
        }

        if (1) {
            glBegin(GL_POLYGON); //Side1
                glVertex3f(-currentScale, -currentScale, currentScale);
                glVertex3f(-currentScale, currentScale, currentScale);
                glVertex3f(-big_scale, big_scale, -currentScale);
                glVertex3f(-big_scale, -big_scale, -currentScale);
            glEnd();
        }

        if (1) {
            glBegin(GL_POLYGON); //Side2
                glVertex3f(-big_scale, -big_scale, -currentScale);
                glVertex3f(big_scale, -big_scale, -currentScale);
                glVertex3f(currentScale, -currentScale, currentScale);
                glVertex3f(-currentScale, -currentScale, currentScale);
            glEnd();
        }

        if (1) {
            glBegin(GL_POLYGON); //Side3
                glVertex3f(big_scale, -big_scale, -currentScale);
                glVertex3f(big_scale, big_scale, -currentScale);
                glVertex3f(currentScale, currentScale, currentScale);
                glVertex3f(currentScale, -currentScale, currentScale);
            glEnd();
        }

        if (1) {
            glBegin(GL_POLYGON); //Side4
                glVertex3f(-currentScale, currentScale, currentScale);
                glVertex3f(currentScale, currentScale, currentScale);
                glVertex3f(big_scale, big_scale, -currentScale);
                glVertex3f(-big_scale, big_scale, -currentScale);
            glEnd();
        }*/
}
