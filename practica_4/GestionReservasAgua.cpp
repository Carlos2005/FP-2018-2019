/***********************************************
*
* modulo: GestionReservasAgua
*
*   Este modulo contiene los elementos para
*   dar de alta la cuenca y/o presa
*   anadir las nuevas mediciones*
*   imprimir los registros
*
*
***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GestionReservasAgua.h"

/* nos devuelve true si la fecha1 es posterior ala fecha 2*/
bool GestionReservasAgua::esFechaPosterior(int dia1, int mes1, int anno1, int dia2, int mes2, int anno2){

    bool fechaMayor=false;

    if(anno1>anno2){
      fechaMayor=true;
      return fechaMayor;
    } else if(anno1 == anno2){
        if (mes1>mes2){
          fechaMayor=true;
          return fechaMayor;
        }
        else if (mes1==mes2){
          if (dia1>dia2){
          fechaMayor=true;
          return fechaMayor;}
           }
        }
     return fechaMayor;
}

/* Comprueba que la fecha sea valida */
bool GestionReservasAgua::esFechaValida(int dia, int mes, int anno){

  bool fechaValida=false;
    if(anno >=1900 && anno <=2100)  /* comprueba el anno */
    {
        if( mes >=1 && mes <=12) /* comprueba el mes */
        {
            /* comprueba el dia */
            if((dia >=1 && dia <=31) && (mes==1 || mes==3 || mes ==5 || mes == 7 || mes== 8 || mes == 10 || mes == 12))
                {
                 fechaValida=true;
                }
            else if((dia>=1 && dia<=30) && (mes==4 || mes==6 || mes==9 || mes==11)){
                fechaValida=true;
                }
            else if((dia>=1 && dia<=28) && (mes==2))
                {
                 fechaValida=true;
                }
            else if(dia==29 && mes==2 && (anno %400 == 0 ||(anno %4 ==0 && anno%100 != 0)))
                {
                fechaValida=true;
                }
            else{
                /* fecha invalida */
                }
        }
        else
        {
            /* mes incorrecto */
        }
    }
    else
    {
        /* anno incorrecto */
    }

    return fechaValida;
}

/* imprime todos los registros a partir de una fecha dada */
void GestionReservasAgua::imprimirRegistrosPresa(int indiceCuenca, int indicePresa, int dia, int mes, int anno){

  int medicionFinal;
  float porcentaje;

   medicionFinal = cuencas[indiceCuenca].presas[indicePresa].numeroMediciones;

       for(int i=0; i<medicionFinal; i++){

        if(esFechaPosterior(cuencas[indiceCuenca].presas[indicePresa].registrosPresa[i].fechaMedicion.dia,
         cuencas[indiceCuenca].presas[indicePresa].registrosPresa[i].fechaMedicion.mes,
         cuencas[indiceCuenca].presas[indicePresa].registrosPresa[i].fechaMedicion.anno,
          dia,mes,anno)){
             porcentaje = (float(cuencas[indiceCuenca].presas[indicePresa].registrosPresa[i].volumenEmbalsado) / float(cuencas[indiceCuenca].presas[indicePresa].capacidadPresa)) * 100.0;

             printf("%-15s %-15s  %4d(%3.1f%%)      %2d/%2d/%4d \n",
             cuencas[indiceCuenca].nombreCuenca,
             cuencas[indiceCuenca].presas[indicePresa].nombrePresa,
             cuencas[indiceCuenca].presas[indicePresa].registrosPresa[i].volumenEmbalsado,
             porcentaje,
             cuencas[indiceCuenca].presas[indicePresa].registrosPresa[i].fechaMedicion.dia,
             cuencas[indiceCuenca].presas[indicePresa].registrosPresa[i].fechaMedicion.mes,
             cuencas[indiceCuenca].presas[indicePresa].registrosPresa[i].fechaMedicion.anno);

            }
       }
}

