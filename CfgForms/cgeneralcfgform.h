#ifndef CGENERALCFGFORM_H
#define CGENERALCFGFORM_H

#include <QWidget>
#include "eor_cfg.hpp"

namespace Ui {
class CGeneralCfgForm;
}

class CGeneralCfgForm : public QWidget
{
    Q_OBJECT

public:
    explicit CGeneralCfgForm(QWidget *parent = 0);
    ~CGeneralCfgForm();

    bool getCfg(general_cfg_t *general_cfg);
    bool setCfg(general_cfg_t *general_cfg);

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
