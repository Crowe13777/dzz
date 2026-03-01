#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , stopwatch(new Stopwatch(this))
    , isRunning(false)
{
    ui->setupUi(this);

    // Инициализация начального состояния
    ui->timeLabel->setText("00:00.0");
    ui->lapButton->setEnabled(false);

    // Подключение сигналов
    connect(stopwatch, &Stopwatch::timeChanged, this, &MainWindow::updateTimeDisplay);
    connect(stopwatch, &Stopwatch::lapRecorded, this, &MainWindow::addLapToDisplay);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startStopButton_clicked()
{
    if (!isRunning) {
        stopwatch->start();
        ui->startStopButton->setText("Стоп");
        ui->lapButton->setEnabled(true);
        isRunning = true;
    } else {
        stopwatch->stop();
        ui->startStopButton->setText("Старт");
        ui->lapButton->setEnabled(false);
        isRunning = false;
    }
}

void MainWindow::on_clearButton_clicked()
{
    stopwatch->reset();
    ui->lapsBrowser->clear();
    ui->startStopButton->setText("Старт");
    ui->lapButton->setEnabled(false);
    isRunning = false;
}

void MainWindow::on_lapButton_clicked()
{
    stopwatch->recordLap();
}

void MainWindow::updateTimeDisplay(int milliseconds)
{
    int seconds = milliseconds / 1000;
    int centiseconds = (milliseconds % 1000) / 100;

    QString timeText = QString("%1:%2.%3")
        .arg(seconds / 60, 2, 10, QChar('0'))
        .arg(seconds % 60, 2, 10, QChar('0'))
        .arg(centiseconds);

    ui->timeLabel->setText(timeText);
}

void MainWindow::addLapToDisplay(int lapNumber, int lapTime)
{
    int seconds = lapTime / 1000;
    int centiseconds = (lapTime % 1000) / 100;

    QString lapText = QString("Круг %1, время: %2.%3 сек")
        .arg(lapNumber)
        .arg(seconds)
        .arg(centiseconds);

    ui->lapsBrowser->append(lapText);
}