/* Guarda en una array todas las variaciones mensuales */
void GestionReservasAgua::imprimirVariacionesPresa(int indiceCuenca, int indicePresa, int mes, int anno){

  int medicionFinal;
  float porcentaje;

   medicionFinal = cuencas[indiceCuenca].presas[indicePresa].numeroMediciones;

   for(int j=1; j<32; j++){

     for(int i=0; i<medicionFinal; i++){

        if(cuencas[indiceCuenca].presas[indicePresa].registrosPresa[i].fechaMedicion.dia == j &&
           cuencas[indiceCuenca].presas[indicePresa].registrosPresa[i].fechaMedicion.mes == mes &&
           cuencas[indiceCuenca].presas[indicePresa].registrosPresa[i].fechaMedicion.anno == anno)
            {

            listaRegistrosMensuales[j].diaMedicion=listaRegistrosMensuales[j].diaMedicion + int(cuencas[indiceCuenca].presas[indicePresa].registrosPresa[i].variacionEmbalsado);
            listaRegistrosMensuales[j].medicionExiste=true;
            }

      }
     }
}

 /* inserta la cuenca y o presa en la estructura principal */
void GestionReservasAgua::insertar(TipoNombre cuenca, TipoNombre presa, int volumenPresa){

  int indiceCuencas;

  if (!existeCuenca(cuenca) && numeroCuencas > 2){
    printf("\n*** Error: alcanzado el numero maximo de cuencas ***\n");
    return;

   } else if (existeCuenca(cuenca)){
    /* buscamos el indice e insertamos solo la presa */
    indiceCuencas = buscaCuenca(cuenca);
    /* condiciones si la presa existe
     o si ya se ha llegado al numero maximo de presas */
    if (cuencas[indiceCuencas].numeroPresas > 2){
       printf("\n*** Error: alcanzado el numero maximo de presas ***\n");
      return;
    }else if(existePresa(indiceCuencas, presa)){
        printf("\n*** Error: la presa ya existe ***\n");
      return;
    }
    else {
    strcpy( cuencas[indiceCuencas].presas[cuencas[indiceCuencas].numeroPresas].nombrePresa , presa);
    cuencas[indiceCuencas].presas[cuencas[indiceCuencas].numeroPresas].capacidadPresa = volumenPresa;
    cuencas[indiceCuencas].totalCapacidad = cuencas[indiceCuencas].totalCapacidad + volumenPresa;
	  capacidadTotalRegion = capacidadTotalRegion + volumenPresa;
    cuencas[indiceCuencas].numeroPresas++;

    printf("\n*** Alta de presa correcta ***\n");
    return;
    }
  }
  else{
    /* alta normal */
     strcpy( cuencas[numeroCuencas].nombreCuenca , cuenca);
     strcpy( cuencas[numeroCuencas].presas[cuencas[numeroCuencas].numeroPresas].nombrePresa, presa);
     cuencas[numeroCuencas].presas[cuencas[numeroCuencas].numeroPresas].capacidadPresa = volumenPresa;
     cuencas[numeroCuencas].totalCapacidad = cuencas[numeroCuencas].totalCapacidad + volumenPresa;
	   capacidadTotalRegion = capacidadTotalRegion + volumenPresa;
     cuencas[numeroCuencas].numeroPresas++;
     numeroCuencas++;
     printf("\n *** Alta de cuenca y presa correcta **** \n\n");
     return;
  }
}

/* inicializa los valores de la estructura principal a 0 */
void GestionReservasAgua::inicializar(){
  numeroCuencas = 0;
  volumenTotalRegion = 0;
  capacidadTotalRegion = 0;
  numMedicionesRegion = 0;
  for (int i=0; i<MAX_NUM_CUENCAS; i++){
    cuencas[i].numeroPresas=0;
    cuencas[i].totalMediciones=0;
    cuencas[i].totalCapacidad=0;
    cuencas[i].numMedicionesCuenca = 0;
    for (int j=0; j<MAX_NUM_PRESAS; j++){
      cuencas[i].presas[j].numeroMediciones=0;
    }
  }
}

