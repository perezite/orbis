#include "Level10.h"

#include "LevelHelper.h"
#include "Level9.h"

#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Components/SimpleParticleRenderer.h"
#include "../../Orbis/Video/VideoManager.h"
using namespace orbis::components;
using namespace video;

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
		LevelHelper::AddLevelSwitcher<Level9>(this, false);

		// init entities
		Entity* particles = new Entity("Particles");
		particles->addComponent(new SimpleParticleRenderer(greenParticleTex));
		this->addEntity(particles);
	}
}
