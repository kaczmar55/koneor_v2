#ifndef CETHERNETCFGFORM_H
#define CETHERNETCFGFORM_H

#include <QWidget>
#include "eor_cfg.hpp"

namespace Ui {
class CEthernetCfgForm;
}

class CEthernetCfgForm : public QWidget
{
    Q_OBJECT

public:
    explicit CEthernetCfgForm(QWidget *parent = 0);
    ~CEthernetCfgForm();

    bool getCfg(eth_cfg_t *eth_cfg);
    bool setCfg(eth_cfg_t *eth_cfg);

private:
    Ui::CEthernetCfgForm *ui;
};

#endif // CETHERNETCFGFORM_H
