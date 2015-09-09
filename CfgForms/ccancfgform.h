#ifndef CCANCFGFORM_H
#define CCANCFGFORM_H

#include "cmyform.h"

namespace Ui {
class CCanCfgForm;
}

class CCanCfgForm : public CMyForm
{
    Q_OBJECT

public:
    explicit CCanCfgForm(QWidget *parent = 0);
    ~CCanCfgForm();

    bool setCfg(void* cfg_struct);
    bool getCfg(void* cfg_struct);

private:
    Ui::CCanCfgForm *ui;
};

#endif // CCANCFGFORM_H
