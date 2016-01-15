#include "stdafx.h"
#include <SFML/Graphics.hpp>

#pragma once

struct Particle
{
	sf::Vector2f velocity;
	sf::Time lifetime;
};

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
	ParticleSystem(unsigned int count);
	void setEmitter(sf::Vector2f position);
	void setStuff(int total);
	virtual void update(sf::Time elapsed);
	void setAttractor(sf::Vector2f attr);

protected:
	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	sf::Time m_lifetime;
	sf::Vector2f m_emitter;
	sf::Vector2f attractor;
	int stuff;

	void resetParticle(std::size_t index, int offset);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class TriParticleSystem : public ParticleSystem {
	public:
		TriParticleSystem(unsigned int count);
		virtual void update(sf::Time elapsed);
		virtual void resetParticle(std::size_t index, int offset);
};

class OrangeParticleSystem : public ParticleSystem {
public:
	OrangeParticleSystem(unsigned int count);
	virtual void update(sf::Time elapsed);
	virtual void resetParticle(std::size_t index, int offset);
};