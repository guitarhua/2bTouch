/****************************************************************************
** Meta object code from reading C++ file 'keypad.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "keypad.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'keypad.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Keypad_t {
    QByteArrayData data[7];
    char stringdata[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Keypad_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Keypad_t qt_meta_stringdata_Keypad = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 11),
QT_MOC_LITERAL(2, 19, 0),
QT_MOC_LITERAL(3, 20, 13),
QT_MOC_LITERAL(4, 34, 12),
QT_MOC_LITERAL(5, 47, 8),
QT_MOC_LITERAL(6, 56, 11)
    },
    "Keypad\0setalphabet\0\0keypadHandler\0"
    "symbolChange\0keyclose\0boardchange"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Keypad[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Keypad::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Keypad *_t = static_cast<Keypad *>(_o);
        switch (_id) {
        case 0: _t->setalphabet(); break;
        case 1: _t->keypadHandler(); break;
        case 2: _t->symbolChange(); break;
        case 3: _t->keyclose(); break;
        case 4: _t->boardchange(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Keypad::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Keypad.data,
      qt_meta_data_Keypad,  qt_static_metacall, 0, 0}
};


const QMetaObject *Keypad::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Keypad::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Keypad.stringdata))
        return static_cast<void*>(const_cast< Keypad*>(this));
    return QDialog::qt_metacast(_clname);
}

int Keypad::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
