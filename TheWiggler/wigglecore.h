#ifndef WIGGLECORE_H
#define WIGGLECORE_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QPointer>

#include <wiggledata.h>
#include <wigglecoreworker.h>

class WiggleCore : public QObject
{
        Q_OBJECT
    public:

        explicit WiggleCore(QObject* parent = nullptr);
        ~WiggleCore();

        Q_INVOKABLE void setWiggleData(const WiggleData& wiggleData);
        Q_INVOKABLE WiggleData getWiggleData() const;

        Q_INVOKABLE void start();
        Q_INVOKABLE void stop();

    private:

        void updateWiggleWorker();

        WiggleData wiggleData;
        QPointer<WiggleCoreWorker> wiggleWorker;
        QThread wiggleWorkerThread;

};

#endif // WIGGLECORE_H
