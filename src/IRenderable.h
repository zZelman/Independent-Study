/*
 * IRenderable.h
 *
 *  Created on: Oct 10, 2013
 *      Author: zZelman
 */

#ifndef IRENDERABLE_H_
#define IRENDERABLE_H_


class IRenderable
{
public:
	IRenderable();
	virtual ~IRenderable();

	virtual void render() = 0;

};


#endif /* IRENDERABLE_H_ */
