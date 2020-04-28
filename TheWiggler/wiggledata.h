#ifndef WIGGLEDATA_H
#define WIGGLEDATA_H

#include <QObject>
#include <QString>

#include <QtUtils.h>

struct WiggleData
{
    Q_GADGET
    public:

    READ_WRITE_QML_PROPERTY(int64_t, WiggleIntervalMs, 5000)
    READ_WRITE_QML_PROPERTY(int64_t, WiggleDurationMs, 1000)
    READ_WRITE_QML_PROPERTY(bool, MoveHorizontal, true)
    READ_WRITE_QML_PROPERTY(bool, MoveVertical, true)
    READ_WRITE_QML_PROPERTY(int64_t, HorizontalMoveDistancePixels, 500)
    READ_WRITE_QML_PROPERTY(int64_t, VerticalMoveDistancePixels, 500)
    READ_WRITE_QML_PROPERTY(bool, FlipHorizontalDirection, true)
    READ_WRITE_QML_PROPERTY(bool, FlipVerticalDirection, true)
    READ_WRITE_QML_PROPERTY(bool, IsRunning, false)

};

// This class is used to create instances of C++ classes in QML (you cannot currently do this purely in JS)
class WiggleDataFactory : public QObject
{
    Q_OBJECT
    public:
        explicit WiggleDataFactory(QObject* parent = nullptr) : QObject(parent) {}

        Q_INVOKABLE WiggleData make(){ return wiggleData; }

    private:

        WiggleData wiggleData;

};

#endif // WIGGLEDATA_H
