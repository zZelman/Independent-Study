/*
 * IUserInput.h
 *
 *  Created on: Oct 19, 2013
 *      Author: zZelman
 */

#ifndef IUSERINPUT_H_
#define IUSERINPUT_H_

#include "include_sfml.h"

class IUserInput
{
public:
	IUserInput();
	virtual ~IUserInput();

	// "pressed" or "released" is determined by the overarching game structure
	virtual bool userInput_keyPress(sf::Event* pEvent) = 0;
	virtual bool userInput_keyRelease(sf::Event* pEvent) = 0;

	virtual bool userInput_mousePress(sf::Event* pEvent) = 0;
	virtual bool userInput_mouseRelease(sf::Event* pEvent) = 0;
};

#endif /* IUSERINPUT_H_ */
