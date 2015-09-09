#ifndef CTGFMCFGFORM_H
#define CTGFMCFGFORM_H

#include "cmyform.h"
#include "eor_cfg.hpp"

namespace Ui {
class CTgfmCfgForm;
}

class CTgfmCfgForm : public CMyForm
{
    Q_OBJECT

public:
    explicit CTgfmCfgForm(QWidget *parent = 0);
    ~CTgfmCfgForm();

    bool getCfg(void* cfg_struct);
    bool setCfg(void* cfg_struct);

private:
    Ui::CTgfmCfgForm *ui;
};

#endif // CTGFMCFGFORM_H
