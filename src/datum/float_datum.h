#ifndef FLOAT_H
#define FLOAT_H

#include <Python.h>
#include "datum/eval_datum.h"

class FloatDatum : public EvalDatum
{
    Q_OBJECT
public:
    explicit FloatDatum(QString name, QObject* parent=0);
    explicit FloatDatum(QString name, QString expr, QObject *parent = 0);
    PyTypeObject* getType() const override { return &PyFloat_Type; }
    DatumType::DatumType getDatumType() const override
        { return DatumType::FLOAT; }
};

#endif // FLOAT_H
