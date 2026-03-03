#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>

struct LapData {
    int lapNumber;
    int lapTime; // в миллисекундах
};

class Stopwatch : public QObject
{
    Q_OBJECT

public:
    explicit Stopwatch(QObject *parent = nullptr);

public slots:
    void start();
    void stop();
    void reset();
    LapData recordLap(); // теперь возвращает структуру

signals:
    void timeChanged(int milliseconds);

private:
    QTimer *timer;
    int elapsedTime;
    int lastLapTime;
    int lapCounter;
};

#endif // STOPWATCH_H
