#include "Level10.h"

#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Components/SimpleParticleRenderer.h"
using namespace Components;

namespace Levels
{
	Level10::Level10()
	{
		// init textures
		Texture* greenParticleTex = new Texture(this, "Textures/GreenParticle.png", true);

		// init camera
		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

		// init entities
		Entity* particles = new Entity("Particles");
		particles->AddComponent(new SimpleParticleRenderer(greenParticleTex));
		this->AddEntity(particles);
	}
}
