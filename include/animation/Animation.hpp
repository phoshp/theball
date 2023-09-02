//
// Created by emrey on 22.04.2022.
//

#ifndef THEBALL_ANIMATION_HPP
#define THEBALL_ANIMATION_HPP

#include <SFML/Graphics.hpp>
#include "animation/Frame.hpp"
#include <cmath>

namespace ph {

template<class T>
class Animation {
public:

	explicit Animation(bool loop) : m_loop(loop) {}

	Animation(std::initializer_list<Frame<T>*> frames, bool loop = false) : m_loop(loop) {
		for (auto& frame: frames) {
			addFrame(frame);
		}
	}

	virtual ~Animation() {
		for (int i = 0; i < m_frames.size(); ++i) {
			delete m_frames[i];
		}
		m_frames.clear();
	}

	void addFrame(Frame<T>* frame) {
		m_frames.push_back(frame);
	}

	void update(T& target, float elapsed) {
		if (m_frames.size() > m_current) {
			Frame<T>* frame = m_frames[m_current];
			if (m_progress == 0.0) {
				frame->start(target);
			}

			m_progress += elapsed;
			frame->update(target, std::min(1.f, m_progress / frame->m_duration));
			if (m_progress >= frame->m_duration) {
				m_progress = 0.0;
				m_current++;
				frame->finish(target);
			}
		}

		if (m_loop && m_current == m_frames.size()) {
			m_progress = 0.0;
			m_current = 0;
		}
	}

	void reset() {
		m_progress = 0.0;
		m_current = 0;
	}

private:
	std::vector<Frame<T>*> m_frames;
	float m_progress = 0.0;
	int m_current = 0;
	bool m_loop = false;
};

} // ph

#endif //THEBALL_ANIMATION_HPP