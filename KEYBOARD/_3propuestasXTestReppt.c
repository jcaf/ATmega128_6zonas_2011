//===============================================
//===============================================
/*
1 PROPUESTA.-

EXAGERANDO:
Si suelta, y si no se comprueba que se leyo en la primera vez, se habra perdido practicamente esa pulsacion,
si viene otra pulsacion rapidamente, pueda ser que recien en ese momento lo lea..

Esto podria acarrear problemas, si por otro lado del sistema (hardware/firmware), por cada pulsacion avanzará un
estado alguna maquina en curso(contador, temporizador, etc)...

Esto podria provocar una desincronización, ejm:

1 PULSACION -> HI-LEVEL 1 FIRMWARE/HARDWARE AVANZA
            -> HI-LEVEL 2 FIRMWARE/HARDWARE NO AVANZA
*/

//Se produjo pulsacion-> PopulateBit()//first
void from_interr(byte * p...)
{
    if (SOLTO)  //En todo momento se comprueba si SOLTO, para luego abortar y resetear maquina de estados
    {
        Abortar-> Reset state machines
    }
    //..................................
    if (sm == 0)
    {
        if (Cont > K_TRIGGER)   //si supera el primer tiempo. avanza
        {
            sm++;
        }
    }
    else if (sm == 1)
    {
        if (leyo desde hi-level)//Para este punto, se espera a que ya se haya leido desde hi-level, sino, esperar
        {
            sm++;               //Ya leyo, entonces, populate de nuevo
            PopulateBit<<1;     //Re-again
        }
    }
    else if (sm == 2)
    {
        if (Cont > K_REPTT)
        {
            PopulateBit<<1; //Re-again
        }
    }
}
//===============================================
//===============================================
//2 PROPUESTA.-

//Se produjo pulsacion-> PopulateBit()//first


    if (sm == 0)
    {
        if (++cont > K_TRIGGER)
        {
            sm++;
        }
        //
        if (SOLTO)
        {
            sm = _ESPERAR_POR_LECTURA_HILEVEL_;
        }
        //
    }
    else if (sm == 1)
    {
        if (leyo)
        {
            sm++;
            PopulateBit<<1; //Re-again
        }
    }
    else if (sm == 2)
    {
        if (++Cont > K_REPTT)
        {
            PopulateBit<<1; //Re-again
        }
        //
        if (SOLTO)
        {
            sm = _ESPERAR_POR_LECTURA_HILEVEL_;
        }
        //
    }

    if (sm == _ESPERAR_POR_LECTURA_HILEVEL_)
    {
        if (leyo)
        {
            //RESET TODO MAQUINA DE ESTADOS
        }
    }

//===============================================
//===============================================
/*
3 PROPUESTA.- CONSISTENCIANDO SIGUIENDO LA LOGICA..

    Por cada key Popularizado EXISTE la espera a que key sea LEIDO DESDE HI-LEVEL

*/
//Se produjo pulsacion-> PopulateBit()//first
//APUESTO POR ESTE CODIGO...Reprogramando entonces...
    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
    if (SOLTO)
    {
        sm = _ESPERAR_POR_LECTURA_HILEVEL_AND_RESET_ALL_SMACHINES_;
    }
    //////////////////////////////////////////////////////////////////////
    if (sm == 0)
    {
        cont++;

        if (cont > K_TRIGGER)
        {
            sm++;
        }
    }
    else if (sm == 1)   //Ping-pong entre sm==1 y sm==2
    {
        if (leyo)
        {
            sm++;
            PopulateBit<<1; //Re-again
        }
    }
    else if (sm == 2)   //Ping-pong entre sm==1 y sm==2
    {
        if (++Cont > K_REPTT)
        {
            sm--;   //comprueba si leyo,
        }
    }
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    if (sm == _ESPERAR_POR_LECTURA_HILEVEL_AND_RESET_ALL_SMACHINES_)
    {
        if (leyo)
        {
            //RESET TODO MAQUINA DE ESTADOS
        }
    }

