#ifndef CGENERALCFGFORM_H
#define CGENERALCFGFORM_H

#include "cmyform.h"
#include "eor_cfg.hpp"

namespace Ui {
class CGeneralCfgForm;
}

class CGeneralCfgForm : public CMyForm
{
    Q_OBJECT

public:
    explicit CGeneralCfgForm(QWidget *parent = 0);
    ~CGeneralCfgForm();

    bool getCfg(void* cfg_struct);
    bool setCfg(void* cfg_struct);
    void setFileVer(uint8_t ver, uint8_t rev);
    void setFileSize(uint32_t len);

private:
    Ui::CGeneralCfgForm *ui;

signals:
    void cirCountChange(int new_cir_count);
    void weatherAutomCountChange(int new_weather_autom_count);
private slots:
    void on_cirCount_valueChanged(int arg1);
    void on_weatherAutomCount_valueChanged(int arg1);
};

#endif // CGENERALCFGFORM_H
