#ifndef CETHRTNETCFGFORM_H
#define CETHRTNETCFGFORM_H

#include <QWidget>

namespace Ui {
class CEthrtnetCfgForm;
}

class CEthrtnetCfgForm : public QWidget
{
    Q_OBJECT

public:
    explicit CEthrtnetCfgForm(QWidget *parent = 0);
    ~CEthrtnetCfgForm();

private:
    Ui::CEthrtnetCfgForm *ui;
};

#endif // CETHRTNETCFGFORM_H
