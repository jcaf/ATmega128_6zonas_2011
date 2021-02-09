/* 
 * File:   main.h
 * Author: jcaf
 *
 * Created on February 9, 2021, 12:43 PM
 */

#ifndef MAIN_H
#define	MAIN_H

    //+--Added 2021
    struct _isr_flag
    {
        unsigned f40ms :1;
        unsigned __a :7;
    };

    struct _main_flag
    {
        unsigned f40ms :1;
    };
    
    extern volatile struct _isr_flag isr_flag;
    extern struct _main_flag main_flag;
    
    //--+


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