/* devuelve true si la cuenca existe en la estructura */
bool GestionReservasAgua::existeCuenca(TipoNombre cuenca){

  bool encontrado;
  int contador;
  encontrado = false;
  contador =0;
  while ((contador<numeroCuencas) && !encontrado){
   if (strcmp(cuencas[contador].nombreCuenca,cuenca)==0){
      encontrado = true;  /* la cuenca existe */
      }
   contador++;
   }
    if (!encontrado)  {
		/* la cuenca no exite */
    }
  return encontrado;
}

/* devuelve true si la presa existe en la estructura */
bool GestionReservasAgua::existePresa(int indiceCuenca, TipoNombre presa){

  bool encontrado;
  int contador;
  encontrado = false;
  contador =0;
  while ((contador<cuencas[indiceCuenca].numeroPresas) && !encontrado){

   if (strcmp(cuencas[indiceCuenca].presas[contador].nombrePresa,presa)==0){
      encontrado = true; /* la presa existe */
      }
   contador++;
   }
    if (!encontrado)  {
		/* la presa no existe */
    }
  return encontrado;
}

/* Nos devuelve el indice de la cuenca en la estructura */
int GestionReservasAgua::buscaCuenca(TipoNombre cuenca){

  bool encontrado;
  int contador;
  encontrado = false;
  contador =0;
  while ((contador<numeroCuencas) && !encontrado){
   if (strcmp(cuencas[contador].nombreCuenca,cuenca)==0){
      encontrado = true;
      return contador;  /* devuelve el indice de la cuenca */
      }
   contador++;
   }
}

/* Nos devuelve el indice de la presa en la estructura */
int GestionReservasAgua::buscaPresa(int indiceCuenca, TipoNombre presa){

  bool encontrado;
  int contador;
  encontrado = false;
  contador =0;
  while ((contador<cuencas[indiceCuenca].numeroPresas) && !encontrado){

   if (strcmp(cuencas[indiceCuenca].presas[contador].nombrePresa,presa)==0){
      encontrado = true;
      return contador;  /* devuelve el indice de la presa */
      }
   contador++;
   }
}

