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

    bool getCfgJsn2(jsn2_module_cfg_t *jsn2_module_cfg);
    bool setCfgJsn2(jsn2_module_cfg_t *jsn2_module_cfg);

    bool getCfgMeter(meter_cfg_t *meter_cfg);
    bool setCfgMeter(meter_cfg_t *meter_cfg);

private slots:
    void on_addIoModuleBtn_clicked();

    void on_delIoModuleBtn_clicked();

    void on_addJsn2Btn_clicked();

    void on_delJsn2Btn_clicked();

    void on_addMeterBtn_clicked();

    void on_delMeterBtn_clicked();

private:
    Ui::CIoModulesCfgForm *ui;
};

#endif // CIOMODULESCFGFORM_H
