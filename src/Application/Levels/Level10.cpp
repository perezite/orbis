#include "Level10.h"

#include "../Controllers/ParticleSystemTester.h"
using namespace Controllers;

#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Components/ParticleRenderer.h"
using namespace Components;

namespace Levels
{
	Level10::Level10()
	{
		// init textures
		Texture* greenParticleTex = new Texture("Textures/GreenParticle.png", true);

		// init camera
		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

		// init entities
		Entity* particles = new Entity("Particles");
		particles->AddComponent(new ParticleSystemTester());
		particles->AddComponent(new ParticleRenderer(greenParticleTex));
		particles->SetTransform(Transform(Vector2D::Zero, 0.0f, Vector2D(0.1f, 0.1f)));
		this->AddEntity(particles);
	}
}
