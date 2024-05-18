#include "viewadmin.h"
#include "ui_viewadmin.h"
#include <QMessageBox>

ViewAdmin::ViewAdmin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewAdmin)
{
    ui->setupUi(this);

    // Inisialisasi model untuk QTableView
    model = new QStandardItemModel(this);
    ui->tableView->setModel(model);

    // Inisialisasi kolom pada model
    QStringList headers;
    headers << "ID" << "Nama" << "Umur" << "Tanggal Masuk" << "Tanggal Keluar" << "Kontak Pasien";
    model->setHorizontalHeaderLabels(headers);
}

ViewAdmin::~ViewAdmin()
{
    delete ui;
}
void ViewAdmin::on_addButton_clicked()
{
    QStringList rowData;
    rowData << ui->idLineEdit->text() << ui->nameLineEdit->text() << ui->ageLineEdit->text()
            << ui->entryDateEdit->text() << ui->exitDateEdit->text() << ui->contactLineEdit->text();

    if(rowData.contains("")) {
        QMessageBox::warning(this, "Warning", "Please fill in all fields!");
        return;
    }

    patientsData.push_back(rowData);
    displayData();
}

void ViewAdmin::on_updateButton_clicked()
{
    int row = ui->tableView->currentIndex().row();
    if(row >= 0) {
        QStringList rowData;
        rowData << ui->idLineEdit->text() << ui->nameLineEdit->text() << ui->ageLineEdit->text()
                << ui->entryDateEdit->text() << ui->exitDateEdit->text() << ui->contactLineEdit->text();

        // Cek apakah semua inputan telah diisi
        if(rowData.contains("")) {
            QMessageBox::warning(this, "Warning", "Please fill in all fields!");
            return;
        }

        patientsData[row] = rowData;
        displayData();
    }
}

void ViewAdmin::on_deleteButton_clicked()
{
    int row = ui->tableView->currentIndex().row();
    if(row >= 0) {
        patientsData.remove(row);
        displayData();
    }
}

void ViewAdmin::displayData()
{
    model->removeRows(0, model->rowCount());
    for(int i = 0; i < patientsData.size(); ++i) {
        QStringList rowData = patientsData[i];
        QList<QStandardItem *> rowItems;
        foreach(QString text, rowData) {
            rowItems.append(new QStandardItem(text));
        }
        model->appendRow(rowItems);
    }
}

int ViewAdmin::sequentialSearch(const QString& namaCari)
{
    for(int i = 0; i < patientsData.size(); ++i) {
        QStringList rowData = patientsData[i];
        if (rowData.contains(namaCari)) {
            return i;
        }
    }
    return -1;
}

void ViewAdmin::on_pushButtonCari_clicked()
{
    QString namaCari = ui->searchLineEdit->text();
    int index = sequentialSearch(namaCari);
    if (index != -1) {
        QMessageBox::information(this, "Pencarian Berhasil", QString("ID pasien '%1' ditemukan di indeks %2").arg(namaCari).arg(index));
        ui->tableView->selectRow(index);
    } else {
        QMessageBox::warning(this, "Pencarian Gagal", QString("ID pasien '%1' tidak ditemukan.").arg(namaCari));
    }
}
