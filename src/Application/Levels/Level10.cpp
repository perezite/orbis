#include "Level10.h"

#include "LevelUtil.h"
#include "Level9.h"

#include "../../Orbis/Orbis.h"
using namespace orb::components;
using namespace orb::video;

namespace levels
{
	void Level10::start()
	{
		// init textures
		Texture* greenParticleTex = VideoManager::getInstance()->getTexture("Textures/GreenParticle.png");

		// init camera
		Entity* cam = new Entity();
		cam->addComponent(new Camera());
		addEntity(cam);

		// add level switchers
		LevelUtil::AddLevelSwitcher<Level9>(this, false);

		// init entities
		Entity* particles = new Entity("Particles");
		particles->addComponent(new SimpleParticleRenderer(greenParticleTex));
		this->addEntity(particles);
	}
}
