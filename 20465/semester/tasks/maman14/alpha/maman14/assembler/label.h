/* 
 * File:   label.h
 * Author: doron
 *
 * Created on March 2, 2010, 1:32 PM
 */

#ifndef _LABEL_H
#define	_LABEL_H

#ifndef _ERRORHANDLER_H
#include "errorHandler.h"
#endif

void initLabelTable(void);
errorCode getLabelAddress(char*, unsigned*);
errorCode addLabel(char*, unsigned );

#endif	/* _LABEL_H */

