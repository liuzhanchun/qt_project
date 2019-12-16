/****************************************************************************
** Meta object code from reading C++ file 'WRChartElement.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/WRCharting/WRChartElement.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WRChartElement.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WRChartElement_t {
    QByteArrayData data[27];
    char stringdata0[218];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WRChartElement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WRChartElement_t qt_meta_stringdata_WRChartElement = {
    {
QT_MOC_LITERAL(0, 0, 14), // "WRChartElement"
QT_MOC_LITERAL(1, 15, 7), // "keyDown"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 10), // "QKeyEvent*"
QT_MOC_LITERAL(4, 35, 1), // "e"
QT_MOC_LITERAL(5, 37, 5), // "keyUp"
QT_MOC_LITERAL(6, 43, 9), // "mouseMove"
QT_MOC_LITERAL(7, 53, 12), // "QMouseEvent*"
QT_MOC_LITERAL(8, 66, 10), // "mouseWheel"
QT_MOC_LITERAL(9, 77, 12), // "QWheelEvent*"
QT_MOC_LITERAL(10, 90, 9), // "mouseDown"
QT_MOC_LITERAL(11, 100, 7), // "mouseUp"
QT_MOC_LITERAL(12, 108, 16), // "mouseDoubleClick"
QT_MOC_LITERAL(13, 125, 10), // "mouseEnter"
QT_MOC_LITERAL(14, 136, 10), // "mouseLeave"
QT_MOC_LITERAL(15, 147, 4), // "rect"
QT_MOC_LITERAL(16, 152, 6), // "WRRect"
QT_MOC_LITERAL(17, 159, 3), // "pos"
QT_MOC_LITERAL(18, 163, 7), // "WRPoint"
QT_MOC_LITERAL(19, 171, 4), // "size"
QT_MOC_LITERAL(20, 176, 6), // "WRSize"
QT_MOC_LITERAL(21, 183, 4), // "left"
QT_MOC_LITERAL(22, 188, 3), // "top"
QT_MOC_LITERAL(23, 192, 5), // "right"
QT_MOC_LITERAL(24, 198, 6), // "bottom"
QT_MOC_LITERAL(25, 205, 5), // "width"
QT_MOC_LITERAL(26, 211, 6) // "height"

    },
    "WRChartElement\0keyDown\0\0QKeyEvent*\0e\0"
    "keyUp\0mouseMove\0QMouseEvent*\0mouseWheel\0"
    "QWheelEvent*\0mouseDown\0mouseUp\0"
    "mouseDoubleClick\0mouseEnter\0mouseLeave\0"
    "rect\0WRRect\0pos\0WRPoint\0size\0WRSize\0"
    "left\0top\0right\0bottom\0width\0height"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WRChartElement[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       9,   82, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       5,    1,   62,    2, 0x06 /* Public */,
       6,    1,   65,    2, 0x06 /* Public */,
       8,    1,   68,    2, 0x06 /* Public */,
      10,    1,   71,    2, 0x06 /* Public */,
      11,    1,   74,    2, 0x06 /* Public */,
      12,    1,   77,    2, 0x06 /* Public */,
      13,    0,   80,    2, 0x06 /* Public */,
      14,    0,   81,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 7,    4,
    QMetaType::Void, 0x80000000 | 9,    4,
    QMetaType::Void, 0x80000000 | 7,    4,
    QMetaType::Void, 0x80000000 | 7,    4,
    QMetaType::Void, 0x80000000 | 7,    4,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      15, 0x80000000 | 16, 0x00095009,
      17, 0x80000000 | 18, 0x00095009,
      19, 0x80000000 | 20, 0x00095009,
      21, QMetaType::Int, 0x00095001,
      22, QMetaType::Int, 0x00095001,
      23, QMetaType::Int, 0x00095001,
      24, QMetaType::Int, 0x00095001,
      25, QMetaType::Int, 0x00095001,
      26, QMetaType::Int, 0x00095001,

       0        // eod
};

void WRChartElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WRChartElement *_t = static_cast<WRChartElement *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->keyDown((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 1: _t->keyUp((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 2: _t->mouseMove((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 3: _t->mouseWheel((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 4: _t->mouseDown((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 5: _t->mouseUp((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 6: _t->mouseDoubleClick((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 7: _t->mouseEnter(); break;
        case 8: _t->mouseLeave(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (WRChartElement::*_t)(QKeyEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartElement::keyDown)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (WRChartElement::*_t)(QKeyEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartElement::keyUp)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (WRChartElement::*_t)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartElement::mouseMove)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (WRChartElement::*_t)(QWheelEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartElement::mouseWheel)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (WRChartElement::*_t)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartElement::mouseDown)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (WRChartElement::*_t)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartElement::mouseUp)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (WRChartElement::*_t)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartElement::mouseDoubleClick)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (WRChartElement::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartElement::mouseEnter)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (WRChartElement::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WRChartElement::mouseLeave)) {
                *result = 8;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        WRChartElement *_t = static_cast<WRChartElement *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< WRRect*>(_v) = _t->rect(); break;
        case 1: *reinterpret_cast< WRPoint*>(_v) = _t->pos(); break;
        case 2: *reinterpret_cast< WRSize*>(_v) = _t->size(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->left(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->top(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->right(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->bottom(); break;
        case 7: *reinterpret_cast< int*>(_v) = _t->width(); break;
        case 8: *reinterpret_cast< int*>(_v) = _t->height(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject WRChartElement::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_WRChartElement.data,
      qt_meta_data_WRChartElement,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WRChartElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WRChartElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WRChartElement.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WRChartElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 9;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void WRChartElement::keyDown(QKeyEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WRChartElement::keyUp(QKeyEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WRChartElement::mouseMove(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WRChartElement::mouseWheel(QWheelEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WRChartElement::mouseDown(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void WRChartElement::mouseUp(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void WRChartElement::mouseDoubleClick(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void WRChartElement::mouseEnter()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void WRChartElement::mouseLeave()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
