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
#include "SistemaExcretor.h"
#include "message.h"
#include "parsimu.h"

/*******************************************************************
* CLASS SistemaExcretor
*********************************************************************/

/*******************************************************************
* Nombre de la Funci¢n: SistemaExcretor::SistemaExcretor()
* Descripción: Constructor
********************************************************************/
SistemaExcretor::SistemaExcretor( const string &name ) :
    Atomic( name ),
    inDesecho( addInputPort( "inDesecho" ) ),
    inLimpieza( addInputPort( "inLimpieza" ) ),
    outHigiene( addOutputPort( "outHigiene" ) ),
    outInfo( addOutputPort( "outInfo" ) ),
    tiempoActivo( 5, 0, 0, 0 )
{
}


/*******************************************************************
* Nombre de la Función: SistemaExcretor::initFunction()
* Descripción: Función de Inicialización
********************************************************************/

Model &SistemaExcretor::initFunction()
{
  return *this ;
}


/*******************************************************************
* Function Name: externalFunction
* Description: Si esta en estado pasivo y entra desecho, comienza a
* procesarlo por un tiempo tiempoActivo. Si esta activo y entra
* limpieza, no emite salida y pasa a estado pasivo
********************************************************************/

Model &SistemaExcretor::externalFunction( const ExternalMessage &msg )
{
  if( msg.port() == inDesecho )
  {
    if( state() == AtomicState::passive && msg.value() )
    {
      holdIn(AtomicState::active, tiempoActivo);
    }
    else
    {
      timeLeft = msg.time() - lastChange();
      aux = tiempoActivo - timeLeft;
      holdIn(AtomicState::active, aux);
    }
  }

  if( msg.port() == inLimpieza )
  {
    passivate();
  }

  return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: Esta funcion se ejecuta cuando no se higeniza a tiempo
*
********************************************************************/
Model &SistemaExcretor::internalFunction( const InternalMessage & )
{
  passivate();
  return *this ;
}


/*******************************************************************
* Function Name: outputFunction
* Description: Solo se emite salida si el desecho no es limpiado rapidamente
*
********************************************************************/
Model &SistemaExcretor::outputFunction( const CollectMessage &msg )
{
  sendOutput( msg.time(), outHigiene, 1 ) ;
  return *this ;
}

