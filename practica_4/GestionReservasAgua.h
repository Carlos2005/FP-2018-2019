
/***********************************************
*
* Interfaz de modulo: GestionReservasAgua
*
*   Este modulo contiene los elementos para
*   dar de alta la cuenca y/o presa
*   anadir las nuevas mediciones*
*   imprimir los registros
*
*
***********************************************/

#pragma once
#include "CalendarioMes.h"

/* definimos las constantes */
const int MAX_NUM_CUENCAS = 3;
const int MAX_NUM_PRESAS = 5;
const int MAX_NUM_REGISTROS = 100;

/*definimos el tipo nombre para nombrar las cuencas y las presas */
typedef char TipoNombre[20];


/* tipo fecha */
typedef struct TipoFecha{
  int dia;
  int mes;
  int anno;
};

/* tipo medicion fecha + medicion */
typedef struct TipoMedicion{
  TipoFecha fechaMedicion;
  int volumenEmbalsado;
  float variacionEmbalsado;
};

/* estructura de la presa */
typedef struct Presa{
  TipoNombre nombrePresa;
  int capacidadPresa;
  int numeroMediciones;
  TipoMedicion registrosPresa[MAX_NUM_REGISTROS];
};

/* estructura de la cuenca  que contine el array de presas y mediciones */
typedef struct Cuenca{
  TipoNombre nombreCuenca;
  Presa presas[MAX_NUM_PRESAS];
  int numeroPresas;
  int totalMediciones;
  int numMedicionesCuenca;
  int totalCapacidad;
};

typedef struct GestionReservasAgua{
  void inicializar();
  void insertar(TipoNombre cuenca, TipoNombre presa, int volumenPresa);
  void nuevaMedicion(TipoNombre presa, int volumen, int dia, int mes, int anno);
  bool existeCuenca(TipoNombre cuenca);
  int buscaCuenca(TipoNombre cuenca);
  bool existePresa(int indiceCuenca, TipoNombre presa);
  int buscaPresa(int indiceCuenca, TipoNombre presa);
  bool esFechaValida(int dia, int mes, int anno);
  bool esFechaPosterior(int dia1, int mes1, int anno1, int dia2, int mes2, int anno);
  void registros(TipoNombre cuenca, TipoNombre presa, int dia, int mes, int anno);
  void imprimirRegistrosPresa(int indiceCuenca,int indicePresa, int dia, int mes, int anno);
  void variaciones(TipoNombre cuenca, TipoNombre presa, int mes, int anno);
  void imprimirVariacionesPresa(int indiceCuenca,int indicePresa, int mes, int anno);

private:
  Cuenca cuencas[MAX_NUM_CUENCAS];
  int numeroCuencas;
  CalendarioMes c;
  TipoRegistroMensual listaRegistrosMensuales[32];
  int volumenTotalRegion;
  int capacidadTotalRegion;
  int numMedicionesRegion;
};
