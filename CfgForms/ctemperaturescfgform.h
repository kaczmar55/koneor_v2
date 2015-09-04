#ifndef CTEMPERATURESCFGFORM_H
#define CTEMPERATURESCFGFORM_H

#include <QWidget>

namespace Ui {
class CTemperaturesCfgForm;
}

class CTemperaturesCfgForm : public QWidget
{
    Q_OBJECT

public:
    explicit CTemperaturesCfgForm(QWidget *parent = 0);
    ~CTemperaturesCfgForm();

private:
    Ui::CTemperaturesCfgForm *ui;
};

#endif // CTEMPERATURESCFGFORM_H
