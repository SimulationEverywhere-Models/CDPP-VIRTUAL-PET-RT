/*******************************************************************
*
*  DESCRIPTION: Atomic Model Sistema Excretor
*
*  AUTHOR: Grupo2- II02 Baranek, Riccillo
*
*  EMAIL: mailto: abaranek@dc.uba.ar
*         mailto: mr9o@dc.uba.ar
*
*  DATE: 25/9/2002
*
*******************************************************************/

#include <string.h>
#include "SistemaSalud.h"
#include "message.h"
#include "parsimu.h"


/*******************************************************************
* CLASS SistemaSalud
*********************************************************************/

/*******************************************************************
* Nombre de la Funci¢n: SistemaSalud::SistemaSalud()
* Descripción: Constructor
********************************************************************/
SistemaSalud::SistemaSalud( const string &name ) :
    Atomic( name ),
    inNutrientes( addInputPort( "inNutrientes" ) ),
    inHigiene( addInputPort( "inHigiene" ) ),
    inJuego( addInputPort( "inJuego" ) ),
    inRemedio( addInputPort( "inRemedio" ) ),
    inConsumo( addInputPort( "inConsumo" ) ),
    outAnimo( addOutputPort( "outAnimo" ) ),
    outSalud( addOutputPort( "outSalud" ) ),
    outEnergia( addOutputPort( "outEnergia" ) ),
    outInfo( addOutputPort( "outInfo" ) ),
    tiempoEnfermo( 120, 0, 0, 0 )
{
}


/*******************************************************************
* Nombre de la Función: SistemaSalud::initFunction()
* Descripción: Función de Inicialización
********************************************************************/

Model &SistemaSalud::initFunction()
{
//Variables de estado
  salud     = 8;
  energia   = 5;
  animo     = 8;
//Constantes. podrian ser parametricas pero tienen que estar equilibradas cuidadosamente
  subaNutrientesEnergia =      4;
  bajaHigieneSalud      =      -1;
  subaJuegoAnimo        =      1;
  bajaJuegoEnergia      =      -0.5;
  subaRemedioSalud      =      1;
  bajaRemedioAnimo      =      -1;
  bajaSanoEnergia       =    -6.4;
  umbralSano            =      5;
  return *this ;
}


/*******************************************************************
* Function Name: externalFunction
* Description: Si esta en estado pasivo y entra desecho, comienza a
* procesarlo por un tiempo tiempoActivo. Si esta activo y entra
* limpieza, no emite salida y pasa a estado pasivo
********************************************************************/

Model &SistemaSalud::externalFunction( const ExternalMessage &msg )
{
  VTime timeLeft = msg.time() - lastChange();
  actualizarConsumo(timeLeft);
  if (estadoSS != muerto ){
    if (msg.port() ==inNutrientes){
        energia += subaNutrientesEnergia;
        actualizarSalud();
        actualizarEstado();
    }
    if (msg.port() == inHigiene){
        salud += bajaHigieneSalud;
        actualizarSalud();
        actualizarEstado();
    }
    if (msg.port() == inJuego){
        animo += subaJuegoAnimo;
        energia += bajaJuegoEnergia;
        actualizarSalud();
        actualizarEstado();
    }
    if (msg.port() ==  inRemedio){
        salud += subaRemedioSalud;
        animo += bajaRemedioAnimo;
        actualizarSalud();
        actualizarEstado();
    }
    estadoSS =llegaEvento;
    holdIn(AtomicState::active, 0);
  }//endif de muerto


  return *this;
}

SistemaSalud &SistemaSalud::actualizarConsumo(VTime &timeLeft){
  if (estadoSS == sano){
    float minutos= timeLeft.asMsecs()/60000;//En minutos
    //tenemos 1440 minutos por dias
    float consumoEnergia =bajaSanoEnergia / 1440; //Consumo de energia diario en milliseconds
    energia+=consumoEnergia* minutos; //Tengo la enetgia consumida
  }
  if (estadoSS == enfermo){
    float minutos= timeLeft.asMsecs()/60000; //en minutos
    float consumoSalud  =-1 / (float) 1440; //Consumo de salud diario de un enfermo
    salud+=consumoSalud* minutos ;
  }
  return *this;
}

SistemaSalud &SistemaSalud::actualizarSalud(){
  if(energia >= 10 && animo >= 2){
  //Animo y energia se transforman en salud
    salud += 2;
    energia -= 10;
    animo -= 2;
  }
  else
  if (energia <= 0 && salud > 0 && animo > 0){
    energia += 5;
    salud -= 1;
    animo -= 1;
  }
  //Falta actualizar la salud si esta enfermo..
  return *this;
}

SistemaSalud &SistemaSalud::actualizarEstado(){
  if (salud > umbralSano){
      estadoSS = sano;
      float cantPotEnergia = (salud-umbralSano)* 5 + energia;
      //salud-5 para entrar en estado enfermedad
      float bajaSanoEnergiaMins  =bajaSanoEnergia / 1440 ;
      float minsDeSano = -(cantPotEnergia /bajaSanoEnergiaMins)+1;
      VTime t(0,minsDeSano,0,0);


      holdIn(AtomicState::active, t);
  }
  //Si el animo es 0 se muere.. Energia 0 solo ocurre cuando no tiene salud y animo
  else if(salud >= 0 && energia >= 0 && animo > 0 ){
     estadoSS = enfermo ;
     holdIn(AtomicState::active, VTime(salud * 24,00,00,00));
  }
  else
    estadoSS = muerto;

  return *this;
}



/*******************************************************************
* Function Name: internalFunction
* Description: Esta funcion se ejecuta cuando termina de procesar el
* desecho y pasa a estado pasivo
********************************************************************/
Model &SistemaSalud::internalFunction( const InternalMessage & msg)
{

  if (estadoSS==llegaEvento){
    actualizarEstado();
  }
  else{
    if (estadoSS== sano){
  //Si paso el holdIn esta enfermo
      salud =umbralSano;
      energia=0;
      actualizarEstado();
    }
    else if (estadoSS== enfermo){
  //Si termino y estaba enfermo, esta muerto
         salud = 0;
         estadoSS = muerto;
         passivate();
    }
  }
  return *this ;
}


/*******************************************************************
* Function Name: outputFunction
* Description: Solo se emite salida si termina de procesar el desecho
* y no entro limpieza en ese tiempo
********************************************************************/
Model &SistemaSalud::outputFunction( const CollectMessage &msg )
{
  sendOutput( msg.time(), outSalud, salud ) ;
  sendOutput( msg.time(), outEnergia, energia ) ;
  sendOutput( msg.time(), outAnimo, animo ) ;
  return *this ;
}



Model &SistemaSalud::outputDebug( float m)
{
  cout <<"debug: "<< m<<endl;
  return *this;
}

