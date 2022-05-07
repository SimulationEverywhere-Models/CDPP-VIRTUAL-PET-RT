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
#ifndef __SistemaJuego_H
#define __SistemaJuego_H

#ifndef DEVS_DEVICHO
  #define DEVS_DEVICHO
#endif

#include <list.h>
#include "atomic.h"       // class Atomic
#include "atomicstate.h"  //
#include "VTime.hh"


class SistemaJuego : public Atomic
{
public:
  SistemaJuego( const string &name = "SistemaJuego" );
  virtual string className() const {  return "SistemaJuego" ;}
protected:
  Model &initFunction();
  Model &externalFunction( const ExternalMessage & );
  Model &internalFunction( const InternalMessage & );
  Model &outputFunction( const CollectMessage & );

private:
  const Port &inJuego;
  Port &outJuego;
  Port &outInfo;
  VTime tiempoJugar, timeLeft, aux;


};  // class SistemaJuego

#endif   //__SistemaJuego_H
