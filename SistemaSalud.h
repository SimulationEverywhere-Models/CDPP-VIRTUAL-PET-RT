/*******************************************************************
*
*  DESCRIPTION: Atomic Model Sistema Salud
*
*  AUTHOR: Grupo2- II02 Baranek, Riccillo
*
*  EMAIL: mailto: abaranek@dc.uba.ar
*         mailto: mr9o@dc.uba.ar
*
*  DATE: 25/9/2002
*
*******************************************************************/
#ifndef __SistemaSalud_H
#define __SistemaSalud_H

#ifndef DEVS_DEVICHO
  #define DEVS_DEVICHO
#endif

#include <list.h>
#include "atomic.h"       // class Atomic
#include "atomicstate.h"  //
#include "VTime.hh"

//#include "codigos.h" // Codigos de mensajes de info


class SistemaSalud : public Atomic
{
public:
  SistemaSalud( const string &name = "SistemaSalud" );
  virtual string className() const {  return "SistemaSalud" ;}
protected:
  Model &initFunction();
  Model &externalFunction( const ExternalMessage & );
  Model &internalFunction( const InternalMessage & );
  Model &outputFunction( const CollectMessage & );
  Model &outputDebug( float m);

private:
  const Port &inNutrientes;
  const Port &inHigiene;
  const Port &inJuego;
  const Port &inRemedio;
  const Port &inConsumo;

  Port &outAnimo;
  Port &outSalud;
  Port &outEnergia;
  Port &outInfo;


  VTime tiempoEnfermo,timeLeft, aux;

  SistemaSalud &SistemaSalud::actualizarConsumo(VTime &timeLeft);
  SistemaSalud &actualizarSalud();
  SistemaSalud &actualizarEstado();

  enum estado {sano, enfermo, muerto, llegaEvento } estadoSS;
  float salud, energia, animo;
//Variables de umbrales:
  float subaNutrientesEnergia;
  float bajaHigieneSalud;
  float subaJuegoAnimo;
  float bajaJuegoEnergia;
  float subaRemedioSalud;
  float bajaRemedioAnimo;
  float bajaSanoEnergia; //por dia
  float umbralSano;
};  // class SistemaSalud

#endif   //__SistemaSalud_H
