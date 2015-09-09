#ifndef CIOCFGFORM_H
#define CIOCFGFORM_H

#include "cmyform.h"
#include "eor_cfg.hpp"

namespace Ui {
class CIOCfgForm;
}

class CIOCfgForm : public CMyForm
{
    Q_OBJECT

public:
    explicit CIOCfgForm(QWidget *parent = 0);
    ~CIOCfgForm();

    bool getCfg(void* cfg_struct);
    bool setCfg(void* cfg_struct);

private:
    Ui::CIOCfgForm *ui;
};

#endif // CIOCFGFORM_H
