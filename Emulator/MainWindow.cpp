#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>

#include "platform.h"
#include "game.h"

#include "GameInput.h"

static const int kTimerDelay = 1000 / 60;

MainWindow *MainWindow::_instance(NULL);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _displayWidget(NULL)
{
    _instance = this;
    setFocusPolicy(Qt::StrongFocus);
    
    _ui->setupUi(this);
    _displayWidget = _ui->displayWidget;
    
    setupToolBar(_ui->toolBar);
    setupActions();

    emulator.start();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(runUpdate()));
    timer->start(kTimerDelay);
    
    setFocus();
}

MainWindow::~MainWindow()
{
    _instance = NULL;
    delete _ui;
}

#pragma mark -
#pragma mark Update

void MainWindow::runUpdate()
{
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    qint64 dt = currentTime - _lastFrameTime;
    _lastFrameTime = currentTime;
    emulator.update(dt);
}

#pragma mark -
#pragma mark Events

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    emulator.buttonPressed(getButtonFromKey(key));
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    int key = event->key();
    emulator.buttonReleased(getButtonFromKey(key));
}

#pragma mark -
#pragma mark Screen Buffer

void MainWindow::copyScreenBuffer(const unsigned char *screenBuffer, int bufferWidth, int bufferHeight)
{
    _displayWidget->copyScreenBuffer(screenBuffer, bufferWidth, bufferHeight);
}

#pragma mark -
#pragma mark Platform

void platformRenderScreen(unsigned const char* screenBuffer, int width, int height)
{
    MainWindow::instance()->copyScreenBuffer(screenBuffer, width, height);
}

#pragma mark -
#pragma mark Emulator

void MainWindow::setPauseMode(bool pauseMode)
{
    emulator.setPaused(pauseMode);
    
    _ui->actionPause->setChecked(pauseMode);
    _ui->actionPlay->setChecked(!pauseMode);
}

#pragma mark -
#pragma mark Toolbar

void MainWindow::setupToolBar(QToolBar *toolBar)
{
    QWidget* emptyLeft = new QWidget();
    emptyLeft->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    toolBar->insertWidget(_ui->actionPlay, emptyLeft);
    
    QWidget* emptyRight = new QWidget();
    emptyRight->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    toolBar->insertWidget(_ui->actionStep, emptyRight);
}

#pragma mark -
#pragma mark Actions

void MainWindow::setupActions()
{
    QAction *actionPlay   = _ui->actionPlay;
    QAction *actionPause  = _ui->actionPause;
    QAction *actionStep   = _ui->actionStep;
    
    // set state
    setPauseMode(emulator.paused());
    
    // connect slots
    connect(actionStep,  SIGNAL(triggered()), this, SLOT(onActionStep()));
    connect(actionPlay,  SIGNAL(triggered()), this, SLOT(onActionPlay()));
    connect(actionPause, SIGNAL(triggered()), this, SLOT(onActionPause()));
}

void MainWindow::onActionPlay()
{
    setPauseMode(false);
}

void MainWindow::onActionPause()
{
    setPauseMode(true);
}

void MainWindow::onActionStep()
{
    setPauseMode(true);
    emulator.step();
}

void MainWindow::onActionSnapshot()
{
    DisplayWidget *widget = displayWidget();
    QPixmap pixmap(widget->size());
    widget->render(&pixmap);

    QDir dir;
    QFileInfoList list = dir.entryInfoList(QStringList("screenshot-*.png"));

    pixmap.save(QString("screenshot-%1.png").arg(list.size()));
}
