#ifndef CUSERSCFGFORM_H
#define CUSERSCFGFORM_H

#include "cmyform.h"
#include "eor_cfg.hpp"

namespace Ui {
class CUsersCfgForm;
}

class CUsersCfgForm : public CMyForm
{
    Q_OBJECT

public:
    explicit CUsersCfgForm(QWidget *parent = 0);
    ~CUsersCfgForm();

    bool getCfg(void* cfg_struct);
    bool setCfg(void* cfg_struct);

private:
    Ui::CUsersCfgForm *ui;
};

#endif // CUSERSCFGFORM_H
