SceneRunner scene2(Window& window) {
	Scene scene;
	
	Entity tetromino;
	tetromino.addComponent(Tetromino);
	tetromino.addComponent(TetrominoRenderer);
	
	Entity sprite;
	sprite.addComponent(SpriteRenderer(sprite));
	
	while(scene.isRunning(window)) {
		scene.draw(window);
		window.display();
	}
}

SceneRunner scene1(Window& window) {
	return scene2;
}

void main()
{
	Window window;
	SceneRunner currentScene = scene1;
	
	while(currentScene != NULL) {
		currentScene = scene(window);
	}
}

