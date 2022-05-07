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
#ifndef __SistemaDigestivo_H
#define __SistemaDigestivo_H

#ifndef DEVS_DEVICHO
  #define DEVS_DEVICHO
#endif

#include <list.h>
#include "atomic.h"       // class Atomic
#include "atomicstate.h"  //
#include "VTime.hh"



class SistemaDigestivo : public Atomic
{
public:
  SistemaDigestivo( const string &name = "SistemaDigestivo" );
  virtual string className() const {  return "SistemaDigestivo" ;}
protected:
  Model &initFunction();
  Model &externalFunction( const ExternalMessage & );
  Model &internalFunction( const InternalMessage & );
  Model &outputFunction( const CollectMessage & );

private:
  const Port &inComida;
  Port &outNutrientes;
  Port &outDesecho;
  Port &outInfo;


  VTime tiempoDigerir, timeLeft, aux;


};  // class SistemaDigestivo

#endif   //__SistemaDigestivo_H
