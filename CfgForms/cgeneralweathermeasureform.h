#ifndef CGENERALWEATHERMEASUREFORM_H
#define CGENERALWEATHERMEASUREFORM_H

#include <QWidget>

namespace Ui {
class CGeneralWeatherMeasureForm;
}

class CGeneralWeatherMeasureForm : public QWidget
{
    Q_OBJECT

public:
    explicit CGeneralWeatherMeasureForm(QWidget *parent = 0);
    ~CGeneralWeatherMeasureForm();

private:
    Ui::CGeneralWeatherMeasureForm *ui;
};

#endif // CGENERALWEATHERMEASUREFORM_H
