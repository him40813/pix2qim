/****************************************************************************
** Meta object code from reading C++ file 'task_runalgo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mivTool/task_runalgo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'task_runalgo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_task_RunAlgo_t {
    QByteArrayData data[14];
    char stringdata0[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_task_RunAlgo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_task_RunAlgo_t qt_meta_stringdata_task_RunAlgo = {
    {
QT_MOC_LITERAL(0, 0, 12), // "task_RunAlgo"
QT_MOC_LITERAL(1, 13, 7), // "uiState"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 9), // "taskState"
QT_MOC_LITERAL(4, 32, 4), // "task"
QT_MOC_LITERAL(5, 37, 22), // "on_selAlgo_itemClicked"
QT_MOC_LITERAL(6, 60, 21), // "on_btnProcess_clicked"
QT_MOC_LITERAL(7, 82, 31), // "on_btnLoadDefaultConfig_clicked"
QT_MOC_LITERAL(8, 114, 29), // "on_browse_inputSource_clicked"
QT_MOC_LITERAL(9, 144, 26), // "on_saveImageFormat_clicked"
QT_MOC_LITERAL(10, 171, 23), // "on_browse_gtDir_clicked"
QT_MOC_LITERAL(11, 195, 27), // "on_browse_resultDir_clicked"
QT_MOC_LITERAL(12, 223, 16), // "on_stepB_clicked"
QT_MOC_LITERAL(13, 240, 14) // "on_pPB_clicked"

    },
    "task_RunAlgo\0uiState\0\0taskState\0task\0"
    "on_selAlgo_itemClicked\0on_btnProcess_clicked\0"
    "on_btnLoadDefaultConfig_clicked\0"
    "on_browse_inputSource_clicked\0"
    "on_saveImageFormat_clicked\0"
    "on_browse_gtDir_clicked\0"
    "on_browse_resultDir_clicked\0"
    "on_stepB_clicked\0on_pPB_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_task_RunAlgo[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    1,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   73,    2, 0x08 /* Private */,
       6,    0,   74,    2, 0x08 /* Private */,
       7,    0,   75,    2, 0x08 /* Private */,
       8,    0,   76,    2, 0x08 /* Private */,
       9,    0,   77,    2, 0x08 /* Private */,
      10,    0,   78,    2, 0x08 /* Private */,
      11,    0,   79,    2, 0x08 /* Private */,
      12,    0,   80,    2, 0x08 /* Private */,
      13,    0,   81,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,

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

       0        // eod
};

void task_RunAlgo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        task_RunAlgo *_t = static_cast<task_RunAlgo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->uiState(); break;
        case 1: _t->taskState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_selAlgo_itemClicked(); break;
        case 3: _t->on_btnProcess_clicked(); break;
        case 4: _t->on_btnLoadDefaultConfig_clicked(); break;
        case 5: _t->on_browse_inputSource_clicked(); break;
        case 6: _t->on_saveImageFormat_clicked(); break;
        case 7: _t->on_browse_gtDir_clicked(); break;
        case 8: _t->on_browse_resultDir_clicked(); break;
        case 9: _t->on_stepB_clicked(); break;
        case 10: _t->on_pPB_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (task_RunAlgo::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&task_RunAlgo::uiState)) {
                *result = 0;
            }
        }
        {
            typedef void (task_RunAlgo::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&task_RunAlgo::taskState)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject task_RunAlgo::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_task_RunAlgo.data,
      qt_meta_data_task_RunAlgo,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *task_RunAlgo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *task_RunAlgo::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_task_RunAlgo.stringdata0))
        return static_cast<void*>(const_cast< task_RunAlgo*>(this));
    return QWidget::qt_metacast(_clname);
}

int task_RunAlgo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void task_RunAlgo::uiState()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void task_RunAlgo::taskState(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
