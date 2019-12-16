/****************************************************************************
** Meta object code from reading C++ file 'WRChartAxisElement.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/WRCharting/WRChartAxisElement.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WRChartAxisElement.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WRChartAxisElement_t {
    QByteArrayData data[19];
    char stringdata0[225];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WRChartAxisElement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WRChartAxisElement_t qt_meta_stringdata_WRChartAxisElement = {
    {
QT_MOC_LITERAL(0, 0, 18), // "WRChartAxisElement"
QT_MOC_LITERAL(1, 19, 14), // "visibleChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "value"
QT_MOC_LITERAL(4, 41, 15), // "scalableChanged"
QT_MOC_LITERAL(5, 57, 16), // "backColorChanged"
QT_MOC_LITERAL(6, 74, 7), // "WRColor"
QT_MOC_LITERAL(7, 82, 16), // "lineColorChanged"
QT_MOC_LITERAL(8, 99, 16), // "textColorChanged"
QT_MOC_LITERAL(9, 116, 10), // "setVisible"
QT_MOC_LITERAL(10, 127, 11), // "setScalable"
QT_MOC_LITERAL(11, 139, 12), // "setBackColor"
QT_MOC_LITERAL(12, 152, 12), // "setLineColor"
QT_MOC_LITERAL(13, 165, 12), // "setTextColor"
QT_MOC_LITERAL(14, 178, 7), // "visible"
QT_MOC_LITERAL(15, 186, 8), // "scalable"
QT_MOC_LITERAL(16, 195, 9), // "backColor"
QT_MOC_LITERAL(17, 205, 9), // "lineColor"
QT_MOC_LITERAL(18, 215, 9) // "textColor"

    },
    "WRChartAxisElement\0visibleChanged\0\0"
    "value\0scalableChanged\0backColorChanged\0"
    "WRColor\0lineColorChanged\0textColorChanged\0"
    "setVisible\0setScalable\0setBackColor\0"
    "setLineColor\0setTextColor\0visible\0"
    "scalable\0backColor\0lineColor\0textColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WRChartAxisElement[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       5,   94, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       5,    1,   70,    2, 0x06 /* Public */,
       7,    1,   73,    2, 0x06 /* Public */,
       8,    1,   76,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   79,    2, 0x0a /* Public */,
      10,    1,   82,    2, 0x0a /* Public */,
      11,    1,   85,    2, 0x0a /* Public */,
      12,    1,   88,    2, 0x0a /* Public */,
      13,    1,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 6,    3,
    QMetaType::Void, 0x80000000 | 6,    3,
    QMetaType::Void, 0x80000000 | 6,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 6,    3,
    QMetaType::Void, 0x80000000 | 6,    3,
    QMetaType::Void, 0x80000000 | 6,    3,

 // properties: name, type, flags
      14, QMetaType::Bool, 0x00495103,
      15, QMetaType::Bool, 0x00495103,
      16, 0x80000000 | 6, 0x0049510b,
      17, 0x80000000 | 6, 0x0049510b,
      18, 0x80000000 | 6, 0x0049510b,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,

       0        // eod
};

void WRChartAxisElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WRChartAxisElement *_t = static_cast<WRChartAxisElement *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->visibleChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->scalableChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->backColorChanged((*reinterpret_cast< WRColor(*)>(_a[1]))); break;
        case 3: _t->lineColorChanged((*reinterpret_cast< WRColor(*)>(_a[1]))); break;
        case 4: _t->textColorChanged((*reinterpret_cast< WRColor(*)>(_a[1]))); break;
        case 5: _t->setVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->setScalable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->setBackColor((*reinterpret_cast< WRColor(*)>(_a[1]))); break;
        case 8: _t->setLineColor((*reinterpret_cast< WRColor(*)>(_a[1]))); break;
        case 9: _t->setTextColor((*reinterpret_cast< WRColor(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (WRChartAxisElement::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartAxisElement::visibleChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (WRChartAxisElement::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartAxisElement::scalableChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (WRChartAxisElement::*_t)(WRColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartAxisElement::backColorChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (WRChartAxisElement::*_t)(WRColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartAxisElement::lineColorChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (WRChartAxisElement::*_t)(WRColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartAxisElement::textColorChanged)) {
                *result = 4;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        WRChartAxisElement *_t = static_cast<WRChartAxisElement *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->visible(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->scalable(); break;
        case 2: *reinterpret_cast< WRColor*>(_v) = _t->backColor(); break;
        case 3: *reinterpret_cast< WRColor*>(_v) = _t->lineColor(); break;
        case 4: *reinterpret_cast< WRColor*>(_v) = _t->textColor(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        WRChartAxisElement *_t = static_cast<WRChartAxisElement *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setVisible(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setScalable(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setBackColor(*reinterpret_cast< WRColor*>(_v)); break;
        case 3: _t->setLineColor(*reinterpret_cast< WRColor*>(_v)); break;
        case 4: _t->setTextColor(*reinterpret_cast< WRColor*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject WRChartAxisElement::staticMetaObject = {
    { &WRChartElement::staticMetaObject, qt_meta_stringdata_WRChartAxisElement.data,
      qt_meta_data_WRChartAxisElement,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WRChartAxisElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WRChartAxisElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WRChartAxisElement.stringdata0))
        return static_cast<void*>(this);
    return WRChartElement::qt_metacast(_clname);
}

int WRChartAxisElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WRChartElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void WRChartAxisElement::visibleChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WRChartAxisElement::scalableChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WRChartAxisElement::backColorChanged(WRColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WRChartAxisElement::lineColorChanged(WRColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WRChartAxisElement::textColorChanged(WRColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
struct qt_meta_stringdata_WRChartHAxisElement_t {
    QByteArrayData data[6];
    char stringdata0[64];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WRChartHAxisElement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WRChartHAxisElement_t qt_meta_stringdata_WRChartHAxisElement = {
    {
QT_MOC_LITERAL(0, 0, 19), // "WRChartHAxisElement"
QT_MOC_LITERAL(1, 20, 11), // "dockChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 5), // "value"
QT_MOC_LITERAL(4, 39, 13), // "setDockBottom"
QT_MOC_LITERAL(5, 53, 10) // "dockBottom"

    },
    "WRChartHAxisElement\0dockChanged\0\0value\0"
    "setDockBottom\0dockBottom"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WRChartHAxisElement[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       1,   30, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // properties: name, type, flags
       5, QMetaType::Bool, 0x00495103,

 // properties: notify_signal_id
       0,

       0        // eod
};

void WRChartHAxisElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WRChartHAxisElement *_t = static_cast<WRChartHAxisElement *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dockChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setDockBottom((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (WRChartHAxisElement::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartHAxisElement::dockChanged)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        WRChartHAxisElement *_t = static_cast<WRChartHAxisElement *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->dockBottom(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        WRChartHAxisElement *_t = static_cast<WRChartHAxisElement *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDockBottom(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject WRChartHAxisElement::staticMetaObject = {
    { &WRChartAxisElement::staticMetaObject, qt_meta_stringdata_WRChartHAxisElement.data,
      qt_meta_data_WRChartHAxisElement,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WRChartHAxisElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WRChartHAxisElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WRChartHAxisElement.stringdata0))
        return static_cast<void*>(this);
    return WRChartAxisElement::qt_metacast(_clname);
}

int WRChartHAxisElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WRChartAxisElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void WRChartHAxisElement::dockChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_WRChartVAxisElement_t {
    QByteArrayData data[6];
    char stringdata0[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WRChartVAxisElement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WRChartVAxisElement_t qt_meta_stringdata_WRChartVAxisElement = {
    {
QT_MOC_LITERAL(0, 0, 19), // "WRChartVAxisElement"
QT_MOC_LITERAL(1, 20, 11), // "dockChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 5), // "value"
QT_MOC_LITERAL(4, 39, 11), // "setDockLeft"
QT_MOC_LITERAL(5, 51, 8) // "dockLeft"

    },
    "WRChartVAxisElement\0dockChanged\0\0value\0"
    "setDockLeft\0dockLeft"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WRChartVAxisElement[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       1,   30, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // properties: name, type, flags
       5, QMetaType::Bool, 0x00495103,

 // properties: notify_signal_id
       0,

       0        // eod
};

void WRChartVAxisElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WRChartVAxisElement *_t = static_cast<WRChartVAxisElement *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dockChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setDockLeft((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (WRChartVAxisElement::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartVAxisElement::dockChanged)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        WRChartVAxisElement *_t = static_cast<WRChartVAxisElement *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->dockLeft(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        WRChartVAxisElement *_t = static_cast<WRChartVAxisElement *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDockLeft(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject WRChartVAxisElement::staticMetaObject = {
    { &WRChartAxisElement::staticMetaObject, qt_meta_stringdata_WRChartVAxisElement.data,
      qt_meta_data_WRChartVAxisElement,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WRChartVAxisElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WRChartVAxisElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WRChartVAxisElement.stringdata0))
        return static_cast<void*>(this);
    return WRChartAxisElement::qt_metacast(_clname);
}

int WRChartVAxisElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WRChartAxisElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void WRChartVAxisElement::dockChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
