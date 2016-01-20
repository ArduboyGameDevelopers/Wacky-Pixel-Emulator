#include "DisplayWidget.h"

#include "game.h"
#include "Emulator.h"
#include "Constants.h"

#include <Arduino.h>

#include <QPainter>
#include <QDebug>

#define RECT_COLOR_PIXEL 0, 0, 0
#define RECT_COLOR_GRID  241, 245, 248

DisplayWidget::DisplayWidget(QWidget *parent) :
    QWidget(parent),
    _pixelRects(DISPLAY_WIDTH * DISPLAY_HEIGHT, RECT_COLOR_PIXEL)
{
    setAutoFillBackground(false);
    setMouseTracking(true);
}

DisplayWidget::~DisplayWidget()
{
}

void DisplayWidget::copyScreenBuffer(const unsigned char *screenBuffer, int bufferWidth, int bufferHeight)
{
    _pixelRects.clear();
    for (int y = 0; y < bufferHeight; y++)
    {
        for (int x = 0; x < bufferWidth; x++)
        {
            int row = y / 8;
            int index = row * bufferWidth + x;
            int bit = screenBuffer[index] & (1 << (y % 8));
            if (!bit)
            {
                _pixelRects.add(x * PIXEL_WIDTH, y * PIXEL_HEIGHT, PIXEL_WIDTH, PIXEL_HEIGHT);
            }
        }
    }

    repaint();
}

void DisplayWidget::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    
    // background
    painter.fillRect(0, 0, width(), height(), Qt::white);
    
    // draw pixels
    _pixelRects.paint(&painter);

    painter.end();
}

void DisplayWidget::keyPressEvent(QKeyEvent *event)
{
}

void DisplayWidget::keyReleaseEvent(QKeyEvent *event)
{
}

void DisplayWidget::mousePressEvent(QMouseEvent *event)
{
}

void DisplayWidget::mouseMoveEvent(QMouseEvent *event)
{
}

void DisplayWidget::mouseReleaseEvent(QMouseEvent *event)
{
}

void DisplayWidget::leaveEvent(QEvent *)
{
}

void DisplayWidget::enterEvent(QEvent *)
{
}

RectList::RectList(int capacity, int r, int g, int b, int a) :
    _color(r, g, b, a),
    _capacity(capacity),
    _count(0)
{
    _rects = (Rect*) malloc(capacity * sizeof(Rect));
}

RectList::~RectList()
{
    free(_rects);
}

void RectList::paint(QPainter *painter)
{
    for (int i = 0; i < count(); ++i)
    {
        painter->fillRect(_rects[i], _color);
    }
}

void RectList::clear()
{
    _count = 0;
}

void RectList::add(int x, int y, int w, int h)
{
    Q_ASSERT(_count < _capacity);
    _rects[_count++] = Rect(x, y, w, h);
}
