/* 
 * File:   stringUtil.h
 * Author: hq4ever
 *
 * Created on March 13, 2010, 6:34 PM
 */

#ifndef _STRINGUTIL_H
#define	_STRINGUTIL_H

/* Create new char array at the size of toPos-fromPos+1 and copy content from source to this array */
char* substr(const char* source, const unsigned int fromPos, const unsigned int toPos);

#endif	/* _STRINGUTIL_H */

