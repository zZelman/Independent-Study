/*
 * IUpdatable.h
 *
 *  Created on: Oct 10, 2013
 *      Author: zZelman
 */

#ifndef IUPDATABLE_H_
#define IUPDATABLE_H_

// this interface makes implementing classes be able to be cast into an updatable list
class IUpdateable
{
public:
	IUpdateable();
	virtual ~IUpdateable();

	virtual void update() = 0;

};


#endif /* IUPDATABLE_H_ */
