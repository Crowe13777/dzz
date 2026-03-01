#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>

class Stopwatch : public QObject
{
    Q_OBJECT

public:
    explicit Stopwatch(QObject *parent = nullptr);

public slots:
    void start();
    void stop();
    void reset();
    void recordLap();

signals:
    void timeChanged(int milliseconds);
    void lapRecorded(int lapNumber, int lapTime);

private:
    QTimer *timer;
    int elapsedTime;
    int lastLapTime;
    int lapCounter;
};

#endif // STOPWATCH_H
