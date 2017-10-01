#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) // конструктор
    : QGLWidget(parent)
{
    resize(300,300); // задаем размеры окна
}
Widget::~Widget() {

}

void Widget::initializeGL()
{
   qglClearColor(Qt::white); // заполняем экран белым цветом
   glEnable(GL_DEPTH_TEST); // задаем глубину проверки пикселей
   glShadeModel(GL_FLAT); // убираем режим сглаживания цветов
   glEnable(GL_CULL_FACE); // говорим, что будем строить только внешние поверхности
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); // фигуры будут закрашены с обеих сторон
}

void Widget::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nHeight, nHeight); // установка точки обзора
    glMatrixMode(GL_PROJECTION); // установка режима матрицы
    glLoadIdentity(); // загрузка матрицы
}

void Widget::paintGL() // рисование
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка экрана
   glMatrixMode(GL_MODELVIEW); // задаем модельно-видовую матрицу
   glLoadIdentity();           // загрузка единичную матрицу

   QColor halfGreen(0, 128, 0, 255); // устанавливаем цвет квадрата
   qglColor(halfGreen); // задаем цвет
   glBegin(GL_QUADS); // говорим, что рисовать будем прямоугольник
   // задаем вершины многоугольника
   glVertex3f(0.5, 0.5, 0.5);
   glVertex3f(-0.5, 0.5, 0.5);
   glVertex3f(-0.5, -0.5, 0.5);
   glVertex3f(0.5, -0.5, 0.5);
   glEnd();

}
