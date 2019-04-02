#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;


int main()
{
	srand(time(0));

	RenderWindow app(VideoMode(544, 704), "Minesweeper!", Style::Titlebar | Style::Close);

	int tile_width = 32;

	int grid_under[17][22];
	int grid_upper[17][22]; 

	Texture under;
	Texture upper;

	under.loadFromFile("Pictures/tiles.jpg");
	upper.loadFromFile("Pictures/desert.jpg");

	Sprite hidden(under);
	Sprite surface(upper);

	/*
		The first part randomly puts a section of desert.jpg to the tile.
		Next part decides randomly 1/5 times whether to 
		put a mine in the current tile.
	*/
	for (int i = 1; i <= 15; i++)
		for (int j = 1; j <= 20; j++)
		{
			grid_upper[i][j] = (rand() % 9) + 12;
			if (rand() % 5 == 0) { grid_under[i][j] = 9; }
			else { grid_under[i][j] = 0; }
		}

	/*
		This calculates how many mines are beside the current tile,
		giving the tile the proper number.
	*/
	for (int i = 1; i <= 15; i++)
		for (int j = 1; j <= 20; j++)
		{
			int n = 0;
			if (grid_under[i][j] == 9) continue;
			if (grid_under[i + 1][j] == 9) n++;
			if (grid_under[i][j + 1] == 9) n++;
			if (grid_under[i - 1][j] == 9) n++;
			if (grid_under[i][j - 1] == 9) n++;
			if (grid_under[i + 1][j + 1] == 9) n++;
			if (grid_under[i - 1][j - 1] == 9) n++;
			if (grid_under[i - 1][j + 1] == 9) n++;
			if (grid_under[i + 1][j - 1] == 9) n++;
			grid_under[i][j] = n;
		}

	while (app.isOpen())
	{
		Vector2i pos = Mouse::getPosition(app);

		int x = pos.x / tile_width;
		int y = pos.y / tile_width;

		Event e;

		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed) { app.close(); }

			if (e.type == Event::MouseButtonPressed)
			{
				grid_upper[x][y] = 0; //If tile is clicked, it being 0 will later mean it will display texture underneath.
				if (e.key.code == Mouse::Right) grid_under[x][y] = 11;
			}
		}

		app.clear(Color::Cyan);
		for (int i = 1; i <= 15; i++)
			for (int j = 1; j <= 20; j++)
			{	
				//If tile underneath is 9 then it is a mine, and upper grid == 0, hence will show all 
				//Tiles underneath the surface texture, ending the game
				if (grid_under[x][y] == 9 && grid_upper[x][y] == 0) { grid_upper[i][j] = 0; }

				//Will draw texture underneath
				if (grid_upper[i][j] == 0) 
				{
					hidden.setTextureRect(IntRect(grid_under[i][j] * tile_width, 0, tile_width, tile_width));
					hidden.setPosition(i*tile_width, j*tile_width);
					app.draw(hidden);
				}
				//Else will just draw surface texture
				else {
					surface.setTextureRect(IntRect(grid_upper[i][j] * tile_width, 0, tile_width, tile_width));
					surface.setPosition(i*tile_width, j*tile_width);
					app.draw(surface);
				}
			}
		app.display();
	}

	return 0;
}
