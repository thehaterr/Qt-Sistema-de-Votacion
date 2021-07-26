#include "certificado.h"
#include "ui_certificado.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
Certificado::Certificado(QWidget *parent, QString nombre, QString cedula) :
    QDialog(parent),
    ui(new Ui::Certificado)
{
    ui->setupUi(this);
    this->nombre = cedula;
    imagen = QImage(QString("%1.jpeg").arg(cedula));
    //Crear el lienzo
    lienzo = QPixmap(523,200);
    //Invocar al metodo dibujar
    this->dibujar(nombre, cedula);
}

Certificado::~Certificado()
{
    delete ui;
}

void Certificado::dibujar(QString nombre, QString cedula)
{
    QTime tiempo = QTime::currentTime();
    QDate fecha = QDate::currentDate();
    //Rellenar el lienzo de color blanco
    lienzo.fill(Qt::white);

    //Crear el pintor
    QPainter painter(&lienzo);

    int x = 50;
    int y = 50;
    painter.drawImage(x,y, imagen.scaled(100,110));
    painter.setFont(QFont("Arial", 10));

    painter.drawText(x+200, y,"Certificado de Votación");
    painter.drawText(x+225, y+17,"Elecciones 2021");
    painter.drawText(x+200, y+50,"Nombre: " + nombre);
    painter.drawText(x+200, y+70,"Cedula: " + cedula);
    painter.drawText(x+200, y+90,"Fecha: " + fecha.toString("dd-MM-yyyy"));
    painter.drawText(x+200, y+110,"Hora: " + tiempo.toString("hh:mm"));
    ui->outCertificado->setPixmap(lienzo);
}

void Certificado::on_cmdGuardar_released()
{
    //Crear un objeto QDir a partir del directorio del usuario
    QDir directorio = QDir::current();
    //Agregar al path absoluto del objeto un nombre por defecto del archivo
    QString pathArchivo = directorio.absolutePath() + "/Certificados/";
    lienzo.save(QString(pathArchivo + nombre + ".png"));
    this->close();
}
