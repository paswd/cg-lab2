#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGLWidget>

namespace Ui {
class Widget;
}

class Widget : public QGLWidget
{
    Q_OBJECT

public:
    //explicit Widget(QWidget *parent = 0);

    Widget(QWidget *parent = 0);
    ~Widget();

    void initializeGL();

    void resizeGL(int nWidth, int nHeight);

    void paintGL(); // рисование

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
