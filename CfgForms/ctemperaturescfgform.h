#ifndef CTEMPERATURESCFGFORM_H
#define CTEMPERATURESCFGFORM_H

#include "cmyform.h"
#include "eor_cfg.hpp"

namespace Ui {
class CTemperaturesCfgForm;
}

class CTemperaturesCfgForm : public CMyForm
{
    Q_OBJECT

public:
    explicit CTemperaturesCfgForm(QWidget *parent = 0);
    ~CTemperaturesCfgForm();

    bool getCfg(void* cfg_struct);
    bool setCfg(void* cfg_struct);

private slots:
    void on_ecoBtn_clicked();

    void on_stdBtn_clicked();

    void on_maxBtn_clicked();

private:
    Ui::CTemperaturesCfgForm *ui;
};

#endif // CTEMPERATURESCFGFORM_H
