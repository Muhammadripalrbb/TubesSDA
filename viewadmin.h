#ifndef VIEWADMIN_H
#define VIEWADMIN_H

#include <QMainWindow>
#include <QString>
#include <QStandardItemModel>
#include <QVector>

namespace Ui {
class ViewAdmin;
}

class ViewAdmin : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewAdmin(QWidget *parent = nullptr);
    ~ViewAdmin();

private slots:
    void on_addButton_clicked();
    void on_updateButton_clicked();
    void on_deleteButton_clicked();
    void on_pushButtonCari_clicked(); // Perbaikan: Ganti nama fungsi pencarian
    void displayData();
    int sequentialSearch(const QString& namaCari); // Perbaikan: Menggunakan nama yang sesuai

private:
    Ui::ViewAdmin *ui;
    QStandardItemModel *model;
    QVector<QStringList> patientsData;
};

#endif // VIEWADMIN_H
