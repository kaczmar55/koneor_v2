#ifndef CRS232CFGFORM_H
#define CRS232CFGFORM_H

#include "cmyform.h"
#include "eor_cfg.hpp"

namespace Ui {
class CRs232CfgForm;
}

class CRs232CfgForm : public CMyForm
{
    Q_OBJECT

public:
    explicit CRs232CfgForm(QWidget *parent = 0);
    ~CRs232CfgForm();

    bool getCfg(void* cfg_struct);
    bool setCfg(void* cfg_struct);

private:
    Ui::CRs232CfgForm *ui;
};

#endif // CRS232CFGFORM_H
