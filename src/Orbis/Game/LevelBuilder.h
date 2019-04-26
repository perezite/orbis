#pragma once

#include "Level.h"

#include "../Components/Component.h"
#include "../Game/Transform.h"

#include <vector>
#include <string>

namespace orb
{
	class Level;

	// Represents a level in the game
	class LevelBuilder
	{
	public: 
		LevelBuilder();

		void setLevel(Level* level) { m_level = level;  }

		LevelBuilder* entity(std::string id = "");

		LevelBuilder* withComponent(Component * component);

		LevelBuilder* withPosition(float x, float y);

		LevelBuilder* withRotation(float alpha);

		LevelBuilder* withScale(float w, float h);

		LevelBuilder* withTransformSpace(TransformSpace space);

		LevelBuilder* withTransform(float x, float y, float alpha, float w, float h);

		LevelBuilder* withTransform(Transform transform);

		void go();

	protected:
		void reset();

	private: 
		Level* m_level;

		Entity* m_entity;

		Transform m_transform;

		std::vector<Component*> m_components;
	};
}