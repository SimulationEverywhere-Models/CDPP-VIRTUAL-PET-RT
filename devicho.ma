[top]
components : ss@SistemaSalud se@SistemaExcretor sj@SistemaJuego sd@SistemaDigestivo
Out : outInfo outSalud outEnergia outAnimo outDesecho
in: inComida inJuego inRemedio inLimpieza
Link : inComida       inComida@sd
Link : inJuego        inJuego@sj
Link : inRemedio      inRemedio@ss

Link : inLimpieza            inLimpieza@se
Link : outNutrientes@sd      inNutrientes@ss
Link : outDesecho@sd         inDesecho@se

Link : outDesecho@sd         outDesecho
Link : outHigiene@se         inHigiene@ss


Link : outJuego@sj           inJuego@ss


Link : outSalud@ss           outSalud
Link : outEnergia@ss         outEnergia
Link : outAnimo@ss           outAnimo

Link : outInfo@sd            outInfo
Link : outInfo@se            outInfo
Link : outInfo@sj            outInfo




[ss]

[se]

[sd]

[sj]


