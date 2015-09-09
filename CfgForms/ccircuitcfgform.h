#ifndef CCIRCUITCFGFORM_H
#define CCIRCUITCFGFORM_H

#include "eor_cfg.hpp"
#include "cmyform.h"

namespace Ui {
class CCircuitCfgForm;
}

class CCircuitCfgForm : public CMyForm
{
    Q_OBJECT

public:
    explicit CCircuitCfgForm(QWidget *parent = 0);
    ~CCircuitCfgForm();

    bool setCfg(void* cfg_struct);
    bool getCfg(void* cfg_struct);

private:
    Ui::CCircuitCfgForm *ui;
};

#endif // CCIRCUITCFGFORM_H
