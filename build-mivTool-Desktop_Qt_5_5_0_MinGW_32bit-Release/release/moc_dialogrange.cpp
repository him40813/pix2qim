/****************************************************************************
** Meta object code from reading C++ file 'dialogrange.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mivTool/dialogrange.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogrange.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DialogRange_t {
    QByteArrayData data[15];
    char stringdata0[261];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogRange_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogRange_t qt_meta_stringdata_DialogRange = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DialogRange"
QT_MOC_LITERAL(1, 12, 19), // "on_cdButton_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 20), // "on_capButton_clicked"
QT_MOC_LITERAL(4, 54, 17), // "on_lcpBut_clicked"
QT_MOC_LITERAL(5, 72, 16), // "on_ccBut_clicked"
QT_MOC_LITERAL(6, 89, 17), // "on_scpBut_clicked"
QT_MOC_LITERAL(7, 107, 16), // "on_fmBut_clicked"
QT_MOC_LITERAL(8, 124, 16), // "on_fcBut_clicked"
QT_MOC_LITERAL(9, 141, 17), // "on_lgpBut_clicked"
QT_MOC_LITERAL(10, 159, 17), // "on_sgpBut_clicked"
QT_MOC_LITERAL(11, 177, 17), // "on_lspBut_clicked"
QT_MOC_LITERAL(12, 195, 17), // "on_sspBut_clicked"
QT_MOC_LITERAL(13, 213, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(14, 235, 25) // "on_calSimulateBut_clicked"

    },
    "DialogRange\0on_cdButton_clicked\0\0"
    "on_capButton_clicked\0on_lcpBut_clicked\0"
    "on_ccBut_clicked\0on_scpBut_clicked\0"
    "on_fmBut_clicked\0on_fcBut_clicked\0"
    "on_lgpBut_clicked\0on_sgpBut_clicked\0"
    "on_lspBut_clicked\0on_sspBut_clicked\0"
    "on_buttonBox_accepted\0on_calSimulateBut_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogRange[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DialogRange::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogRange *_t = static_cast<DialogRange *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_cdButton_clicked(); break;
        case 1: _t->on_capButton_clicked(); break;
        case 2: _t->on_lcpBut_clicked(); break;
        case 3: _t->on_ccBut_clicked(); break;
        case 4: _t->on_scpBut_clicked(); break;
        case 5: _t->on_fmBut_clicked(); break;
        case 6: _t->on_fcBut_clicked(); break;
        case 7: _t->on_lgpBut_clicked(); break;
        case 8: _t->on_sgpBut_clicked(); break;
        case 9: _t->on_lspBut_clicked(); break;
        case 10: _t->on_sspBut_clicked(); break;
        case 11: _t->on_buttonBox_accepted(); break;
        case 12: _t->on_calSimulateBut_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject DialogRange::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogRange.data,
      qt_meta_data_DialogRange,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DialogRange::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogRange::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DialogRange.stringdata0))
        return static_cast<void*>(const_cast< DialogRange*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogRange::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
