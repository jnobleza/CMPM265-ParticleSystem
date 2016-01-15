#include "stdafx.h"
#include "ParticleSystem.h"
#include <SFML/Graphics.hpp>

#define ACC_MULTIPLIER 1
#define QUAD_SIZE 20
#define TRI_SIZE 80

ParticleSystem::ParticleSystem(unsigned int count) :
		m_particles(count),
		m_vertices(sf::Quads, count*4),
		m_lifetime(sf::seconds(3)),
		m_emitter(0, 0)
	{
	}

// some differences for the other particle systems.
TriParticleSystem::TriParticleSystem(unsigned int count) : ParticleSystem(count) {
	// Do things
	m_particles = std::vector<Particle>(count);
	m_vertices = sf::VertexArray(sf::Triangles, count * 3);
}

OrangeParticleSystem::OrangeParticleSystem(unsigned int count) : ParticleSystem(count) {
	m_particles = std::vector<Particle>(count);
	m_vertices = sf::VertexArray(sf::Quads, count * 4);
}

void ParticleSystem::setEmitter(sf::Vector2f position)
{
	m_emitter = position;
}

//sets number for particles that show on screen
void ParticleSystem::setStuff(int total)
{
	stuff = total;
}

//set attractors
void ParticleSystem::setAttractor(sf::Vector2f attr) {
	this->attractor = attr;
}


// updates for particle systems
void TriParticleSystem::update(sf::Time elapsed) {
	for (std::size_t i = 0; i < stuff; i++)
	{
		// update the particle lifetime
		Particle& p = m_particles[i];
		p.lifetime -= elapsed;

		// if the particle is dead, respawn it
		if (p.lifetime <= sf::Time::Zero)
			resetParticle(i,3);

		sf::Vector2f acc = sf::Vector2f(0.0f, 9.8f * ACC_MULTIPLIER);

		//if 
		// new vector that is (.position - attractor), then vector normalization
		// add resulting vector times elapsed.asSeconds to acc

		//float posVec = sqrt((m_vertices[i].position.x * m_vertices[i].position.x) + (m_vertices[i].position.y * m_vertices[i].position.y));
		//float posAtt = sqrt((attractor.position.x * attractor.position.x) + (attractor.position.y * attractor.position.y));

		// attractor
		sf::Vector2f disVec = m_vertices[i].position - attractor;//sf::Vector2f((m_vertices[i].position.x - attractor.x), (m_vertices[i].position.y - attractor.y));
		float length = sqrt((disVec.x * disVec.x) + (disVec.y * disVec.y));
		sf::Vector2f normalizedVector = sf::Vector2f(disVec.x/length, disVec.y/length);
		acc = acc - (normalizedVector * 100.0f);
		

		p.velocity += acc * elapsed.asSeconds();

		sf::Vector2f speed = p.velocity * elapsed.asSeconds();

		// update the position of the corresponding vertex
		int index = i * 3;

		// Make the Four points be at the same location
		m_vertices[index].position += speed;
		m_vertices[index + 1].position = m_vertices[index].position;
		m_vertices[index + 2].position = m_vertices[index].position;

		// Do an offset
		m_vertices[index + 1].position.x = m_vertices[index].position.x + TRI_SIZE;

		m_vertices[index + 2].position.y = m_vertices[index].position.y + TRI_SIZE;
		m_vertices[index + 2].position.x = m_vertices[index].position.x + (TRI_SIZE / 2);

		m_vertices[index].texCoords = sf::Vector2f(0, 0);
		m_vertices[index + 1].texCoords = sf::Vector2f(200, 0);
		m_vertices[index + 2].texCoords = sf::Vector2f(0, 200);

		// update the alpha (transparency) of the particle according to its lifetime
		float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
		m_vertices[index].color.a = static_cast<sf::Uint8>(ratio * 255);
	}

	for (std::size_t i = stuff; i < m_particles.size(); i++)
	{
		// update the particle lifetime
		Particle& p = m_particles[i];
		p.lifetime -= elapsed;

		// if the particle is dead, respawn it
		if (p.lifetime <= sf::Time::Zero)
			resetParticle(i, 3);
	}
}

