/****************************************************************************
** Meta object code from reading C++ file 'WRSpectroDataViewElement.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/WRCharting/WRSpectroDataViewElement.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WRSpectroDataViewElement.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WRSpectroDataViewElement_t {
    QByteArrayData data[13];
    char stringdata0[166];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WRSpectroDataViewElement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WRSpectroDataViewElement_t qt_meta_stringdata_WRSpectroDataViewElement = {
    {
QT_MOC_LITERAL(0, 0, 24), // "WRSpectroDataViewElement"
QT_MOC_LITERAL(1, 25, 16), // "backColorChanged"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 7), // "WRColor"
QT_MOC_LITERAL(4, 51, 5), // "value"
QT_MOC_LITERAL(5, 57, 16), // "gridColorChanged"
QT_MOC_LITERAL(6, 74, 18), // "gridVisibleChanged"
QT_MOC_LITERAL(7, 93, 12), // "setBackColor"
QT_MOC_LITERAL(8, 106, 12), // "setGridColor"
QT_MOC_LITERAL(9, 119, 14), // "setGridVisible"
QT_MOC_LITERAL(10, 134, 9), // "backColor"
QT_MOC_LITERAL(11, 144, 9), // "gridColor"
QT_MOC_LITERAL(12, 154, 11) // "gridVisible"

    },
    "WRSpectroDataViewElement\0backColorChanged\0"
    "\0WRColor\0value\0gridColorChanged\0"
    "gridVisibleChanged\0setBackColor\0"
    "setGridColor\0setGridVisible\0backColor\0"
    "gridColor\0gridVisible"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WRSpectroDataViewElement[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       3,   62, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,
       6,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   53,    2, 0x0a /* Public */,
       8,    1,   56,    2, 0x0a /* Public */,
       9,    1,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Bool,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Bool,    4,

 // properties: name, type, flags
      10, 0x80000000 | 3, 0x0049510b,
      11, 0x80000000 | 3, 0x0049510b,
      12, QMetaType::Bool, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,

       0        // eod
};

void WRSpectroDataViewElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WRSpectroDataViewElement *_t = static_cast<WRSpectroDataViewElement *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backColorChanged((*reinterpret_cast< WRColor(*)>(_a[1]))); break;
        case 1: _t->gridColorChanged((*reinterpret_cast< WRColor(*)>(_a[1]))); break;
        case 2: _t->gridVisibleChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->setBackColor((*reinterpret_cast< WRColor(*)>(_a[1]))); break;
        case 4: _t->setGridColor((*reinterpret_cast< WRColor(*)>(_a[1]))); break;
        case 5: _t->setGridVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (WRSpectroDataViewElement::*_t)(WRColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRSpectroDataViewElement::backColorChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (WRSpectroDataViewElement::*_t)(WRColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRSpectroDataViewElement::gridColorChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (WRSpectroDataViewElement::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRSpectroDataViewElement::gridVisibleChanged)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        WRSpectroDataViewElement *_t = static_cast<WRSpectroDataViewElement *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< WRColor*>(_v) = _t->backColor(); break;
        case 1: *reinterpret_cast< WRColor*>(_v) = _t->gridColor(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->gridVisible(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        WRSpectroDataViewElement *_t = static_cast<WRSpectroDataViewElement *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setBackColor(*reinterpret_cast< WRColor*>(_v)); break;
        case 1: _t->setGridColor(*reinterpret_cast< WRColor*>(_v)); break;
        case 2: _t->setGridVisible(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject WRSpectroDataViewElement::staticMetaObject = {
    { &WRChartDataViewElement::staticMetaObject, qt_meta_stringdata_WRSpectroDataViewElement.data,
      qt_meta_data_WRSpectroDataViewElement,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WRSpectroDataViewElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WRSpectroDataViewElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WRSpectroDataViewElement.stringdata0))
        return static_cast<void*>(this);
    return WRChartDataViewElement::qt_metacast(_clname);
}

int WRSpectroDataViewElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WRChartDataViewElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void WRSpectroDataViewElement::backColorChanged(WRColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WRSpectroDataViewElement::gridColorChanged(WRColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WRSpectroDataViewElement::gridVisibleChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
