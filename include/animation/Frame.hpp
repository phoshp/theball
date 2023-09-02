//
// Created by Fatih on 28.04.2022.
//

#ifndef THEBALL_FRAME_HPP
#define THEBALL_FRAME_HPP

#include <SFML/Graphics.hpp>

namespace ph {

template<class T>
class Frame {
public:
	float m_duration = 0.0; // in seconds

	virtual void start(T& target) = 0;

	virtual void update(T& target, float mul) = 0;

	virtual void finish(T& target) = 0;

};

} // ph

#endif //THEBALL_FRAME_HPP
