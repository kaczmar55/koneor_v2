#ifndef CTGFMCFGFORM_H
#define CTGFMCFGFORM_H

#include <QWidget>

namespace Ui {
class CTgfmCfgForm;
}

class CTgfmCfgForm : public QWidget
{
    Q_OBJECT

public:
    explicit CTgfmCfgForm(QWidget *parent = 0);
    ~CTgfmCfgForm();

private:
    Ui::CTgfmCfgForm *ui;
};

#endif // CTGFMCFGFORM_H
