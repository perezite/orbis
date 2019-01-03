typedef int (*)(Window&) SceneRunner;

int level1(Window& window) {
	Scene scene;
	
	Entity tetromino;
	scene.add(&tetromino);
	tetromino.addComponent(TetrominoDrawer);
	
	Entity sprite;
	scene.add(&sprite);
	sprite.addComponent(SpriteDrawer(sprite));
	
	while(scene.isRunning(window)) {
		scene.update();
		
		scene.draw(window);
		window.display();
		
		static Stopwatch sw;
		if (sw.elapsedSeconds() > 10)
			window.close();
	}
}

int level0(Window& window) {
	return level1;
}

void main()
{
	Window window;
	Scene scene;
	std::map<int, SceneRunner> scenes;
	scenes[0] = level0;
	scenes[1] = level1;
	
	int currentScene = 0;
	while(window.isOpen()) 
		currentScene = scenes[currentScene]();
	}
}
