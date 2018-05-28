#include "Level10.h"

#include "LevelHelper.h"
#include "Level9.h"

#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Components/SimpleParticleRenderer.h"
using namespace Components;

namespace Levels
{
	void Level10::Start()
	{
		// init textures
		Texture* greenParticleTex = new Texture(this, "Textures/GreenParticle.png", true);

		// init camera
		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

		// add level switchers
		LevelHelper::AddLevelSwitcher(this, new Level9(), false);

		// init entities
		Entity* particles = new Entity("Particles");
		particles->AddComponent(new SimpleParticleRenderer(greenParticleTex));
		this->AddEntity(particles);
	}
}
