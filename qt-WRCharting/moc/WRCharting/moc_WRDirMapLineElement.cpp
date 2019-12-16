/****************************************************************************
** Meta object code from reading C++ file 'WRDirMapLineElement.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/WRCharting/WRDirMapLineElement.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WRDirMapLineElement.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WRDirMapLineElement_t {
    QByteArrayData data[8];
    char stringdata0[85];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WRDirMapLineElement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WRDirMapLineElement_t qt_meta_stringdata_WRDirMapLineElement = {
    {
QT_MOC_LITERAL(0, 0, 19), // "WRDirMapLineElement"
QT_MOC_LITERAL(1, 20, 12), // "colorChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 7), // "WRColor"
QT_MOC_LITERAL(4, 42, 5), // "value"
QT_MOC_LITERAL(5, 48, 15), // "moveableChanged"
QT_MOC_LITERAL(6, 64, 8), // "setColor"
QT_MOC_LITERAL(7, 73, 11) // "setMoveable"

    },
    "WRDirMapLineElement\0colorChanged\0\0"
    "WRColor\0value\0moveableChanged\0setColor\0"
    "setMoveable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WRDirMapLineElement[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   40,    2, 0x0a /* Public */,
       7,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Bool,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Bool,    4,

       0        // eod
};

void WRDirMapLineElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WRDirMapLineElement *_t = static_cast<WRDirMapLineElement *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->colorChanged((*reinterpret_cast< WRColor(*)>(_a[1]))); break;
        case 1: _t->moveableChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->setColor((*reinterpret_cast< WRColor(*)>(_a[1]))); break;
        case 3: _t->setMoveable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (WRDirMapLineElement::*_t)(WRColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRDirMapLineElement::colorChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (WRDirMapLineElement::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRDirMapLineElement::moveableChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject WRDirMapLineElement::staticMetaObject = {
    { &WRDirMapGaugeElement::staticMetaObject, qt_meta_stringdata_WRDirMapLineElement.data,
      qt_meta_data_WRDirMapLineElement,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WRDirMapLineElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WRDirMapLineElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WRDirMapLineElement.stringdata0))
        return static_cast<void*>(this);
    return WRDirMapGaugeElement::qt_metacast(_clname);
}

int WRDirMapLineElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WRDirMapGaugeElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void WRDirMapLineElement::colorChanged(WRColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WRDirMapLineElement::moveableChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_WRDirMapDataPointLineElement_t {
    QByteArrayData data[6];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WRDirMapDataPointLineElement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WRDirMapDataPointLineElement_t qt_meta_stringdata_WRDirMapDataPointLineElement = {
    {
QT_MOC_LITERAL(0, 0, 28), // "WRDirMapDataPointLineElement"
QT_MOC_LITERAL(1, 29, 15), // "positionUpdated"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 5), // "value"
QT_MOC_LITERAL(4, 52, 15), // "positionChanged"
QT_MOC_LITERAL(5, 68, 11) // "setPosition"

    },
    "WRDirMapDataPointLineElement\0"
    "positionUpdated\0\0value\0positionChanged\0"
    "setPosition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WRDirMapDataPointLineElement[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void WRDirMapDataPointLineElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WRDirMapDataPointLineElement *_t = static_cast<WRDirMapDataPointLineElement *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->positionUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->positionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setPosition((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (WRDirMapDataPointLineElement::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRDirMapDataPointLineElement::positionUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (WRDirMapDataPointLineElement::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRDirMapDataPointLineElement::positionChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject WRDirMapDataPointLineElement::staticMetaObject = {
    { &WRDirMapLineElement::staticMetaObject, qt_meta_stringdata_WRDirMapDataPointLineElement.data,
      qt_meta_data_WRDirMapDataPointLineElement,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WRDirMapDataPointLineElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WRDirMapDataPointLineElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WRDirMapDataPointLineElement.stringdata0))
        return static_cast<void*>(this);
    return WRDirMapLineElement::qt_metacast(_clname);
}

int WRDirMapDataPointLineElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WRDirMapLineElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void WRDirMapDataPointLineElement::positionUpdated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WRDirMapDataPointLineElement::positionChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_WRDirMapDataAngleLineElement_t {
    QByteArrayData data[6];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WRDirMapDataAngleLineElement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WRDirMapDataAngleLineElement_t qt_meta_stringdata_WRDirMapDataAngleLineElement = {
    {
QT_MOC_LITERAL(0, 0, 28), // "WRDirMapDataAngleLineElement"
QT_MOC_LITERAL(1, 29, 15), // "positionUpdated"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 5), // "value"
QT_MOC_LITERAL(4, 52, 15), // "positionChanged"
QT_MOC_LITERAL(5, 68, 11) // "setPosition"

    },
    "WRDirMapDataAngleLineElement\0"
    "positionUpdated\0\0value\0positionChanged\0"
    "setPosition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WRDirMapDataAngleLineElement[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    3,

       0        // eod
};

void WRDirMapDataAngleLineElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WRDirMapDataAngleLineElement *_t = static_cast<WRDirMapDataAngleLineElement *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->positionUpdated((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->positionChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->setPosition((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (WRDirMapDataAngleLineElement::*_t)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRDirMapDataAngleLineElement::positionUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (WRDirMapDataAngleLineElement::*_t)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRDirMapDataAngleLineElement::positionChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject WRDirMapDataAngleLineElement::staticMetaObject = {
    { &WRDirMapLineElement::staticMetaObject, qt_meta_stringdata_WRDirMapDataAngleLineElement.data,
      qt_meta_data_WRDirMapDataAngleLineElement,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WRDirMapDataAngleLineElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WRDirMapDataAngleLineElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WRDirMapDataAngleLineElement.stringdata0))
        return static_cast<void*>(this);
    return WRDirMapLineElement::qt_metacast(_clname);
}

int WRDirMapDataAngleLineElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WRDirMapLineElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void WRDirMapDataAngleLineElement::positionUpdated(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WRDirMapDataAngleLineElement::positionChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
