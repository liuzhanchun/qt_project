/****************************************************************************
** Meta object code from reading C++ file 'WROscilloLineElement.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/WRCharting/WROscilloLineElement.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WROscilloLineElement.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WROscilloLineElement_t {
    QByteArrayData data[8];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WROscilloLineElement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WROscilloLineElement_t qt_meta_stringdata_WROscilloLineElement = {
    {
QT_MOC_LITERAL(0, 0, 20), // "WROscilloLineElement"
QT_MOC_LITERAL(1, 21, 12), // "colorChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 7), // "WRColor"
QT_MOC_LITERAL(4, 43, 5), // "value"
QT_MOC_LITERAL(5, 49, 15), // "moveableChanged"
QT_MOC_LITERAL(6, 65, 8), // "setColor"
QT_MOC_LITERAL(7, 74, 11) // "setMoveable"

    },
    "WROscilloLineElement\0colorChanged\0\0"
    "WRColor\0value\0moveableChanged\0setColor\0"
    "setMoveable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WROscilloLineElement[] = {

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

void WROscilloLineElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WROscilloLineElement *_t = static_cast<WROscilloLineElement *>(_o);
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
            typedef void (WROscilloLineElement::*_t)(WRColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WROscilloLineElement::colorChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (WROscilloLineElement::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WROscilloLineElement::moveableChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject WROscilloLineElement::staticMetaObject = {
    { &WROscilloGaugeElement::staticMetaObject, qt_meta_stringdata_WROscilloLineElement.data,
      qt_meta_data_WROscilloLineElement,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WROscilloLineElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WROscilloLineElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WROscilloLineElement.stringdata0))
        return static_cast<void*>(this);
    return WROscilloGaugeElement::qt_metacast(_clname);
}

int WROscilloLineElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WROscilloGaugeElement::qt_metacall(_c, _id, _a);
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
void WROscilloLineElement::colorChanged(WRColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WROscilloLineElement::moveableChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_WROscilloDataPointLineElement_t {
    QByteArrayData data[6];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WROscilloDataPointLineElement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WROscilloDataPointLineElement_t qt_meta_stringdata_WROscilloDataPointLineElement = {
    {
QT_MOC_LITERAL(0, 0, 29), // "WROscilloDataPointLineElement"
QT_MOC_LITERAL(1, 30, 15), // "positionUpdated"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 5), // "value"
QT_MOC_LITERAL(4, 53, 15), // "positionChanged"
QT_MOC_LITERAL(5, 69, 11) // "setPosition"

    },
    "WROscilloDataPointLineElement\0"
    "positionUpdated\0\0value\0positionChanged\0"
    "setPosition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WROscilloDataPointLineElement[] = {

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

void WROscilloDataPointLineElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WROscilloDataPointLineElement *_t = static_cast<WROscilloDataPointLineElement *>(_o);
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
            typedef void (WROscilloDataPointLineElement::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WROscilloDataPointLineElement::positionUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (WROscilloDataPointLineElement::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WROscilloDataPointLineElement::positionChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject WROscilloDataPointLineElement::staticMetaObject = {
    { &WROscilloLineElement::staticMetaObject, qt_meta_stringdata_WROscilloDataPointLineElement.data,
      qt_meta_data_WROscilloDataPointLineElement,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WROscilloDataPointLineElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WROscilloDataPointLineElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WROscilloDataPointLineElement.stringdata0))
        return static_cast<void*>(this);
    return WROscilloLineElement::qt_metacast(_clname);
}

int WROscilloDataPointLineElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WROscilloLineElement::qt_metacall(_c, _id, _a);
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
void WROscilloDataPointLineElement::positionUpdated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WROscilloDataPointLineElement::positionChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_WROscilloDataValueLineElement_t {
    QByteArrayData data[6];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WROscilloDataValueLineElement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WROscilloDataValueLineElement_t qt_meta_stringdata_WROscilloDataValueLineElement = {
    {
QT_MOC_LITERAL(0, 0, 29), // "WROscilloDataValueLineElement"
QT_MOC_LITERAL(1, 30, 15), // "positionUpdated"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 5), // "value"
QT_MOC_LITERAL(4, 53, 15), // "positionChanged"
QT_MOC_LITERAL(5, 69, 11) // "setPosition"

    },
    "WROscilloDataValueLineElement\0"
    "positionUpdated\0\0value\0positionChanged\0"
    "setPosition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WROscilloDataValueLineElement[] = {

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

void WROscilloDataValueLineElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WROscilloDataValueLineElement *_t = static_cast<WROscilloDataValueLineElement *>(_o);
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
            typedef void (WROscilloDataValueLineElement::*_t)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WROscilloDataValueLineElement::positionUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (WROscilloDataValueLineElement::*_t)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WROscilloDataValueLineElement::positionChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject WROscilloDataValueLineElement::staticMetaObject = {
    { &WROscilloLineElement::staticMetaObject, qt_meta_stringdata_WROscilloDataValueLineElement.data,
      qt_meta_data_WROscilloDataValueLineElement,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WROscilloDataValueLineElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WROscilloDataValueLineElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WROscilloDataValueLineElement.stringdata0))
        return static_cast<void*>(this);
    return WROscilloLineElement::qt_metacast(_clname);
}

int WROscilloDataValueLineElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WROscilloLineElement::qt_metacall(_c, _id, _a);
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
void WROscilloDataValueLineElement::positionUpdated(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WROscilloDataValueLineElement::positionChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
