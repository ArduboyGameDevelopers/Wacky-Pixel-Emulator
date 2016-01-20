#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QtGlobal>
#include <QWidget>
#include <QPainter>

#include "Constants.h"

typedef QRect Rect;

class RectList
{
public:
    RectList(int capacity, int r, int g, int b, int a = 255);
    virtual ~RectList();

public:
    void paint(QPainter* painter);
    void clear();
    void add(int x, int y, int w, int h);

public:
    inline int capacity() const { return _capacity; }
    inline int count() const { return _count; }

private:
    Rect*  _rects;
    QColor _color;
    int    _capacity;
    int    _count;
};

class DisplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayWidget(QWidget *parent = 0);
    virtual ~DisplayWidget();

public:
    void copyScreenBuffer(unsigned const char* screenBuffer, int bufferWidth, int bufferHeight);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void enterEvent(QEvent *event)  Q_DECL_OVERRIDE;

private:
    RectList _pixelRects;
};

#endif // DISPLAYWIDGET_H
