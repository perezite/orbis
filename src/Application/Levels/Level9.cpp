#include "Level9.h"

#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/ParticleSystemRenderer.h"
using namespace Components;

namespace Levels
{
	Level9::Level9()
	{
		// init textures
		Texture* greenParticleTex = new Texture("Textures/GreenParticle.png");

		// init camera
		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

		// add particle system
		Entity* particles = new Entity();
		particles->AddComponent(new ParticleSystemRenderer(greenParticleTex));
		AddEntity(particles);
	}
}
