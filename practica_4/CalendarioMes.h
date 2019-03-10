/***********************************************
*
* Interfaz de modulo: CalendarioMes
*
*   Este modulo contiene los elementos para
*   imprimir el calendario sobre el que se
*   muestran las variacines
*
***********************************************/

#pragma once

/* lista de los registros mensuales */
typedef struct TipoRegistroMensual{
  int diaMedicion;
  bool medicionExiste;
  };


typedef struct CalendarioMes{

  int GetFecha(int mes, int anno);
  bool EsBisiesto(int year);
  void PrintFechaCabecera(int mes, int anno);
  void PrintCabeceraCalendario();
  int DuracionMes(int month, int year);
  void PrintCuerpoCalendario(TipoRegistroMensual listaRegistros[],int mes, int anno);


};
