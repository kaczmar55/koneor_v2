#ifndef MYFORM_H
#define MYFORM_H

#include <QWidget>

class CMyForm : public QWidget
{
    Q_OBJECT

public:
    explicit CMyForm(QWidget *parent = 0);
    ~CMyForm();

    virtual bool getCfg(void* cfg_struct) = 0;
    virtual bool setCfg(void* cfg_struct) = 0;
};

#endif // MYFORM_H
