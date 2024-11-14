#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    private slots:
    void on_ajouter_Materiel_clicked();
    void on_supression_Materiel_clicked();
    void on_modifier_Materiel_clicked();
};

#endif // MAINWINDOW_H