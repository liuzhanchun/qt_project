/****************************************************************************
** Meta object code from reading C++ file 'WRWaterfallLineElement.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/WRCharting/WRWaterfallLineElement.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WRWaterfallLineElement.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WRWaterfallLineElement_t {
    QByteArrayData data[8];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WRWaterfallLineElement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WRWaterfallLineElement_t qt_meta_stringdata_WRWaterfallLineElement = {
    {
QT_MOC_LITERAL(0, 0, 22), // "WRWaterfallLineElement"
QT_MOC_LITERAL(1, 23, 12), // "colorChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 7), // "WRColor"
QT_MOC_LITERAL(4, 45, 5), // "value"
QT_MOC_LITERAL(5, 51, 15), // "moveableChanged"
QT_MOC_LITERAL(6, 67, 8), // "setColor"
QT_MOC_LITERAL(7, 76, 11) // "setMoveable"

    },
    "WRWaterfallLineElement\0colorChanged\0"
    "\0WRColor\0value\0moveableChanged\0setColor\0"
    "setMoveable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WRWaterfallLineElement[] = {

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

void WRWaterfallLineElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WRWaterfallLineElement *_t = static_cast<WRWaterfallLineElement *>(_o);
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
            typedef void (WRWaterfallLineElement::*_t)(WRColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRWaterfallLineElement::colorChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (WRWaterfallLineElement::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRWaterfallLineElement::moveableChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject WRWaterfallLineElement::staticMetaObject = {
    { &WRWaterfallGaugeElement::staticMetaObject, qt_meta_stringdata_WRWaterfallLineElement.data,
      qt_meta_data_WRWaterfallLineElement,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WRWaterfallLineElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WRWaterfallLineElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WRWaterfallLineElement.stringdata0))
        return static_cast<void*>(this);
    return WRWaterfallGaugeElement::qt_metacast(_clname);
}

int WRWaterfallLineElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WRWaterfallGaugeElement::qt_metacall(_c, _id, _a);
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
void WRWaterfallLineElement::colorChanged(WRColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WRWaterfallLineElement::moveableChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_WRWaterfallDataFrameLineElement_t {
    QByteArrayData data[6];
    char stringdata0[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WRWaterfallDataFrameLineElement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WRWaterfallDataFrameLineElement_t qt_meta_stringdata_WRWaterfallDataFrameLineElement = {
    {
QT_MOC_LITERAL(0, 0, 31), // "WRWaterfallDataFrameLineElement"
QT_MOC_LITERAL(1, 32, 15), // "positionUpdated"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 5), // "value"
QT_MOC_LITERAL(4, 55, 15), // "positionChanged"
QT_MOC_LITERAL(5, 71, 11) // "setPosition"

    },
    "WRWaterfallDataFrameLineElement\0"
    "positionUpdated\0\0value\0positionChanged\0"
    "setPosition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WRWaterfallDataFrameLineElement[] = {

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

void WRWaterfallDataFrameLineElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WRWaterfallDataFrameLineElement *_t = static_cast<WRWaterfallDataFrameLineElement *>(_o);
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
            typedef void (WRWaterfallDataFrameLineElement::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRWaterfallDataFrameLineElement::positionUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (WRWaterfallDataFrameLineElement::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRWaterfallDataFrameLineElement::positionChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject WRWaterfallDataFrameLineElement::staticMetaObject = {
    { &WRWaterfallLineElement::staticMetaObject, qt_meta_stringdata_WRWaterfallDataFrameLineElement.data,
      qt_meta_data_WRWaterfallDataFrameLineElement,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WRWaterfallDataFrameLineElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WRWaterfallDataFrameLineElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WRWaterfallDataFrameLineElement.stringdata0))
        return static_cast<void*>(this);
    return WRWaterfallLineElement::qt_metacast(_clname);
}

int WRWaterfallDataFrameLineElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WRWaterfallLineElement::qt_metacall(_c, _id, _a);
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
void WRWaterfallDataFrameLineElement::positionUpdated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WRWaterfallDataFrameLineElement::positionChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_WRWaterfallDataPointLineElement_t {
    QByteArrayData data[6];
    char stringdata0[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WRWaterfallDataPointLineElement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WRWaterfallDataPointLineElement_t qt_meta_stringdata_WRWaterfallDataPointLineElement = {
    {
QT_MOC_LITERAL(0, 0, 31), // "WRWaterfallDataPointLineElement"
QT_MOC_LITERAL(1, 32, 15), // "positionUpdated"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 5), // "value"
QT_MOC_LITERAL(4, 55, 15), // "positionChanged"
QT_MOC_LITERAL(5, 71, 11) // "setPosition"

    },
    "WRWaterfallDataPointLineElement\0"
    "positionUpdated\0\0value\0positionChanged\0"
    "setPosition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WRWaterfallDataPointLineElement[] = {

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

void WRWaterfallDataPointLineElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WRWaterfallDataPointLineElement *_t = static_cast<WRWaterfallDataPointLineElement *>(_o);
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
            typedef void (WRWaterfallDataPointLineElement::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRWaterfallDataPointLineElement::positionUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (WRWaterfallDataPointLineElement::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRWaterfallDataPointLineElement::positionChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject WRWaterfallDataPointLineElement::staticMetaObject = {
    { &WRWaterfallLineElement::staticMetaObject, qt_meta_stringdata_WRWaterfallDataPointLineElement.data,
      qt_meta_data_WRWaterfallDataPointLineElement,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WRWaterfallDataPointLineElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WRWaterfallDataPointLineElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WRWaterfallDataPointLineElement.stringdata0))
        return static_cast<void*>(this);
    return WRWaterfallLineElement::qt_metacast(_clname);
}

int WRWaterfallDataPointLineElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WRWaterfallLineElement::qt_metacall(_c, _id, _a);
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
void WRWaterfallDataPointLineElement::positionUpdated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WRWaterfallDataPointLineElement::positionChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
