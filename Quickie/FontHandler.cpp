#include "src/FontHandler.h"

FontHandler::FontHandler() {
	
	memset(&this->widths, 0, sizeof(widths));
	
	spriteData.width = 32;
	spriteData.height = 32;
	spriteData.x = 0;
	spriteData.y = 0;
	spriteData.rect.right = spriteData.width;
	spriteData.rect.bottom = spriteData.height;
	spriteData.scale = 0.5;
	startFrame = 0;
	endFrame = 255;
	currentFrame = 0;

}

FontHandler::~FontHandler()
{
}


bool FontHandler::initialize(Graphics* g, int width, int height, int ncols, TextureManager* tM)
{
	return (Image::initialize(g, width, height, ncols, tM));
}

void FontHandler::draw()
{
	Image::draw();
}

void FontHandler::print(int x, int y, std::string text)
{
	auto fx = float(x);
	auto fy = float(y);
	
	for (size_t i = 0; i < text.length(); ++i) {

		auto frame = int(text[i] - '!' + 1);
		setCurrentFrame(frame);
		setX(fx);
		setY(fy);
		draw();		// repeatedly draw each letter 
		if (widths[frame] == 0)
			widths[frame] = getWidth();
		fx += widths[frame] * getScale();

	}
}

int FontHandler::getTotalWidth(std::string text)
{
	float fx = 0;
	
	for (size_t i = 0; i < text.length(); i++)
	{
		int frame = int(text[i] - '!' + 1);
		if (isdigit(text[i]))
			frame += 32;

		fx += widths[frame] * getScale();
	}
	 
		 return int(fx);
}


