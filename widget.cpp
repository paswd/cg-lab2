#include "widget.h"

Widget::Widget(QWidget *parent)
        : QGLWidget(parent)
{
    resize(300,300);
    xRotation = 0;
    yRotation = 0;
    zRotation = 0;
    scale = 1;
}

void Widget::initializeGL()
{
    qglClearColor(Qt::white);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}

void Widget::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nHeight, nHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void Widget::paintGL() // рисование
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка буфера изображения и глубины

    glMatrixMode(GL_MODELVIEW); // устанавливает положение и ориентацию матрице моделирования
    glLoadIdentity();           // загружает единичную матрицу моделирования

    glScalef(scale, scale, scale);        // масштабирование
    glRotatef(xRotation, 1.0f, 0.0f, 0.0f); // поворот по X
    glRotatef(yRotation, 0.0f, 1.0f, 0.0f); // поворот по Y
    glRotatef(zRotation, 0.0f, 0.0f, 1.0f); // поворот по Z

    //drawAxis();

    QColor clr(128, 128, 0, 255);
    QColor clr_lines(0, 0, 0, 255);
    qglColor(clr);
    currentScale = .3;
    qreal big_scale = currentScale * 1.6;
    glBegin(GL_QUADS); //Top
        glVertex3f(currentScale, currentScale, currentScale);
        glVertex3f(-currentScale, currentScale, currentScale);
        glVertex3f(-currentScale, -currentScale, currentScale);
        glVertex3f(currentScale, -currentScale, currentScale);
    glEnd();

    glBegin(GL_QUADS); //Bottom
        glVertex3f(big_scale, big_scale, -currentScale);
        glVertex3f(big_scale, -big_scale, -currentScale);
        glVertex3f(-big_scale, -big_scale, -currentScale);
        glVertex3f(-big_scale, big_scale, -currentScale);
    glEnd();

    glBegin(GL_QUADS); //Side1
        glVertex3f(big_scale, -big_scale, -currentScale);
        glVertex3f(big_scale, big_scale, -currentScale);
        glVertex3f(currentScale, currentScale, currentScale);
        glVertex3f(currentScale, -currentScale, currentScale);
    glEnd();

    glBegin(GL_QUADS); //Side2
        glVertex3f(-big_scale, -big_scale, -currentScale);
        glVertex3f(big_scale, -big_scale, -currentScale);
        glVertex3f(currentScale, -currentScale, currentScale);
        glVertex3f(-currentScale, -currentScale, currentScale);
    glEnd();

    glBegin(GL_QUADS); //Side3
        glVertex3f(-big_scale, big_scale, -currentScale);
        glVertex3f(-big_scale, -big_scale, -currentScale);
        glVertex3f(-currentScale, -currentScale, currentScale);
        glVertex3f(-currentScale, currentScale, currentScale);
    glEnd();

    glBegin(GL_QUADS); //Side4
        glVertex3f(-currentScale, currentScale, currentScale);
        glVertex3f(currentScale, currentScale, currentScale);
        glVertex3f(big_scale, big_scale, -currentScale);
        glVertex3f(-big_scale, big_scale, -currentScale);
    glEnd();

    //LINES
    qglColor(clr_lines);
    glBegin(GL_LINES); //Top
        glVertex3f(currentScale, currentScale, currentScale);
        glVertex3f(-currentScale, currentScale, currentScale);
        glVertex3f(-currentScale, -currentScale, currentScale);
        glVertex3f(currentScale, -currentScale, currentScale);
    glEnd();

    glBegin(GL_LINES); //Bottom
        glVertex3f(big_scale, big_scale, -currentScale);
        glVertex3f(big_scale, -big_scale, -currentScale);
        glVertex3f(-big_scale, -big_scale, -currentScale);
        glVertex3f(-big_scale, big_scale, -currentScale);
    glEnd();

    glBegin(GL_LINES); //Side1
        glVertex3f(big_scale, -big_scale, -currentScale);
        glVertex3f(big_scale, big_scale, -currentScale);
        glVertex3f(currentScale, currentScale, currentScale);
        glVertex3f(currentScale, -currentScale, currentScale);
    glEnd();

    glBegin(GL_LINES); //Side2
        glVertex3f(-big_scale, -big_scale, -currentScale);
        glVertex3f(big_scale, -big_scale, -currentScale);
        glVertex3f(currentScale, -currentScale, currentScale);
        glVertex3f(-currentScale, -currentScale, currentScale);
    glEnd();

    glBegin(GL_LINES); //Side3
        glVertex3f(-big_scale, big_scale, -currentScale);
        glVertex3f(-big_scale, -big_scale, -currentScale);
        glVertex3f(-currentScale, -currentScale, currentScale);
        glVertex3f(-currentScale, currentScale, currentScale);
    glEnd();

    glBegin(GL_LINES); //Side4
        glVertex3f(-currentScale, currentScale, currentScale);
        glVertex3f(currentScale, currentScale, currentScale);
        glVertex3f(big_scale, big_scale, -currentScale);
        glVertex3f(-big_scale, big_scale, -currentScale);
    glEnd();


}

void Widget::mousePressEvent(QMouseEvent* pe) // нажатие клавиши мыши
{
    // запоминаем координату нажатия мыши
    mousePos = pe->pos();
}

void Widget::mouseMoveEvent(QMouseEvent* pe) // изменение положения стрелки мыши
{
    xRotation += 180/scale*(GLfloat)(pe->y()-mousePos.y())/height(); // вычисляем углы поворота
    zRotation += 180/scale*(GLfloat)(pe->x()-mousePos.x())/width();

    mousePos = pe->pos();

    updateGL(); // обновляем изображение
}

void Widget::mouseReleaseEvent(QMouseEvent *pe)
{
}

void Widget::drawAxis()
{
    glLineWidth(3.0f); // устанавливаем ширину линии

    glColor4f(1.00f, 0.00f, 0.00f, 1.0f); // устанавливается цвет последующих линий
    // ось x
    glBegin(GL_LINES); // построение линии
        glVertex3f( 1.0f,  0.0f,  0.0f); // первая точка
        glVertex3f(-1.0f,  0.0f,  0.0f); // вторая точка
    glEnd();

    QColor halfGreen(0, 128, 0, 255);
    qglColor(halfGreen);
    glBegin(GL_LINES);
        // ось y
        glVertex3f( 0.0f,  1.0f,  0.0f);
        glVertex3f( 0.0f, -1.0f,  0.0f);

        glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
        // ось z
        glVertex3f( 0.0f,  0.0f,  1.0f);
        glVertex3f( 0.0f,  0.0f, -1.0f);
    glEnd();
}

void Widget::wheelEvent(QWheelEvent* pe) // вращение колёсика мыши
{
    // если колесико вращаем вперед -- умножаем переменную масштаба на 1.1
    // иначе -- делим на 1.1
    if ((pe->delta())>0) scale*=1.1; else if ((pe->delta())<0) scale/=1.1;
        updateGL();
}
