/***********************************************
*
* Modulo: CalendarioMes
*
*   Este modulo contiene los elementos para
*   imprimir el calendario sobre el que se
*   muestran las variacines
*
***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CalendarioMes.h"

/* Devuelve el dia de la semana */
int CalendarioMes::GetFecha(int mes, int anno)
{

int q,m,k,j,h;

  if (mes == 1)
  {
    mes = 13;
    anno--;
  }
  if (mes == 2)
  {
    mes = 14;
    anno--;
  }
  q = 1;
  m = mes;
  k = anno % 100;
  j = anno / 100;
  h = q + 13*(m+1)/5 + k + k/4 + j/4 + 5*j;
  h = h % 7;

  /* devuelve el dia de la semana */
  return  (h+5)%7;
}

/* devuelve true si el anno es bisiesto */
bool CalendarioMes::EsBisiesto(int year)
{

    if (year % 400 == 0){
        return true;}


    if (year % 100 == 0){
        return false;}


    if (year % 4 == 0){
        return true;}
    return false;
}

/* solo imprime la fecha en la cabecera del calendario */
void CalendarioMes::PrintFechaCabecera(int mes, int anno)
{

  if(mes == 1){
    printf("ENERO                  %d\n",anno);
    }else if(mes ==2){
    printf("FEBRERO                %d\n",anno);
    }else if(mes ==3){
    printf("MARZO                  %d\n",anno);
    }else if(mes ==4){
    printf("ABRIL                  %d\n",anno);
     }else if(mes ==5){
    printf("MAYO                   %d\n",anno);
    }else if(mes ==6){
    printf("JUNIO                  %\n",anno);
    }else if(mes ==7){
    printf("JULIO                  %d\n",anno);
    }else if(mes ==8){
    printf("AGOSTO                 %d\n",anno);
    }else if(mes ==9){
    printf("SEPTIEMBRE             %d\n",anno);
    }else if(mes ==10){
    printf("OCTUBRE                %d\n",anno);
    }else if(mes ==11){
    printf("NOVIEMBRE              %d\n",anno);
    }else {printf("DICIEMBRE              %d\n",anno);
          }

}

/* imprime la cabecera del calendario */
void CalendarioMes::PrintCabeceraCalendario(){

  printf("===========================\n");

  printf("LU  MA  MI  JU  VI | SA  DO\n");

  printf("===========================\n");

}

/* calcula la duracion en dias del mes corriente */
int CalendarioMes::DuracionMes(int month, int year){
  if(month == 2 ){

    if (EsBisiesto(year) == true){
                              return 29;}
      else {return 28;}

  }else if (month == 4 || month == 6 || month == 9 || month == 11 )
                                        { return 30;}

  else {return 31;}


}

/* imprime sobre el calendario las variaciones mensuales introducidas mediate
un array llamado listaRegistros[]  */
void CalendarioMes::PrintCuerpoCalendario(TipoRegistroMensual listaRegistros[],int mes, int anno){

  int semana = 1;
  int duracionMes = DuracionMes(mes,anno); /* duracion del mes dependiendo ano bisiesto */
  int diaSemana = GetFecha(mes, anno); /* dia de la semana en el que empieza el mes */
  int duracionTotal;
  int diaActual;

  duracionTotal = duracionMes + diaSemana ;

  if(duracionTotal%7 !=0){
  duracionTotal = duracionTotal + (7-duracionTotal%7);
  }

  for(int i=1; i < duracionTotal+1; i++){

    diaActual = i - diaSemana;

    if(diaActual<0 || diaActual==0 || diaActual>duracionMes){
      printf("  ");}
      else{

         if (listaRegistros[diaActual].medicionExiste==false){
           printf("--");

         }
         else {

             if(listaRegistros[diaActual].diaMedicion == 0){
              printf("00");
             }
             else if(listaRegistros[diaActual].diaMedicion <-9 || listaRegistros[diaActual].diaMedicion >9){
               printf("EE");
             }

             else if(listaRegistros[diaActual].diaMedicion > 0 ){
               printf("+%1d",listaRegistros[diaActual].diaMedicion);
             }
             else { printf("%2d",listaRegistros[diaActual].diaMedicion);}

         }

      }

    if(semana%5 == 0){
      printf(" | ");
    } else if(i%7 == 0){
      printf("\n");
      semana=0;
    }else {printf("  ");}

    semana++;

  }
  printf("\n");

}
