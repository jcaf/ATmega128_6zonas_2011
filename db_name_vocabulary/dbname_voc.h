/*
 * dbname_voc.h
 *
 * Created: 11/28/2012 8:02:05 PM
 *  Author: jc
 */ 


#ifndef DBNAME_VOC_H_
#define DBNAME_VOC_H_

//#include <avr/pgmspace.h>

#define _MAX_LENGTH_CADS_COMMON_	(11)	//COMMUN PARA TODOS
//
#define _MAX_LENGTH_NOM_ESCENAS_	(_MAX_LENGTH_CADS_COMMON_)
//
#define _MAX_LENGTH_AMBIENTE_CASA_	(_MAX_LENGTH_CADS_COMMON_)
#define _MAX_LENGTH_POSICION_REF_	(_MAX_LENGTH_CADS_COMMON_)
#define _MAX_LENGTH_TIPO_LUMINARIA_ (_MAX_LENGTH_CADS_COMMON_)
#define _MAX_LENGTH_OTROS_EN_CASA_	(_MAX_LENGTH_CADS_COMMON_)

#define V_NAMES_FOR_SCENES {\
"Todos 0%",\
"Todos 25%",\
"Todos 50%",\
"Todos 75%",\
"Todo 100%",\
"Luz Paso",\
"LuzDiario",\
"LuzNoche",\
"LuzTarde",\
"LuzVisita",\
"Luz Cena",\
"Mix 1",\
"Mix 2",\
"Mix 3",\
"Mix 4",\
"Mix 5",\
"Mix 6",\
"Mix 7",\
"Mix 8",\
"Mix 9",\
"Reunion",\
"Recepcion",\
"Juego",\
"Lectura",\
"Calido",\
"Confort",\
"Fiesta",\
"Frio",\
"Intermedio",\
"Natural",\
"Neutro",\
"Sutil",\
"Decorativo",\
"Agradable",\
"Velada",\
"L.Entrada",\
"Emergencia"\
}

#define V_PLACES_OF_HOUSE {\
"-VACIO-",\
"Alero",\
"Aseo",\
"Balcon",\
"Bar",\
"Bodega",\
"Cerco",\
"Cesped",\
"Cochera",\
"Cocina",\
"Comedor",\
"CuartoServ",\
"Despacho",\
"Despensa",\
"Desvan",\
"Dormitorio",\
"Entr.Auto",\
"Entrada",\
"Escalera",\
"Estudio",\
"Habitacion",\
"Hall",\
"Jardin",\
"Lavadero",\
"Lobby",\
"Pared",\
"Pasadiso",\
"Pasillo",\
"Patio",\
"Pileta",\
"Piscina",\
"Piso",\
"Planta",\
"Portico",\
"Puerta",\
"Sala",\
"Salon",\
"Servicios",\
"Sotano",\
"Techo",\
"Terraza",\
"Ventana",\
"Vestibulo",\
}

#define V_TYPES_OF_LUMINARY {\
"-VACIO-",\
"ampolla",\
"apantallad",\
"balastro",\
"braquete",\
"bombilla",\
"candelabro",\
"colgante",\
"cristal",\
"cubo",\
"dicroico",\
"difusor",\
"esferico",\
"estaca",\
"faro",\
"fluo frio",\
"fluoBlanco",\
"fluoresc.",\
"foco",\
"foco Ahorr",\
"halogeno",\
"halospot",\
"hornacina",\
"incandesc.",\
"induccion",\
"l.colgante",\
"lamp.mesa",\
"lamp.techo",\
"lamp.pie",\
"lampara",\
"LED",\
"Luz",\
"luzDirect",\
"luzIndirec",\
"mercurio",\
"RGB",\
"nicho",\
"parabolico",\
"plafon",\
"poste",\
"reflector",\
"sodio",\
"spotlight",\
"telescopic",\
"tira",\
}

