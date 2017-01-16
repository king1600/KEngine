#include "KEngine.h"

int main(int argc, char *argv[])
{
	// Initialize KEngine
	KInit();

	// Create a new KWindow
	KWindow window = KCreateWindow("window title", 640, 480);
	if (&window == nullptr) return 0;
	window.show();

	// Get window objects
	KEvent e;
	KEventManager events;
	KRenderer renderer = window.getRenderer();
	KAssetManager assets = window.getAssetManager();

	// game loop
	bool running = true;
	while (running) {
		
		// event handler
		while (events.hasNext(0)) {
			e = events.nextEvent();
			if (e.type == K_QUIT)
				running = false;
		}

		// delay for fps
		window.tick();

		// drawing
		renderer.clear();
		renderer.setRenderColor({ 255, 0, 0, 0});
		renderer.display();
	}
	
	// Destroy window on exit
	window.destroy();
	return 0;
}