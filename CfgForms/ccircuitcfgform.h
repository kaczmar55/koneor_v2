#ifndef CCIRCUITCFGFORM_H
#define CCIRCUITCFGFORM_H

#include <QWidget>
#include "eor_cfg.hpp"

namespace Ui {
class CCircuitCfgForm;
}

class CCircuitCfgForm : public QWidget
{
    Q_OBJECT

public:
    explicit CCircuitCfgForm(QWidget *parent = 0);
    ~CCircuitCfgForm();

    bool setCfg(circuit_cfg_t *circuit_cfg);
    bool getCfg(circuit_cfg_t *circuit_cfg);

private:
    Ui::CCircuitCfgForm *ui;
};

#endif // CCIRCUITCFGFORM_H
