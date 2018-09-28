#include "Level10.h"

#include "LevelUtil.h"
#include "Level9.h"

#include "../../Orbis/Orbis.h"
using namespace orb;

namespace app
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
		LevelUtil::addLevelSwitcher<Level9>(false);

		// init entities
		Entity* particles = new Entity("Particles");
		particles->addComponent(new SimpleParticleRenderer(greenParticleTex));
		this->addEntity(particles);
	}
}
