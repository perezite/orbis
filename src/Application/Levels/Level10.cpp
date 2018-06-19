#include "Level10.h"

#include "LevelHelper.h"
#include "Level9.h"

#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Components/SimpleParticleRenderer.h"
#include "../../Orbis/Video/VideoManager.h"
using namespace Components;
using namespace Video;

namespace Levels
{
	void Level10::start()
	{
		// init textures
		Texture* greenParticleTex = VideoManager::getInstance()->getTexture("Textures/GreenParticle.png");

		// init camera
		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

		// add level switchers
		LevelHelper::AddLevelSwitcher<Level9>(this, false);

		// init entities
		Entity* particles = new Entity("Particles");
		particles->AddComponent(new SimpleParticleRenderer(greenParticleTex));
		this->AddEntity(particles);
	}
}
