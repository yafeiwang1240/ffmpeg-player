/****************************************************************************
** Meta object code from reading C++ file 'h265viedoplayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../FFMPEGTest/h265viedoplayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'h265viedoplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_H265ViedoPlayer_t {
    QByteArrayData data[4];
    char stringdata0[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_H265ViedoPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_H265ViedoPlayer_t qt_meta_stringdata_H265ViedoPlayer = {
    {
QT_MOC_LITERAL(0, 0, 15), // "H265ViedoPlayer"
QT_MOC_LITERAL(1, 16, 12), // "currentTimes"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 3) // "sec"

    },
    "H265ViedoPlayer\0currentTimes\0\0sec"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_H265ViedoPlayer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong,    3,

       0        // eod
};

void H265ViedoPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        H265ViedoPlayer *_t = static_cast<H265ViedoPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->currentTimes((*reinterpret_cast< long long(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (H265ViedoPlayer::*_t)(long long );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&H265ViedoPlayer::currentTimes)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject H265ViedoPlayer::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_H265ViedoPlayer.data,
      qt_meta_data_H265ViedoPlayer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *H265ViedoPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *H265ViedoPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_H265ViedoPlayer.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int H265ViedoPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void H265ViedoPlayer::currentTimes(long long _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
