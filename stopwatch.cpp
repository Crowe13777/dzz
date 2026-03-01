#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent)
    : QObject(parent)
    , timer(new QTimer(this))
    , elapsedTime(0)
    , lastLapTime(0)
    , lapCounter(0)
{
    connect(timer, &QTimer::timeout, this, [this]() {
        elapsedTime += 100; // 100 мс = 0.1 сек
        emit timeChanged(elapsedTime);
    });
}

void Stopwatch::start()
{
    timer->start(100); // обновление каждые 0.1 сек
}

void Stopwatch::stop()
{
    timer->stop();
}

void Stopwatch::reset()
{
    timer->stop();
    elapsedTime = 0;
    lastLapTime = 0;
    lapCounter = 0;
    emit timeChanged(0);
}

void Stopwatch::recordLap()
{
    lapCounter++;
    int currentLapTime = elapsedTime - lastLapTime;
    lastLapTime = elapsedTime;
    emit lapRecorded(lapCounter, currentLapTime);
}
