#ifndef CETHERNETCFGFORM_H
#define CETHERNETCFGFORM_H

#include "cmyform.h"
#include "eor_cfg.hpp"

namespace Ui {
class CEthernetCfgForm;
}

class CEthernetCfgForm : public CMyForm
{
    Q_OBJECT

public:
    explicit CEthernetCfgForm(QWidget *parent = 0);
    ~CEthernetCfgForm();

    bool getCfg(void* cfg_struct);
    bool setCfg(void* cfg_struct);

private:
    Ui::CEthernetCfgForm *ui;
};

#endif // CETHERNETCFGFORM_H
