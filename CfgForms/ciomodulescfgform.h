#ifndef CIOMODULESCFGFORM_H
#define CIOMODULESCFGFORM_H

#include "cmyform.h"
#include "eor_cfg.hpp"

namespace Ui {
class CIoModulesCfgForm;
}

class CIoModulesCfgForm : public CMyForm
{
    Q_OBJECT

public:
    explicit CIoModulesCfgForm(QWidget *parent = 0);
    ~CIoModulesCfgForm();

    bool getCfg(void* cfg_struct);
    bool setCfg(void* cfg_struct);

private:
    Ui::CIoModulesCfgForm *ui;
};

#endif // CIOMODULESCFGFORM_H
