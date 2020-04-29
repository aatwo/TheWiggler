#ifndef WIGGLECOREWORKER_H
#define WIGGLECOREWORKER_H

#include <QObject>
#include <QTimer>

#include <wiggledata.h>

class WiggleCoreWorker : public QObject
{
    Q_OBJECT
    public:
        explicit WiggleCoreWorker(QObject *parent = nullptr);

    public slots:

        void setWiggleData(const WiggleData& data);

    private:

        void handleWiggleDataChanged();
        void computeRelativeMouseMovementValues(qint64 elapsedDurationMs, float& x_OUT, float& y_OUT);

        void intervalExpired();
        void mouseMoveUpdate();
        void moveMouseRelative(long x, long y);
        void moveMouseAbsolute(long x, long y);

        WiggleData data;
        QTimer* intervalTimer = nullptr;
        QTimer* mouseMoveUpdateTimer = nullptr;
        const int mouseMoveUpdateIntervalMs = 17; // around 60 fps
        int64_t mouseMoveStartTimestamp = 0;

        long horizontalMovementModifier = 1;
        long horizontalPixelsMoved = 0;

        long verticalMovementModifier = 1;
        long verticalPixelsMoved = 0;
};

#endif // WIGGLECOREWORKER_H