#define V_POSITION_OR_REFERENCE {\
"-VACIO-",\
"abajo",\
"alto(a)",\
"anterior",\
"arriba",\
"bajo(a)",\
"centro",\
"costado",\
"cruzado",\
"delantera",\
"derecho(a)",\
"diagonal",\
"este",\
"emb.pared",\
"emb.piso",\
"extremo",\
"frente",\
"fondo",\
"izquierdo",\
"int.1",\
"int.2",\
"int.3",\
"int.4",\
"int.5",\
"int.6",\
"int.7",\
"int.8",\
"int.9",\
"lateral",\
"mitad",\
"noreste",\
"noroeste",\
"norte",\
"oeste",\
"posterior",\
"piso",\
"sector 1",\
"sector 2",\
"sector 3",\
"sur",\
"sureste",\
"suroeste",\
"techo",\
"trasero(a)",\
}

#define V_OTHERS_ABOUT_OF_HOUSE {\
"-VACIO-",\
"antena",\
"bienvenida",\
"chimenea",\
"cielorraso",\
"cobertizo",\
"computer",\
"doble",\
"ingreso",\
"pantalla",\
"persiana",\
"salida",\
"seto",\
"sol-sombra",\
"tector",\
"tabiqueria",\
"terreno",\
"timbre",\
"tragaluz",\
"1",\
"2",\
"3",\
"4",\
"5",\
"6",\
"7",\
"8",\
"9",\
"10",\
}

//
extern const char v_names_for_scenes[][_MAX_LENGTH_NOM_ESCENAS_];// PROGMEM;

extern const char v_places_of_house[][_MAX_LENGTH_AMBIENTE_CASA_];//PROGMEM;
extern const char v_types_of_luminary[][_MAX_LENGTH_TIPO_LUMINARIA_];// PROGMEM;
extern const char v_position_or_reference[][_MAX_LENGTH_POSICION_REF_];// PROGMEM;
extern const char v_others_about_of_house[][_MAX_LENGTH_OTROS_EN_CASA_];// PROGMEM;


#define LENGTH__V_NAMES_FOR_SCENES (sizeof( (const char [][_MAX_LENGTH_AMBIENTE_CASA_])V_NAMES_FOR_SCENES ) / sizeof( (const char [][_MAX_LENGTH_AMBIENTE_CASA_])V_NAMES_FOR_SCENES[0] ) )
#define LENGTH__V_PLACES_OF_HOUSE (sizeof( (const char [][_MAX_LENGTH_AMBIENTE_CASA_])V_PLACES_OF_HOUSE ) / sizeof( (const char [][_MAX_LENGTH_AMBIENTE_CASA_])V_PLACES_OF_HOUSE[0] ) )
#define LENGTH__V_TYPES_OF_LUMINARY (sizeof( (const char [][_MAX_LENGTH_TIPO_LUMINARIA_])V_TYPES_OF_LUMINARY ) / sizeof( (const char [][_MAX_LENGTH_TIPO_LUMINARIA_])V_TYPES_OF_LUMINARY[0] ) )
#define LENGTH__V_POSITION_OR_REFERENCE (sizeof( (const char [][_MAX_LENGTH_POSICION_REF_])V_POSITION_OR_REFERENCE ) / sizeof( (const char [][_MAX_LENGTH_POSICION_REF_])V_POSITION_OR_REFERENCE[0] ) )
#define LENGTH__V_OTHERS_ABOUT_OF_HOUSE (sizeof( (const char [][_MAX_LENGTH_OTROS_EN_CASA_])V_OTHERS_ABOUT_OF_HOUSE ) / sizeof( (const char [][_MAX_LENGTH_OTROS_EN_CASA_])V_OTHERS_ABOUT_OF_HOUSE[0] ) )

//unsigned int length__v_names_for_scenes(void);//Otra solucion para obtener sizeof x otros modulos externos
////unsigned int length__v_names_for_scenes(void){return sizeof(v_names_for_scenes)/sizeof(v_names_for_scenes[0]);}


#endif /* DBNAME_VOC_H_ */