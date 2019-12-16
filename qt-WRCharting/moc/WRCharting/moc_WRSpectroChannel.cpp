/****************************************************************************
** Meta object code from reading C++ file 'WRSpectroChannel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/WRCharting/WRSpectroChannel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WRSpectroChannel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WRSpectroChannel_t {
    QByteArrayData data[16];
    char stringdata0[213];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WRSpectroChannel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WRSpectroChannel_t qt_meta_stringdata_WRSpectroChannel = {
    {
QT_MOC_LITERAL(0, 0, 16), // "WRSpectroChannel"
QT_MOC_LITERAL(1, 17, 14), // "visibleChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 5), // "value"
QT_MOC_LITERAL(4, 39, 16), // "lineColorChanged"
QT_MOC_LITERAL(5, 56, 7), // "WRColor"
QT_MOC_LITERAL(6, 64, 16), // "markColorChanged"
QT_MOC_LITERAL(7, 81, 21), // "dataZoomMethodChanged"
QT_MOC_LITERAL(8, 103, 14), // "DataZoomMethod"
QT_MOC_LITERAL(9, 118, 10), // "setVisible"
QT_MOC_LITERAL(10, 129, 12), // "setLineColor"
QT_MOC_LITERAL(11, 142, 12), // "setMarkColor"
QT_MOC_LITERAL(12, 155, 17), // "setDataZoomMethod"
QT_MOC_LITERAL(13, 173, 13), // "ShowDataRange"
QT_MOC_LITERAL(14, 187, 12), // "ShowMaxValue"
QT_MOC_LITERAL(15, 200, 12) // "ShowMinValue"

    },
    "WRSpectroChannel\0visibleChanged\0\0value\0"
    "lineColorChanged\0WRColor\0markColorChanged\0"
    "dataZoomMethodChanged\0DataZoomMethod\0"
    "setVisible\0setLineColor\0setMarkColor\0"
    "setDataZoomMethod\0ShowDataRange\0"
    "ShowMaxValue\0ShowMinValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WRSpectroChannel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       1,   78, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       6,    1,   60,    2, 0x06 /* Public */,
       7,    1,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   66,    2, 0x0a /* Public */,
      10,    1,   69,    2, 0x0a /* Public */,
      11,    1,   72,    2, 0x0a /* Public */,
      12,    1,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 5,    3,
    QMetaType::Void, 0x80000000 | 5,    3,
    QMetaType::Void, 0x80000000 | 8,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 5,    3,
    QMetaType::Void, 0x80000000 | 5,    3,
    QMetaType::Void, 0x80000000 | 8,    3,

 // enums: name, flags, count, data
       8, 0x0,    3,   82,

 // enum data: key, value
      13, uint(WRSpectroChannel::ShowDataRange),
      14, uint(WRSpectroChannel::ShowMaxValue),
      15, uint(WRSpectroChannel::ShowMinValue),

       0        // eod
};

void WRSpectroChannel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WRSpectroChannel *_t = static_cast<WRSpectroChannel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->visibleChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->lineColorChanged((*reinterpret_cast< WRColor(*)>(_a[1]))); break;
        case 2: _t->markColorChanged((*reinterpret_cast< WRColor(*)>(_a[1]))); break;
        case 3: _t->dataZoomMethodChanged((*reinterpret_cast< DataZoomMethod(*)>(_a[1]))); break;
        case 4: _t->setVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setLineColor((*reinterpret_cast< WRColor(*)>(_a[1]))); break;
        case 6: _t->setMarkColor((*reinterpret_cast< WRColor(*)>(_a[1]))); break;
        case 7: _t->setDataZoomMethod((*reinterpret_cast< DataZoomMethod(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (WRSpectroChannel::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRSpectroChannel::visibleChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (WRSpectroChannel::*_t)(WRColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRSpectroChannel::lineColorChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (WRSpectroChannel::*_t)(WRColor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRSpectroChannel::markColorChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (WRSpectroChannel::*_t)(DataZoomMethod );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRSpectroChannel::dataZoomMethodChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject WRSpectroChannel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_WRSpectroChannel.data,
      qt_meta_data_WRSpectroChannel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WRSpectroChannel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WRSpectroChannel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WRSpectroChannel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WRSpectroChannel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
    return _id;
}

// SIGNAL 0
void WRSpectroChannel::visibleChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WRSpectroChannel::lineColorChanged(WRColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WRSpectroChannel::markColorChanged(WRColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WRSpectroChannel::dataZoomMethodChanged(DataZoomMethod _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
