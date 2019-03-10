/***********************************************
*
* Modulo: TipoMenu
*
*   Este modulo contiene los elementos para
*   general el menu del programa
*
***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Tipomenu.h"

/* inicializa toda la estructra inicial cuenca-presa-mediciones a 0 */
void TipoMenu::menuInicializar(){
    a.inicializar();
}

/* imprime por pantalla el menu principal */
void TipoMenu::pulsarIntro(){
  printf("\nPulsar INTRO para volver al menu principal\n");
  getchar();
  fflush(stdin);
  system("cls");

}


void TipoMenu::menuPrincipal(){

  system("cls");

	printf("******************************************\n");
	printf("     Fundamentos de Programacion\n");
	printf("Curso 2018-2019 - Practica 4 - Enero 2019 \n");
	printf("   Autor: Carlos J. de la Calleja Llado\n");
	printf("******************************************\n\n");

  do {
  printf("\n       Gestion de Reservas de Agua\n");
  printf("------------------------------------------\n");
  printf("    Alta cuenca/presa         (Pulsar A)\n");
  printf("    Nueva medicion            (Pulsar N)\n");
  printf("    Registros                 (Pulsar R)\n");
  printf("    Variaciones mensuales     (Pulsar V)\n");
  printf("    Salir                     (Pulsar S)\n\n");
  printf("Teclear una opcion valida  (A|N|R|V|S)? ");
  scanf("%c",&opcionPrincipal);
  fflush(stdin);
              switch (toupper(opcionPrincipal)) {
                  case 'A':
                      menuAltaCuencaPresa();
                      pulsarIntro();
                      break;
                  case 'N':
                      menuNuevaMedicion();
                      pulsarIntro();
                      break;
                   case 'R':
                      menuRegistros();
                      pulsarIntro();
                      break;
                   case 'V':
                      menuVariaciones();
                      pulsarIntro();
                      break;
                  case 'S':
                      printf("\n -- Fin del programa --\n");
                      break;
                  default:
                      printf("Por favor, introduzca una opcion valida.\n ");
                  }
          } while (toupper(opcionPrincipal) != 'S');
}

/* menu de altas */
void TipoMenu::menuAltaCuencaPresa(){

  printf("\n\n--Alta cuenca/presa--\n");
  printf("   Nombre de la cuenca? ");
  scanf("%s",&inputCuenca);
  fflush(stdin);
  printf("   Nombre de la presa? ");
  scanf("%s",&inputPresa);
  fflush(stdin);
  printf("   Capacidad de la presa? ");
  scanf("%d",&inputCapacidadPresaInt);
  fflush(stdin);
  a.insertar(inputCuenca, inputPresa, inputCapacidadPresaInt);
}

/* menu para la entrada de nuevas mediciones */
void TipoMenu::menuNuevaMedicion(){

  printf("\n\n-- Nueva medicion: --\n");
  printf("   Nombre de la presa? ");
  scanf("%s",&inputPresa);
  fflush(stdin);
  printf("   Volumen embalsado? ");
  scanf("%d",&volumenEmbalsado);
  fflush(stdin);
  printf("   Dia de lectura? ");
  scanf("%d",&diaLectura);
  fflush(stdin);
  printf("   Mes de lectura? ");
  scanf("%d",&mesLectura);
  fflush(stdin);
  printf("   Anno de lectura? ");
  scanf("%d",&annoLectura);
  fflush(stdin);
  a.nuevaMedicion(inputPresa,volumenEmbalsado,diaLectura,mesLectura,annoLectura);
 }

/*menu para la impresion de la lista de la mediciones */
void TipoMenu::menuRegistros(){

  printf("\n\n-- Registros: --\n");
  printf("   Nombre de la cuenca? ");
  scanf("%s",&inputCuenca);
  fflush(stdin);
  printf("   Nombre de la presa? ");
  scanf("%s",&inputPresa);
  fflush(stdin);
  printf("   Posterior al dia? ");
  scanf("%d",&diaLectura);
  fflush(stdin);
  printf("   Mes? ");
  scanf("%d",&mesLectura);
  fflush(stdin);
  printf("   Anno? ");
  scanf("%d",&annoLectura);
  fflush(stdin);
  a.registros(inputCuenca, inputPresa, diaLectura, mesLectura, annoLectura);
  }

void TipoMenu::menuVariaciones(){

  printf("\n\n-- Variaciones mensuales: --\n");
  printf("   Nombre de la cuenca? ");
  scanf("%s",&inputCuenca);
  fflush(stdin);
  printf("   Nombre de la presa? ");
  scanf("%s",&inputPresa);
  fflush(stdin);
  printf("   Mes? ");
  scanf("%d",&mesLectura);
  fflush(stdin);
  printf("   Anno? ");
  scanf("%d",&annoLectura);
  fflush(stdin);
  a.variaciones(inputCuenca, inputPresa, mesLectura, annoLectura);
 }
