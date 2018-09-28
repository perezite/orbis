#include "LevelBuilder.h"

namespace orb
{
	LevelBuilder::LevelBuilder()
	{
		reset();
	}

	LevelBuilder* LevelBuilder::entity(std::string id)
	{
		m_entity = new Entity(id);
		return this;
	}

	LevelBuilder* LevelBuilder::withComponent(Component* component)
	{
		m_components.push_back(component);
		return this;
	}

	LevelBuilder* LevelBuilder::withPosition(float x, float y)
	{
		m_transform.position = Vector2D(x, y);
		return this;
	}

	LevelBuilder* LevelBuilder::withRotation(float alpha)
	{
		m_transform.rotation = alpha;
		return this;
	}

	LevelBuilder* LevelBuilder::withScale(float w, float h)
	{
		m_transform.scale = Vector2D(w, h);
		return this;
	}

	LevelBuilder* LevelBuilder::withTransformSpace(TransformSpace space)
	{
		m_transform.transformSpace = space;
		return this;
	}

	LevelBuilder* LevelBuilder::withTransform(float x, float y, float alpha, float w, float h)
	{
		this->withPosition(x, y)->withRotation(alpha)->withScale(w, h);
		return this;
	}

	LevelBuilder* LevelBuilder::withTransform(Transform transform)
	{
		m_transform = transform;
		return this;
	}

	void LevelBuilder::go()
	{
		for (unsigned int i = 0; i < m_components.size(); i++)
			m_entity->addComponent(m_components[i]);

		m_entity->setTransform(m_transform);

		m_level->addEntity(m_entity);

		reset();
	}

	void LevelBuilder::reset()
	{
		m_entity = NULL;
		m_transform = Transform(Vector2D(0.0f, 0.0f), 0.0f, Vector2D(1.0f, 1.0f), TransformSpace::World);
		m_components.clear();
	}
}
