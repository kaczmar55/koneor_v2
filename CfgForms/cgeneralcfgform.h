#ifndef CGENERALCFGFORM_H
#define CGENERALCFGFORM_H

#include <QWidget>

namespace Ui {
class CGeneralCfgForm;
}

class CGeneralCfgForm : public QWidget
{
    Q_OBJECT

public:
    explicit CGeneralCfgForm(QWidget *parent = 0);
    ~CGeneralCfgForm();

private:
    Ui::CGeneralCfgForm *ui;
};

#endif // CGENERALCFGFORM_H
