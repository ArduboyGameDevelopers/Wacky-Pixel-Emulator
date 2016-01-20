#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGlobal>
#include <QtWidgets>

#include "Emulator.h"

namespace Ui {
class MainWindow;
}

class QToolBar;
class DisplayWidget;
class TilesWidget;
class EditorTool;
class CharacterButton;
class Level;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void runUpdate();

    void onActionPlay();
    void onActionPause();
    void onActionStep();
    void onActionSnapshot();

public:
    void copyScreenBuffer(unsigned const char* screenBuffer, int bufferWidth, int bufferHeight);
    
public:
    inline static MainWindow* instance() { return _instance; }
    inline DisplayWidget *displayWidget() const { return _displayWidget; }
    inline Ui::MainWindow* ui() const { return _ui; }
    
protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private:
    void setupToolBar(QToolBar* toolBar);
    void setupActions();
    void setPauseMode(bool pauseMode);

private:
    static MainWindow *_instance;
    Ui::MainWindow *_ui;
    DisplayWidget *_displayWidget;
    EditorTool *_lastTool;
    qint64 _lastFrameTime;
    QList<CharacterButton *> _characterButtons;
};

#endif // MAINWINDOW_H
