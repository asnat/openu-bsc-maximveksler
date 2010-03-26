/* 
 * File:   CodeSegmentMgr.h
 * Author: hq4ever
 *
 * Created on February 27, 2010, 11:03 PM
 */

#ifndef _CODESEGMENTMGR_H
#define	_CODESEGMENTMGR_H

void resetCode();
unsigned int getIC();
unsigned short storeCode(unsigned short data);
unsigned short* getCode();

#endif	/* _CODESEGMENTMGR_H */

