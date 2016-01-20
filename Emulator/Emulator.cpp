#include "Emulator.h"

#include "platform.h"
#include "game.h"

Emulator emulator;

static uint8_t _inputMask = 0;
static unsigned long _gameTime = 0;

static const int kFrameRate = 60;
static const int kFrameTime = 1000 / kFrameRate;

Emulator::Emulator() :
    _paused(false),
    _step(false),
    _frameTime(kFrameTime) // run the first update immediately
{
}

void Emulator::start()
{
    setupGame();
}

void Emulator::reset()
{
    _frameTime = kFrameRate;  // run the first update immediately
    _gameTime = 0;
    _inputMask = 0;
}

void Emulator::update(unsigned int dt)
{
    _gameTime += dt;
    _frameTime += dt;

    if (_frameTime >= kFrameTime)
    {
        _frameTime = 0;
        
        if (!_paused || _step)
        {
            loopGame();
            _step = false;
        }
    }
}

void Emulator::stop()
{
}

void Emulator::buttonPressed(int button)
{
    _inputMask |= button;
}

void Emulator::buttonReleased(int button)
{
    _inputMask &= ~button;
}

unsigned long platformMillis(void)
{
    return _gameTime;
}

void platformDelay(unsigned long)
{
}

uint8_t platformInput()
{
    return _inputMask;
}
