//
//  date_time.h
//  E01
//
//  Created by Andrea Pellegrino on 11/01/21.
//

#ifndef date_time_h
#define date_time_h

#include <stdio.h>

typedef struct time{
    
    int hour;
    int minute;

}time;

typedef struct date{
    
    int year;
    int month;
    int day;
    time time;
    
}date;


#endif /* date_time_h */

