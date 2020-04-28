#include "wigglecoreworker.h"

#include <cmath>

#include <QTimer>
#include <QDateTime>
#include <QDebug>

#include <Windows.h>

WiggleCoreWorker::WiggleCoreWorker(QObject *parent) : QObject(parent)
{
    intervalTimer = new QTimer(this);
    intervalTimer->setSingleShot(true);
    connect(intervalTimer, &QTimer::timeout, this, &WiggleCoreWorker::intervalExpired);

    mouseMoveUpdateTimer = new QTimer(this);
    mouseMoveUpdateTimer->setSingleShot(false);
    mouseMoveUpdateTimer->setInterval(mouseMoveUpdateIntervalMs);
    connect(mouseMoveUpdateTimer, &QTimer::timeout, this, &WiggleCoreWorker::mouseMoveUpdate);

    handleWiggleDataChanged();
}

void WiggleCoreWorker::setWiggleData(const WiggleData& data)
{
    this->data = data;
    handleWiggleDataChanged();

    intervalTimer->stop();
    mouseMoveUpdateTimer->stop();

    if(data.getIsRunning())
        intervalTimer->start();
}

void WiggleCoreWorker::handleWiggleDataChanged()
{
    intervalTimer->setInterval(data.getWiggleIntervalMs());
}

void WiggleCoreWorker::computeRelativeMouseMovementValues(qint64 timestamp, float& x_OUT, float& y_OUT)
{
    qint64 elapsedDurationMs = timestamp - mouseMoveStartTimestamp;
    double completionPercentage = static_cast<double>(elapsedDurationMs) / static_cast<double>(data.getWiggleDurationMs());
    bool finished = (elapsedDurationMs >= data.getWiggleDurationMs());

    x_OUT = 0;
    y_OUT = 0;

    if(data.getMoveHorizontal())
    {
        if(finished)
            x_OUT = (data.getHorizontalMoveDistancePixels() - horizontalPixelsMoved) * horizontalMovementModifier;
        else
        {
            long requiredHorizontalMovedPixelCount = static_cast<long>(ceil(completionPercentage * data.getHorizontalMoveDistancePixels()));
            x_OUT = (requiredHorizontalMovedPixelCount - horizontalPixelsMoved) * horizontalMovementModifier;
        }
    }

    if(data.getMoveVertical())
    {
        if(finished)
            y_OUT = (data.getVerticalMoveDistancePixels() - verticalPixelsMoved) * verticalMovementModifier;
        else
        {
            long requiredVerticalMovedPixelCount = static_cast<long>(ceil(completionPercentage * data.getVerticalMoveDistancePixels()));
            y_OUT = (requiredVerticalMovedPixelCount - verticalPixelsMoved) * verticalMovementModifier;
        }
    }
}

void WiggleCoreWorker::intervalExpired()
{
    qDebug() << "interval expired";

    horizontalPixelsMoved = 0;
    verticalPixelsMoved = 0;
    mouseMoveStartTimestamp = QDateTime::currentMSecsSinceEpoch();
    mouseMoveUpdateTimer->start();
}

void WiggleCoreWorker::mouseMoveUpdate()
{
    qint64 currentTimestamp = QDateTime::currentMSecsSinceEpoch();
    qint64 elapsedDurationMs = currentTimestamp - mouseMoveStartTimestamp;
    bool finished = (elapsedDurationMs >= data.getWiggleDurationMs());
    float x, y;
    computeRelativeMouseMovementValues(currentTimestamp, x, y);

    qDebug() << "to move: x: " << x << ", y: " << y;
    moveMouseRelative(x, y);

    horizontalPixelsMoved += abs(x);
    verticalPixelsMoved += abs(y);

    if(finished)
    {
        qDebug() << "duration expired";
        qDebug() << "OVERALL PIXELS MOVED: x: " << horizontalPixelsMoved << ", y: " << verticalPixelsMoved;

        if(data.getFlipHorizontalDirection())
            horizontalMovementModifier *= -1;

        if(data.getFlipVerticalDirection())
            verticalMovementModifier *= -1;

        mouseMoveUpdateTimer->stop();
        intervalTimer->start();
    }
}

void WiggleCoreWorker::moveMouseRelative(long x, long y)
{
    INPUT Input = { 0 };
    Input.type = INPUT_MOUSE;

    Input.mi.dx = (LONG)x;
    Input.mi.dy = (LONG)y;
    Input.mi.dwFlags = MOUSEEVENTF_MOVE; // | MOUSEEVENTF_ABSOLUTE

    SendInput(1, &Input, sizeof(INPUT));
}

void WiggleCoreWorker::moveMouseAbsolute(long x, long y)
{
    INPUT Input = { 0 };
    Input.type = INPUT_MOUSE;

    Input.mi.dx = (LONG)x;
    Input.mi.dy = (LONG)y;
    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

    SendInput(1, &Input, sizeof(INPUT));
}
