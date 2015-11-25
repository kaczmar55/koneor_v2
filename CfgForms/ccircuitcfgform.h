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

private slots:
    void on_l1ActiveChk_toggled(bool checked);

    void on_l2ActiveChk_toggled(bool checked);

    void on_l3ActiveChk_toggled(bool checked);

private:
    Ui::CCircuitCfgForm *ui;
};

#endif // CCIRCUITCFGFORM_H
