/*
 * lab6.h
 *
 *  Created on: Dec 8, 2014
 *      Author: C16Justin.Niquette
 */

#ifndef LAB6_H_
#define LAB6_H_

unsigned int getRunningAverage(unsigned int a[]);

//http://stackoverflow.com/questions/400951/does-c-have-a-foreach-loop-construct
#define foreach(item, array) \
    for(int keep = 1, \
            count = 0,\
            size = sizeof (array) / sizeof *(array); \
        keep && count != size; \
        keep = !keep, count++) \
      for(item = (array) + count; keep; keep = !keep)




#endif /* LAB6_H_ */
