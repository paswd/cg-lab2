#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui>
#include <QGLWidget>

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
    int xRotation,yRotation,zRotation,scale;
    QPoint mousePos;
    qreal currentScale;
    void drawAxis();
};

#endif // WIDGET_H
