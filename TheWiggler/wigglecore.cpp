#include "wigglecore.h"

#include <QDebug>
#include <QMetaObject>

WiggleCore::WiggleCore(QObject* parent)
    : QObject(parent)
{
    wiggleWorker = new WiggleCoreWorker();
    wiggleWorker->moveToThread(&wiggleWorkerThread);
    wiggleWorkerThread.start();
}

WiggleCore::~WiggleCore()
{
    if(wiggleWorkerThread.isRunning())
    {
        wiggleWorkerThread.quit();
        wiggleWorkerThread.wait();
    }
}

void WiggleCore::setWiggleData(const WiggleData& wiggleData)
{
    this->wiggleData = wiggleData;
    updateWiggleWorker();
}

WiggleData WiggleCore::getWiggleData() const
{
    return wiggleData;
}

void WiggleCore::start()
{
    wiggleData.setIsRunning(true);
    updateWiggleWorker();
}

void WiggleCore::stop()
{
    wiggleData.setIsRunning(false);
    updateWiggleWorker();
}

void WiggleCore::updateWiggleWorker()
{
    QMetaObject::invokeMethod(wiggleWorker.data(), "setWiggleData", Q_ARG(WiggleData, this->wiggleData));
}
