/****************************************************************************
** Meta object code from reading C++ file 'WRChartScrollElement.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/WRCharting/WRChartScrollElement.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WRChartScrollElement.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WRChartScrollElement_t {
    QByteArrayData data[16];
    char stringdata0[187];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WRChartScrollElement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WRChartScrollElement_t qt_meta_stringdata_WRChartScrollElement = {
    {
QT_MOC_LITERAL(0, 0, 20), // "WRChartScrollElement"
QT_MOC_LITERAL(1, 21, 14), // "visibleChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 5), // "value"
QT_MOC_LITERAL(4, 43, 15), // "scalableChanged"
QT_MOC_LITERAL(5, 59, 16), // "backColorChanged"
QT_MOC_LITERAL(6, 76, 7), // "WRColor"
QT_MOC_LITERAL(7, 84, 16), // "foreColorChanged"
QT_MOC_LITERAL(8, 101, 10), // "setVisible"
QT_MOC_LITERAL(9, 112, 11), // "setScalable"
QT_MOC_LITERAL(10, 124, 12), // "setBackColor"
QT_MOC_LITERAL(11, 137, 12), // "setForeColor"
QT_MOC_LITERAL(12, 150, 7), // "visible"
QT_MOC_LITERAL(13, 158, 8), // "scalable"
QT_MOC_LITERAL(14, 167, 9), // "backColor"
QT_MOC_LITERAL(15, 177, 9) // "foreColor"

    },
    "WRChartScrollElement\0visibleChanged\0"
    "\0value\0scalableChanged\0backColorChanged\0"
    "WRColor\0foreColorChanged\0setVisible\0"
    "setScalable\0setBackColor\0setForeColor\0"
    "visible\0scalable\0backColor\0foreColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WRChartScrollElement[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       4,   78, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       5,    1,   60,    2, 0x06 /* Public */,
       7,    1,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   66,    2, 0x0a /* Public */,
       9,    1,   69,    2, 0x0a /* Public */,
      10,    1,   72,    2, 0x0a /* Public */,
      11,    1,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 6,    3,
    QMetaType::Void, 0x80000000 | 6,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 6,    3,
    QMetaType::Void, 0x80000000 | 6,    3,

 // properties: name, type, flags
      12, QMetaType::Bool, 0x00495103,
      13, QMetaType::Bool, 0x00495103,
      14, 0x80000000 | 6, 0x0049510b,
      15, 0x80000000 | 6, 0x0049510b,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

       0        // eod
};

void WRChartScrollElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WRChartScrollElement *_t = static_cast<WRChartScrollElement *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->visibleChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->scalableChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->backColorChanged((*reinterpret_cast< WRColor(*)>(_a[1]))); break;
        case 3: _t->foreColorChanged((*reinterpret_cast< WRColor(*)>(_a[1]))); break;
        case 4: _t->setVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setScalable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->setBackColor((*reinterpret_cast< WRColor(*)>(_a[1]))); break;
        case 7: _t->setForeColor((*reinterpret_cast< WRColor(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (WRChartScrollElement::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartScrollElement::visibleChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (WRChartScrollElement::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartScrollElement::scalableChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (WRChartScrollElement::*_t)(WRColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartScrollElement::backColorChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (WRChartScrollElement::*_t)(WRColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartScrollElement::foreColorChanged)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        WRChartScrollElement *_t = static_cast<WRChartScrollElement *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->visible(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->scalable(); break;
        case 2: *reinterpret_cast< WRColor*>(_v) = _t->backColor(); break;
        case 3: *reinterpret_cast< WRColor*>(_v) = _t->foreColor(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        WRChartScrollElement *_t = static_cast<WRChartScrollElement *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setVisible(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setScalable(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setBackColor(*reinterpret_cast< WRColor*>(_v)); break;
        case 3: _t->setForeColor(*reinterpret_cast< WRColor*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject WRChartScrollElement::staticMetaObject = {
    { &WRChartElement::staticMetaObject, qt_meta_stringdata_WRChartScrollElement.data,
      qt_meta_data_WRChartScrollElement,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WRChartScrollElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WRChartScrollElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WRChartScrollElement.stringdata0))
        return static_cast<void*>(this);
    return WRChartElement::qt_metacast(_clname);
}

int WRChartScrollElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WRChartElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void WRChartScrollElement::visibleChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WRChartScrollElement::scalableChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WRChartScrollElement::backColorChanged(WRColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WRChartScrollElement::foreColorChanged(WRColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
struct qt_meta_stringdata_WRChartHScrollElement_t {
    QByteArrayData data[6];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WRChartHScrollElement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WRChartHScrollElement_t qt_meta_stringdata_WRChartHScrollElement = {
    {
QT_MOC_LITERAL(0, 0, 21), // "WRChartHScrollElement"
QT_MOC_LITERAL(1, 22, 11), // "dockChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "value"
QT_MOC_LITERAL(4, 41, 13), // "setDockBottom"
QT_MOC_LITERAL(5, 55, 10) // "dockBottom"

    },
    "WRChartHScrollElement\0dockChanged\0\0"
    "value\0setDockBottom\0dockBottom"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WRChartHScrollElement[] = {

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

void WRChartHScrollElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WRChartHScrollElement *_t = static_cast<WRChartHScrollElement *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dockChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setDockBottom((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (WRChartHScrollElement::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartHScrollElement::dockChanged)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        WRChartHScrollElement *_t = static_cast<WRChartHScrollElement *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->dockBottom(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        WRChartHScrollElement *_t = static_cast<WRChartHScrollElement *>(_o);
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

const QMetaObject WRChartHScrollElement::staticMetaObject = {
    { &WRChartScrollElement::staticMetaObject, qt_meta_stringdata_WRChartHScrollElement.data,
      qt_meta_data_WRChartHScrollElement,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WRChartHScrollElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WRChartHScrollElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WRChartHScrollElement.stringdata0))
        return static_cast<void*>(this);
    return WRChartScrollElement::qt_metacast(_clname);
}

int WRChartHScrollElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WRChartScrollElement::qt_metacall(_c, _id, _a);
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
void WRChartHScrollElement::dockChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_WRChartVScrollElement_t {
    QByteArrayData data[6];
    char stringdata0[62];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WRChartVScrollElement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WRChartVScrollElement_t qt_meta_stringdata_WRChartVScrollElement = {
    {
QT_MOC_LITERAL(0, 0, 21), // "WRChartVScrollElement"
QT_MOC_LITERAL(1, 22, 11), // "dockChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "value"
QT_MOC_LITERAL(4, 41, 11), // "setDockLeft"
QT_MOC_LITERAL(5, 53, 8) // "dockLeft"

    },
    "WRChartVScrollElement\0dockChanged\0\0"
    "value\0setDockLeft\0dockLeft"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WRChartVScrollElement[] = {

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

void WRChartVScrollElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WRChartVScrollElement *_t = static_cast<WRChartVScrollElement *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dockChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setDockLeft((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (WRChartVScrollElement::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartVScrollElement::dockChanged)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        WRChartVScrollElement *_t = static_cast<WRChartVScrollElement *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->dockLeft(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        WRChartVScrollElement *_t = static_cast<WRChartVScrollElement *>(_o);
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

const QMetaObject WRChartVScrollElement::staticMetaObject = {
    { &WRChartScrollElement::staticMetaObject, qt_meta_stringdata_WRChartVScrollElement.data,
      qt_meta_data_WRChartVScrollElement,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WRChartVScrollElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WRChartVScrollElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WRChartVScrollElement.stringdata0))
        return static_cast<void*>(this);
    return WRChartScrollElement::qt_metacast(_clname);
}

int WRChartVScrollElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WRChartScrollElement::qt_metacall(_c, _id, _a);
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
void WRChartVScrollElement::dockChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
