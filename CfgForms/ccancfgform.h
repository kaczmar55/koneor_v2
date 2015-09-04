#ifndef CCANCFGFORM_H
#define CCANCFGFORM_H

#include <QWidget>

namespace Ui {
class CCanCfgForm;
}

class CCanCfgForm : public QWidget
{
    Q_OBJECT

public:
    explicit CCanCfgForm(QWidget *parent = 0);
    ~CCanCfgForm();

private:
    Ui::CCanCfgForm *ui;
};

#endif // CCANCFGFORM_H
