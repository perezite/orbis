void main()
{
	Window window;
	DrawBatch batch;
	
	Sprite sprite1;
	Sprite sprite2;
	Sprite sprite3;
	
	while(window.isOpen()) {
		sprite1.draw(batch);
		sprite2.draw(batch);
	
		batch.draw(window);
		sprite3.draw(window);
		window.display();
	}
}