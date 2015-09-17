#ifndef CMODBUSSLAVECFGFORM_H
#define CMODBUSSLAVECFGFORM_H

#include "cmyform.h"
#include "eor_cfg.hpp"

namespace Ui {
class CModbusSlaveCfgForm;
}

class CModbusSlaveCfgForm : public CMyForm
{
    Q_OBJECT

public:
    explicit CModbusSlaveCfgForm(QWidget *parent = 0);
    ~CModbusSlaveCfgForm();

    bool getCfg(void* cfg_struct);
    bool setCfg(void* cfg_struct);

private slots:
    void on_modbusSlaveMediumCmb_currentIndexChanged(int index);

private:
    Ui::CModbusSlaveCfgForm *ui;
};

#endif // CMODBUSSLAVECFGFORM_H
