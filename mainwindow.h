#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_menuTreeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void on_actionZako_cz_triggered();
    void on_cirCountChanged(int new_circuit_count);
    void on_weatherAutomCountChanged(int new_weather_autom_count);

private:
    Ui::MainWindow *ui;
    QTreeWidgetItem* addForm(QString name, QWidget* widget, int id1, int id2, QTreeWidgetItem *parent);

    QTreeWidgetItem *weatherAutomItem, *circuitItem;
    bool doNotChange;
};

#endif // MAINWINDOW_H
