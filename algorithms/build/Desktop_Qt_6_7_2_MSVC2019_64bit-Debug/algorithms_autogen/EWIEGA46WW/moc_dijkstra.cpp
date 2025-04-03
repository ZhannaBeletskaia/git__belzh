/****************************************************************************
** Meta object code from reading C++ file 'dijkstra.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../dijkstra.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dijkstra.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSDijkstraENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSDijkstraENDCLASS = QtMocHelpers::stringData(
    "Dijkstra",
    "vertexProcessing",
    "",
    "int&",
    "name",
    "color",
    "edgeProcessing",
    "from",
    "to",
    "weight",
    "finished"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSDijkstraENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   32,    2, 0x06,    1 /* Public */,
       6,    4,   37,    2, 0x06,    4 /* Public */,
      10,    0,   46,    2, 0x06,    9 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QColor,    4,    5,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, QMetaType::QColor,    7,    8,    9,    5,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Dijkstra::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSDijkstraENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSDijkstraENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSDijkstraENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Dijkstra, std::true_type>,
        // method 'vertexProcessing'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'edgeProcessing'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QColor, std::false_type>,
        // method 'finished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Dijkstra::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Dijkstra *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->vertexProcessing((*reinterpret_cast< std::add_pointer_t<int&>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QColor>>(_a[2]))); break;
        case 1: _t->edgeProcessing((*reinterpret_cast< std::add_pointer_t<int&>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int&>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int&>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QColor>>(_a[4]))); break;
        case 2: _t->finished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Dijkstra::*)(int & , QColor );
            if (_t _q_method = &Dijkstra::vertexProcessing; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Dijkstra::*)(int & , int & , int & , QColor );
            if (_t _q_method = &Dijkstra::edgeProcessing; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Dijkstra::*)();
            if (_t _q_method = &Dijkstra::finished; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *Dijkstra::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dijkstra::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSDijkstraENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Dijkstra::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Dijkstra::vertexProcessing(int & _t1, QColor _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Dijkstra::edgeProcessing(int & _t1, int & _t2, int & _t3, QColor _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Dijkstra::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
