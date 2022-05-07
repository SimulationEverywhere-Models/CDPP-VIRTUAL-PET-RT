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
#ifndef __SistemaExcretor_H
#define __SistemaExcretor_H

#ifndef DEVS_DEVICHO
  #define DEVS_DEVICHO
#endif

#include <list.h>
#include "atomic.h"       // class Atomic
#include "atomicstate.h"  //
#include "VTime.hh"



class SistemaExcretor : public Atomic
{
public:
  SistemaExcretor( const string &name = "SistemaExcretor" );
  virtual string className() const {  return "SistemaExcretor" ;}
protected:
  Model &initFunction();
  Model &externalFunction( const ExternalMessage & );
  Model &internalFunction( const InternalMessage & );
  Model &outputFunction( const CollectMessage & );

private:
  const Port &inDesecho;
  const Port &inLimpieza;
  Port &outHigiene;
  Port &outInfo;
  VTime tiempoActivo, timeLeft, aux;


};  // class SistemaExcretor

#endif   //__SistemaExcretor_H