/* Introducimos una nueva medicion del volumen de la presa */
void GestionReservasAgua::nuevaMedicion(TipoNombre presa, int volumen, int dia, int mes, int anno){

  int contador=0;
  float volumenAnterior=0.0;
  float volumenActual=0.0;
  int indiceCuenca;
  int indicePresa;
  int indiceMedicion;
  int dia2, mes2, anno2;
  bool encontrado;
  encontrado = false;

  while(contador<3 && !encontrado){
    if (existePresa(contador,presa)){
      indiceCuenca = contador;
      encontrado = true;
    }
    contador ++;
  }

  if (!encontrado){
    printf("\n*** Error: presa no encontrada ***\n");
    return;
  }
  else {
      indicePresa = buscaPresa(indiceCuenca, presa); /* presa encontrada */

          if (cuencas[indiceCuenca].presas[indicePresa].capacidadPresa < volumen){
            printf("\n**** Error: el volumen embalsado excede la capacidad de la presa ****\n");
            return;
          }
          else if(!esFechaValida(dia, mes, anno)){
            printf("\n**** Error: fecha no valida ****\n");
            return;
          }
          else {

              indiceMedicion = cuencas[indiceCuenca].presas[indicePresa].numeroMediciones;

			  /* comprobamos que no se llegue al numero maximo de mediciones */

			  if(indiceMedicion==MAX_NUM_REGISTROS){

				 /* corremos todos los registros a la izquierda una posicion y liberamos el ultimo */

				 for(int i=1; i<MAX_NUM_REGISTROS; i++){

					cuencas[indiceCuenca].presas[indicePresa].registrosPresa[i].volumenEmbalsado = cuencas[indiceCuenca].presas[i-1].registrosPresa[i].volumenEmbalsado;
					cuencas[indiceCuenca].presas[indicePresa].registrosPresa[i].variacionEmbalsado = cuencas[indiceCuenca].presas[i-1].registrosPresa[i].variacionEmbalsado;
					cuencas[indiceCuenca].presas[indicePresa].registrosPresa[i].fechaMedicion.dia = cuencas[indiceCuenca].presas[i-1].registrosPresa[i].fechaMedicion.dia;
					cuencas[indiceCuenca].presas[indicePresa].registrosPresa[i].fechaMedicion.mes = cuencas[indiceCuenca].presas[i-1].registrosPresa[i].fechaMedicion.mes;
					cuencas[indiceCuenca].presas[indicePresa].registrosPresa[i].fechaMedicion.anno = cuencas[indiceCuenca].presas[i-1].registrosPresa[i].fechaMedicion.anno;

				 }
          cuencas[indiceCuenca].presas[indicePresa].numeroMediciones = cuencas[indiceCuenca].presas[indicePresa].numeroMediciones -1;
				  indiceMedicion = indiceMedicion-1;

			  }

              if(indiceMedicion==0){          /* introducimos la primera medicion */
                cuencas[indiceCuenca].presas[indicePresa].registrosPresa[indiceMedicion].volumenEmbalsado = volumen;
                cuencas[indiceCuenca].presas[indicePresa].registrosPresa[indiceMedicion].variacionEmbalsado = 0.0;
                cuencas[indiceCuenca].presas[indicePresa].registrosPresa[indiceMedicion].fechaMedicion.dia=dia;
                cuencas[indiceCuenca].presas[indicePresa].registrosPresa[indiceMedicion].fechaMedicion.mes=mes;
                cuencas[indiceCuenca].presas[indicePresa].registrosPresa[indiceMedicion].fechaMedicion.anno=anno;
                cuencas[indiceCuenca].presas[indicePresa].numeroMediciones++;
                printf("\n**** Medicion correcta y guardada  ****\n");
                cuencas[indiceCuenca].totalMediciones = cuencas[indiceCuenca].totalMediciones + volumen;
                cuencas[indiceCuenca].numMedicionesCuenca =  cuencas[indiceCuenca].numMedicionesCuenca +1;
				        volumenTotalRegion = volumenTotalRegion + volumen;
				        numMedicionesRegion = numMedicionesRegion + 1;
                return;
              }
              else {
                       dia2=cuencas[indiceCuenca].presas[indicePresa].registrosPresa[indiceMedicion-1].fechaMedicion.dia;
                       mes2=cuencas[indiceCuenca].presas[indicePresa].registrosPresa[indiceMedicion-1].fechaMedicion.mes;
                       anno2=cuencas[indiceCuenca].presas[indicePresa].registrosPresa[indiceMedicion-1].fechaMedicion.anno;

                       if(esFechaPosterior(dia, mes, anno, dia2, mes2, anno2)){

                          cuencas[indiceCuenca].presas[indicePresa].registrosPresa[indiceMedicion].volumenEmbalsado = volumen;

                          volumenAnterior = float(cuencas[indiceCuenca].presas[indicePresa].registrosPresa[indiceMedicion-1].volumenEmbalsado);
                          cuencas[indiceCuenca].presas[indicePresa].registrosPresa[indiceMedicion].variacionEmbalsado = float((float(volumen)-float(volumenAnterior))/float(volumenAnterior))*100.0;

                          cuencas[indiceCuenca].presas[indicePresa].registrosPresa[indiceMedicion].fechaMedicion.dia=dia;
                          cuencas[indiceCuenca].presas[indicePresa].registrosPresa[indiceMedicion].fechaMedicion.mes=mes;
                          cuencas[indiceCuenca].presas[indicePresa].registrosPresa[indiceMedicion].fechaMedicion.anno=anno;

                          cuencas[indiceCuenca].presas[indicePresa].numeroMediciones++;
                          cuencas[indiceCuenca].totalMediciones = cuencas[indiceCuenca].totalMediciones + volumen;
                          cuencas[indiceCuenca].numMedicionesCuenca =  cuencas[indiceCuenca].numMedicionesCuenca +1;
                          volumenTotalRegion = volumenTotalRegion + volumen;
                          numMedicionesRegion = numMedicionesRegion + 1;

                          printf("\n**** Medicion correcta y guardada  ****\n");
                       }
                       else{
                           printf("\n**** Error: la fecha no es posterior  ****\n");
                           return;
                       }
              }

          }

        }
}


