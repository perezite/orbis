#include "Level9.h"

#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Components/ParticleRenderer.h"
using namespace Components;

namespace Levels
{
	Level9::Level9()
	{
		// init textures
		Texture* yellowBlockTex = new Texture("Textures/YellowBlock.png", true);
		Texture* redBlockTex = new Texture("Textures/RedBlock.png", true);
		Texture* greenParticleTex = new Texture("Textures/GreenParticle.png", true);

		// init camera
		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

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
		particles->AddComponent(new ParticleRenderer(greenParticleTex));
		particles->SetTransform(Transform(Vector2D(0.0f, -0.3f), 0.0f, Vector2D(0.1f, 0.1f)));
		this->AddEntity(particles);
	}
}
