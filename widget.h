#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui>
#include <QGLWidget>

const size_t SIDES_NUM = 6;
const size_t VERTEX_NUM = 4;
const size_t VECTORS_NUM = 3;

class Widget : public QGLWidget
{
public:
    Widget(QWidget *parent = 0);

protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent* pe);
    void wheelEvent(QWheelEvent *);

private:
    int xRotation, yRotation, zRotation,scale;
    QPoint mousePos;
    qreal currentScale;
    double Coordinates[SIDES_NUM][VERTEX_NUM][VECTORS_NUM];

    void drawAxis();
    void drawPiramide();
    void fillCoordinateMatrix();
};

#endif // WIDGET_H