/* Imprimimos la medicions por orden desde la fecha introducida */
void GestionReservasAgua::registros(TipoNombre cuenca, TipoNombre presa, int dia, int mes, int anno){

  int contador=0;
  float porcentaje;
  int indiceCuenca=0;
  int indicePresa=0;
  int medicionFinal=0;
  bool encontrado;
  encontrado = false;

  if(!esFechaValida(dia, mes, anno)){
            printf("\n**** Error: fecha no valida ****\n");
            return;
  }

  else if(!existeCuenca(cuenca)){

    /* si la cuenca no existe listamos toda la region */

     printf("\nCuenca          Presa             Volumen          Fecha\n");
         printf("------------------------------------------------------------\n");

     for(int i=0; i<numeroCuencas ; i++){

         for(int j=0;j<cuencas[i].numeroPresas ; j++){

          imprimirRegistrosPresa(i, j, dia, mes, anno);

        }
      /* imprimimos el total de la cuenca */

		  porcentaje = (float(cuencas[i].totalMediciones)/float(cuencas[i].totalCapacidad)) * 100.0 / float(cuencas[indiceCuenca].numMedicionesCuenca);
	    printf("%-15s TOTAL            %4d(%3.1f%%)\n",cuencas[i].nombreCuenca,cuencas[i].totalMediciones, porcentaje);

     }
      /* imprimimos el total de la region */

	    porcentaje = (float(volumenTotalRegion)/float(capacidadTotalRegion)) *100.0 / float(numMedicionesRegion);
	    printf("TODAS           TOTAL            %4d(%3.1f%%)\n",volumenTotalRegion, porcentaje);

    return;
  }

  else {

    while(contador<3 && !encontrado){
    if (existePresa(contador,presa)){
      indiceCuenca = contador;
      encontrado = true;
      }
    contador ++;
    }

    if(encontrado){

        /* listamos solo la presa */

       printf("\nCuenca          Presa             Volumen          Fecha\n");
       printf("------------------------------------------------------------\n");

       indicePresa = buscaPresa(indiceCuenca, presa);

       imprimirRegistrosPresa(indiceCuenca, indicePresa, dia, mes, anno);

        /* imprimimos el total de la cuenca */

        porcentaje = (float(cuencas[indiceCuenca].totalMediciones)/float(cuencas[indiceCuenca].totalCapacidad)) * 100.0 / float(cuencas[indiceCuenca].numMedicionesCuenca);
        printf("%-15s TOTAL            %4d(%3.1f%%)\n",cuencas[indiceCuenca].nombreCuenca,cuencas[indiceCuenca].totalMediciones, porcentaje);

       /* imprimir total de la region */

        porcentaje = (float(volumenTotalRegion)/float(capacidadTotalRegion)) * 100.0 / float(numMedicionesRegion);
        printf("TODAS           TOTAL            %4d(%3.1f%%)\n",volumenTotalRegion,porcentaje);

       return;

    } else{

      /* listmos toda la cuenca */

         printf("\nCuenca          Presa             Volumen          Fecha\n");
         printf("------------------------------------------------------------\n");

         for(int i=0;i<cuencas[indiceCuenca].numeroPresas ; i++){
            imprimirRegistrosPresa(indiceCuenca, i, dia, mes, anno);

        }

	    /* imprimimos toda la cuenca */

        porcentaje = (float(cuencas[indiceCuenca].totalMediciones)/float(cuencas[indiceCuenca].totalCapacidad)) *100.0 / float(cuencas[indiceCuenca].numMedicionesCuenca);
        printf("%-15s TOTAL            %4d(%3.1f%%)\n",cuencas[indiceCuenca].nombreCuenca,cuencas[indiceCuenca].totalMediciones, porcentaje);

            // imprimir el total de la region

        porcentaje = (float(volumenTotalRegion)/float(capacidadTotalRegion)) * 100.0 / float(numMedicionesRegion);
        printf("TODAS           TOTAL            %4d(%3.1f%%)\n",volumenTotalRegion, porcentaje);

      return;
    }
  }
}

