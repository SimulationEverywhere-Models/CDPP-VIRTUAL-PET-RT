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
#include "SistemaJuego.h"
#include "message.h"
#include "parsimu.h"

/*******************************************************************
* CLASS SistemaJuego
*********************************************************************/

/*******************************************************************
* Nombre de la Funcion: SistemaJuego::SistemaJuego()
* Descripción: Constructor
********************************************************************/
SistemaJuego::SistemaJuego( const string &name ) :
    Atomic( name ),
    inJuego( addInputPort( "inJuego" ) ),
    outJuego( addOutputPort( "outJuego" ) ),
    outInfo( addOutputPort( "outInfo" ) ),

    tiempoJugar( 3, 0, 0, 0 )
{
}


/*******************************************************************
* Nombre de la Funcion: SistemaJuego::initFunction()
* Descripcion: Funcion de Inicializacion
********************************************************************/

Model &SistemaJuego::initFunction()
{
  passivate();
  return *this ;
}


/*******************************************************************
* Function Name: externalFunction
* Description: Si entra Juego pasa a estado activo por un tiempo
* tiempoJugar
********************************************************************/

Model &SistemaJuego::externalFunction( const ExternalMessage &msg )
{
  if( msg.port() == inJuego )
  {
    if( state() == AtomicState::passive && msg.value() )
    {
      holdIn(AtomicState::active, tiempoJugar);
    }
    else
    {
      timeLeft = msg.time() - lastChange();
      aux = tiempoJugar - timeLeft;
      holdIn(AtomicState::active, aux);
    }
  }
  return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: Cuando termina de jugar pasa a estado pasivo y emite
* juego
********************************************************************/
Model &SistemaJuego::internalFunction( const InternalMessage & )
{
  passivate();
  return *this ;
}


/*******************************************************************
* Function Name: outputFunction
* Description: Cuando termina de jugar pasa a estado pasivo y emite
* juego
********************************************************************/
Model &SistemaJuego::outputFunction( const CollectMessage &msg )
{
  sendOutput( msg.time(), outJuego, 1 ) ;
  return *this ;
}

