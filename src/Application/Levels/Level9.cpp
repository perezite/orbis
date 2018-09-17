#include "Level9.h"

#include "LevelUtil.h"
#include "Level8.h"
#include "Level10.h"

#include "../../Orbis/Orbis.h"
using namespace orb::components;
using namespace orb::video;

namespace levels
{
	void Level9::start()
	{
		// init textures
		Texture* yellowBlockTex = VideoManager::getInstance()->getTexture("Textures/YellowBlock.png");
		Texture* redBlockTex = VideoManager::getInstance()->getTexture("Textures/RedBlock.png");
		Texture* greenParticleTex = VideoManager::getInstance()->getTexture("Textures/GreenParticle.png");

		// init camera
		Entity* cam = new Entity();
		cam->addComponent(new Camera());
		addEntity(cam);

		// add level switchers
		LevelUtil::AddLevelSwitcher<Level8>(this, false);
		LevelUtil::AddLevelSwitcher<Level10>(this, true);

		// init entities
		Entity* yellowBlock = new Entity("Yellow Brick");
		yellowBlock->addComponent(new SpriteRenderer(yellowBlockTex));
		yellowBlock->setTransform(Transform(Vector2D(-0.25f, 0.3f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->addEntity(yellowBlock);

		Entity* yellowBlock2 = new Entity("Yellow Brick 2");
		yellowBlock2->addComponent(new SpriteRenderer(yellowBlockTex));
		yellowBlock2->setTransform(Transform(Vector2D(0.25f, 0.3f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->addEntity(yellowBlock2);

		Entity* redBlock = new Entity("Red Brick");
		redBlock->addComponent(new SpriteRenderer(redBlockTex));
		redBlock->setTransform(Transform(Vector2D(0.0f, 0.0f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->addEntity(redBlock);

		Entity* particles = new Entity("Particles");
		particles->addComponent(new ParticleRenderer(greenParticleTex));
		particles->setTransform(Transform(Vector2D(0.0f, -0.3f), 0.0f, Vector2D(0.1f, 0.1f)));
		this->addEntity(particles);
	}
}