/* utilizando la TAD CalendarioMes imprimimos todas la variaciones */

void GestionReservasAgua::variaciones(TipoNombre cuenca, TipoNombre presa, int mes, int anno){

  int dia =1;
  int contador=0;
  float porcentaje= 0.0;
  float porcentajeCuenca= 0.0;
  float porcentajeRegion= 0.0;
  int indiceCuenca=0;
  int indicePresa=0;
  int medicionFinal=0;
  bool encontrado;
  encontrado = false;

  /* inicializamos a 0 el array que contiene las mediciones */

    for (int k=0; k<32; k++){
        listaRegistrosMensuales[k].diaMedicion=0;
        listaRegistrosMensuales[k].medicionExiste=false;
  }


  if(mes<1 || mes>12){
            printf("\n**** Error: fecha no valida ****\n");
            return;
  }

  else if(!existeCuenca(cuenca)){
     for(int i=0; i<numeroCuencas ; i++){
         for(int j=0;j<cuencas[i].numeroPresas ; j++){
         imprimirVariacionesPresa(i, j, mes, anno);
        }
     }
      /* imprimimos el total de la region */

    printf("\n%% Variacion Agua Embalsada\n");
    printf("\nCuenca: TODAS\tPresa: TODAS\n");
		c.PrintFechaCabecera(mes,anno);
		c.PrintCabeceraCalendario();
		c.PrintCuerpoCalendario(listaRegistrosMensuales, mes, anno);

    return;
  }

  else {
    while(contador<3 && !encontrado){
    if (existePresa(contador,presa)){
      indiceCuenca = contador;
      encontrado = true;
      }
    contador ++;
    }
    if(encontrado){
        indicePresa = buscaPresa(indiceCuenca, presa);
        imprimirVariacionesPresa(indiceCuenca, indicePresa, mes, anno);
        printf("\n%% Variacion Agua Embalsada\n");
        printf("\nCuenca: %s\tPresa: %s\n",cuencas[indiceCuenca].nombreCuenca,cuencas[indiceCuenca].presas[indicePresa].nombrePresa);
        c.PrintFechaCabecera(mes,anno);
        c.PrintCabeceraCalendario();
        c.PrintCuerpoCalendario(listaRegistrosMensuales, mes, anno);
        return;

    } else{

         for(int i=0;i<cuencas[indiceCuenca].numeroPresas ; i++){
          imprimirVariacionesPresa(indiceCuenca, i, mes, anno);

        }
        printf("\n%% Variacion Agua Embalsada\n");
        printf("\nCuenca: %s\tPresa: TODAS\n",cuencas[indiceCuenca].nombreCuenca);

        c.PrintFechaCabecera(mes,anno);
        c.PrintCabeceraCalendario();
        c.PrintCuerpoCalendario(listaRegistrosMensuales, mes, anno);

      return;
    }
  }
}
