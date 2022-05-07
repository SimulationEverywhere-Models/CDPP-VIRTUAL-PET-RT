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
#include "SistemaDigestivo.h"
#include "message.h"
#include "parsimu.h"


/*******************************************************************
* CLASS SistemaDigestivo
*********************************************************************/

/*******************************************************************
* Nombre de la Funcion: SistemaDigestivo::SistemaDigestivo()
* Descripción: Constructor
********************************************************************/
SistemaDigestivo::SistemaDigestivo( const string &name ) :
    Atomic( name ),
    inComida( addInputPort( "inComida" ) ),
    outNutrientes( addOutputPort( "outNutrientes" ) ),
    outDesecho( addOutputPort( "outDesecho" ) ),
    outInfo( addOutputPort( "outInfo" ) ),

    tiempoDigerir( 2, 0, 0, 0 )
{
}


/*******************************************************************
* Nombre de la Funcion: SistemaDigestivo::initFunction()
* Descripcion: Funcion de Inicializacion
********************************************************************/

Model &SistemaDigestivo::initFunction()
{
  return *this ;
}


/*******************************************************************
* Function Name: externalFunction
* Description: Si entra Comida pasa a estado activo por un tiempo
* tiempoDigerir
********************************************************************/

Model &SistemaDigestivo::externalFunction( const ExternalMessage &msg )
{
  if( msg.port() == inComida )
  {
      holdIn(AtomicState::active, tiempoDigerir);
      //Siempre que llega comida, vuelve a empezar
  }
  return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: Cuando termina de digerir pasa a estado pasivo y emite
* nutrientes y desechos
********************************************************************/
Model &SistemaDigestivo::internalFunction( const InternalMessage & )
{
  passivate();
  return *this ;
}


/*******************************************************************
* Function Name: outputFunction
* Description: Cuando termina de digerir pasa a estado pasivo y emite
* nutrientes y desechos
********************************************************************/
Model &SistemaDigestivo::outputFunction( const CollectMessage &msg )
{
  sendOutput( msg.time(), outNutrientes, 1 ) ;
  sendOutput( msg.time(), outDesecho, 1 ) ;
  return *this ;
}