void ParticleSystem::update(sf::Time elapsed)
{
	//m_particles.size()
	for (std::size_t i = 0; i < stuff; i++)
	{
		// update the particle lifetime
		Particle& p = m_particles[i];
		p.lifetime -= elapsed;

		// if the particle is dead, respawn it
		if (p.lifetime <= sf::Time::Zero)
			resetParticle(i, 4);

		//sf::Vector2f acc = sf::Vector2f(0.0f, 9.8f * ACC_MULTIPLIER);

		// repeller
		sf::Vector2f disVec = m_vertices[i].position - attractor;//sf::Vector2f((m_vertices[i].position.x - attractor.x), (m_vertices[i].position.y - attractor.y));
		float length = sqrt((disVec.x * disVec.x) + (disVec.y * disVec.y));
		sf::Vector2f normalizedVector = sf::Vector2f(disVec.x / length, disVec.y / length);

		sf::Vector2f acc = (normalizedVector * 100.0f);
		p.velocity += acc * elapsed.asSeconds();

		sf::Vector2f speed = p.velocity * elapsed.asSeconds();

		// update the position of the corresponding vertex
		int index = i * 4;

		// Make the Four points be at the same location
		m_vertices[index].position += speed;
		m_vertices[index +1].position = m_vertices[index].position;
		m_vertices[index +2].position = m_vertices[index].position;
		m_vertices[index +3].position = m_vertices[index].position;

		// Do an offset
		m_vertices[index + 1].position.x = m_vertices[index].position.x + QUAD_SIZE;
		m_vertices[index + 2].position.y = m_vertices[index].position.y + QUAD_SIZE;

		m_vertices[index + 3].position.x = m_vertices[index].position.x + QUAD_SIZE;
		m_vertices[index + 3].position.y = m_vertices[index].position.y + QUAD_SIZE;

		m_vertices[index].texCoords = sf::Vector2f(0, 0);
		m_vertices[index +1].texCoords = sf::Vector2f(200, 0);
		m_vertices[index +2].texCoords = sf::Vector2f(0, 200);
		m_vertices[index +3].texCoords = sf::Vector2f(200, 200);

		// update the alpha (transparency) of the particle according to its lifetime
		float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
		m_vertices[index].color.a = static_cast<sf::Uint8>(ratio * 255);
	}

	for (std::size_t i = stuff; i < m_particles.size(); i++)
	{
		// update the particle lifetime
		Particle& p = m_particles[i];
		p.lifetime -= elapsed;

		// if the particle is dead, respawn it
		if (p.lifetime <= sf::Time::Zero)
			resetParticle(i, 4);
	}

}

void OrangeParticleSystem::update(sf::Time elapsed)
{
	//m_particles.size()
	for (std::size_t i = 0; i < stuff; i++)
	{
		// update the particle lifetime
		Particle& p = m_particles[i];
		p.lifetime -= elapsed;

		// if the particle is dead, respawn it
		if (p.lifetime <= sf::Time::Zero)
			resetParticle(i, 4);

		sf::Vector2f acc = sf::Vector2f(0.0f, 9.8f * ACC_MULTIPLIER);

		p.velocity += acc * elapsed.asSeconds();

		sf::Vector2f speed = p.velocity * elapsed.asSeconds();

		// update the position of the corresponding vertex
		int index = i * 4;

		// Make the Four points be at the same location
		m_vertices[index].position += speed;
		m_vertices[index + 1].position = m_vertices[index].position;
		m_vertices[index + 2].position = m_vertices[index].position;
		m_vertices[index + 3].position = m_vertices[index].position;

		// Do an offset
		m_vertices[index + 1].position.x = m_vertices[index].position.x + QUAD_SIZE;
		m_vertices[index + 2].position.y = m_vertices[index].position.y + QUAD_SIZE;

		m_vertices[index + 3].position.x = m_vertices[index].position.x + QUAD_SIZE;
		m_vertices[index + 3].position.y = m_vertices[index].position.y + QUAD_SIZE;

		m_vertices[index].texCoords = sf::Vector2f(0, 0);
		m_vertices[index + 1].texCoords = sf::Vector2f(200, 0);
		m_vertices[index + 2].texCoords = sf::Vector2f(0, 200);
		m_vertices[index + 3].texCoords = sf::Vector2f(200, 200);

		// update the alpha (transparency) of the particle according to its lifetime
		float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
		m_vertices[index].color.a = static_cast<sf::Uint8>(ratio * 255);
	}

	for (std::size_t i = stuff; i < m_particles.size(); i++)
	{
		// update the particle lifetime
		Particle& p = m_particles[i];
		p.lifetime -= elapsed;

		// if the particle is dead, respawn it
		if (p.lifetime <= sf::Time::Zero)
			resetParticle(i, 4);
	}

}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// our particles don't use a texture
	//states.texture = NULL;//tex;

	// draw the vertex array
	target.draw(m_vertices, states);
}



void ParticleSystem::resetParticle(std::size_t index, int offset)
{
	// give a random velocity and lifetime to the particle
	float angle = (std::rand() % 180) * -3.14f / 180.f;
	float speed = (std::rand() % 50) + 50.f;
	float acc = 9.18;
	float dt = 0.01667;
	m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

	// reset the position of the corresponding vertex5
	for (int i = 0; i < offset; i++) {
		m_vertices[index * offset + i].position = m_emitter;
	}
}

void OrangeParticleSystem::resetParticle(std::size_t index, int offset)
{
	// give a random velocity and lifetime to the particle
	float angle = (std::rand() % 90) * -3.14f / 180.f;
	float speed = (std::rand() % 75); //+ 50.f;
	float acc = 9.18;
	float dt = 0.01667;
	m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

	// reset the position of the corresponding vertex5
	for (int i = 0; i < offset; i++) {
		m_vertices[index * offset + i].position = m_emitter;
	}
}

void TriParticleSystem::resetParticle(std::size_t index, int offset)
{
	// give a random velocity and lifetime to the particle
	float angle = (std::rand() % 180) * 3.14f / 180.f;
	float speed = (std::rand() % 50); + 50.f;
	float acc = 9.18;
	float dt = 0.01667;
	m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

	// reset the position of the corresponding vertex
	for (int i = 0; i < offset; i++) {
		m_vertices[index * offset + i].position = m_emitter;
	}
}

