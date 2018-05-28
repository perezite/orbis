#include "Level9.h"

#include "LevelHelper.h"
#include "Level8.h"
#include "Level10.h"

#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Components/ParticleRenderer.h"
using namespace Components;

namespace Levels
{
	void Level9::Start()
	{
		// init textures
		Texture* yellowBlockTex = new Texture(this, "Textures/YellowBlock.png", true);
		Texture* redBlockTex = new Texture(this, "Textures/RedBlock.png", true);
		Texture* greenParticleTex = new Texture(this, "Textures/GreenParticle.png", true);

		// init camera
		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

		// add level switchers
		LevelHelper::AddLevelSwitcher(this, new Level8(), false);
		LevelHelper::AddLevelSwitcher(this, new Level10(), true);

		// init entities
		Entity* yellowBlock = new Entity("Yellow Brick");
		yellowBlock->AddComponent(new SpriteRenderer(yellowBlockTex));
		yellowBlock->SetTransform(Transform(Vector2D(-0.25f, 0.3f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->AddEntity(yellowBlock);

		Entity* yellowBlock2 = new Entity("Yellow Brick 2");
		yellowBlock2->AddComponent(new SpriteRenderer(yellowBlockTex));
		yellowBlock2->SetTransform(Transform(Vector2D(0.25f, 0.3f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->AddEntity(yellowBlock2);

		Entity* redBlock = new Entity("Red Brick");
		redBlock->AddComponent(new SpriteRenderer(redBlockTex));
		redBlock->SetTransform(Transform(Vector2D(0.0f, 0.0f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->AddEntity(redBlock);

		Entity* particles = new Entity("Particles");
		particles->AddComponent(new ParticleRenderer(this, greenParticleTex));
		particles->SetTransform(Transform(Vector2D(0.0f, -0.3f), 0.0f, Vector2D(0.1f, 0.1f)));
		this->AddEntity(particles);
	}
}
