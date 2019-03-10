/***********************************************
*
* Interfaz de modulo: TipoMenu
*
*   Este modulo contiene los elementos para
*   general el menu del programa
*
***********************************************/

#pragma once
#include "GestionReservasAgua.h"

typedef struct TipoMenu{

  void menuPrincipal();
  void menuAltaCuencaPresa();
  void menuInicializar();
  void menuNuevaMedicion();
  void menuRegistros();
  void menuVariaciones();
  void pulsarIntro();

private:
  char opcionPrincipal;
  int inputCapacidadPresaInt, volumenEmbalsado, diaLectura, mesLectura, annoLectura;
  TipoNombre inputCuenca, inputPresa, inputCapacidadPresa;
  GestionReservasAgua a;

};
