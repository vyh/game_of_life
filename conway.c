/* Conway's Game of Life
 * an undergraduate programming project
 * coded by Nicki Hoffman in 2008
 */

#include <FPT.h>

void overlay_grid()
{
	double a;
	G_rgb(0.4, 0.4, 0.4);
	
	a = 0;
	while (a < 510) 
	{ 
		G_line(0, a, 510, a);  
		a = a + 15; 
	}

	a = 0;
	while (a < 510) 
	{ 
		G_line(a, 0, a, 510);
		a = a + 15; 
	}
}


void display_world(char **w)
{
	double r, c, x, y;
	double q;

	G_rgb(0.9, 0.9, 0.9); 
	G_clear();

	G_rgb(0.8, 0.4, 0.2);
	G_rectangle(210, 555, 65, 17);
	G_draw_string("Start", 218, 556);
	G_draw_string("c to reset - q to quit", 90, 525);

	G_rgb(0, 0.5, 0.8);
	r = 1; 
	y = 0;
	while (r < 35) 
	{
		c = 1; 
		x = 0;
		while (c < 35) 
		{
			if (w[r][c] == '*') { G_fill_rectangle(x, y, 15, 15); }
			c = c + 1; 
			x = x + 15;
		}
		r = r + 1; 
		y = y + 15;
	}

	overlay_grid();
}


char set_up_world(char **w)
{
	double r, c, q;
	double p[2];
	G_wait_click(p);
	while (p[0] < 210 || p[0] > 275 || p[1] < 555 || p[1] > 572)
	{
		c = floor(p[0] / 15) + 1; 
		r = floor(p[1] / 15) + 1;
		w[r][c] = '*';
		display_world(w);
		G_wait_click(p);
	}
	return **w;
}


int main()
{
	double swidth, sheight;
	double q, k;
	double nr, nc, r, c, row, col, live;
	char w[100][100];
	nc = 36; 
	nr = 36; 
	live = 0; 
	k = 0;

	swidth = 511; 
	sheight = 600;
	G_init_graphics(swidth, sheight);

	while (0 == 0)
	{
		r = 0;
		while (r < nr)
		{
			c = 0;
			while (c < nc) 
			{
				w[r][c] = '.';
				c = c + 1;
			}
			r = r + 1;
		}

		display_world(w);
		**w = set_up_world(w);

		while (k == 0)
		{
			r = 1;
			while (r < nr - 1)
			{
				c = 1;
				while (c < nc - 1)
				{
					row = r - 1;
					live = 0;
					while (row <= r + 1)
					{
						col = c - 1;
						while (col <= c + 1)
						{
							if ((row != r || col != c) && (w[row][col] == '*' || w[r][c] == 'd'))
							{
								live = live + 1;
							}
							col = col + 1;
						}
						row = row + 1;
					}
					if (w[r][c] == '*' && (live < 2 || live > 3)) { w[r][c]='d'; }
					else if (w[r][c] == '.' && live == 3) { w[r][c] = 'l'; }
					c = c + 1;
				}
				r = r + 1;
			}

			r = 1;
			while (r < nr - 1)
			{
				c = 1;
				while (c < nc - 1)
				{
					if (w[r][c] == 'l') { w[r][c] = '*'; }
					else if (w[r][c] == 'd') { w[r][c] = '.'; }
					c = c + 1;
				}
				r = r + 1;
			}

			display_world(w);
			q = G_wait_key();
			if (q == 99) { k = 1; }
			else if (q == 113) { G_close(); }
		}
		k = 0;
	}
}
