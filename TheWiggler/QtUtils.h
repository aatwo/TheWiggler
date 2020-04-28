#ifndef QTUTILS_H
#define QTUTILS_H

#include <QObject>

// These macros define the following:
//      1. member variable
//      2. read function for the member variable
//      3. write function for the member variable
//      4. QT property macro to define the property so QT understands it
// Notes:
//      - For the qmlName ensure the variable starts with a capital letter
//      - These macros do NOT define the onChange signals
//      - The CREF variant makes the setter take a const reference type
#define READ_WRITE_QML_PROPERTY(type, qmlName, defaultValue) \
    public: \
        Q_PROPERTY(type qmlName MEMBER m_##qmlName READ get##qmlName WRITE set##qmlName) \
        void set##qmlName(type v) { m_##qmlName = v; } \
        type get##qmlName() const { return m_##qmlName; } \
    private: \
        type m_##qmlName = defaultValue;

#define READ_WRITE_QML_PROPERTY_CREF(type, qmlName, defaultValue) \
    public: \
        Q_PROPERTY(type qmlName MEMBER m_##qmlName READ get##qmlName WRITE set##qmlName) \
        void set##qmlName(const type& v) { m_##qmlName = v; } \
        type get##qmlName() const { return m_##qmlName; } \
    private: \
        type m_##qmlName = defaultValue;

#endif // QTUTILS_H
