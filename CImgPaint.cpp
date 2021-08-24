//load an image and let the user "paint" regions of the image with different colors. Save the altered image into a file.
//Jeremiah Stubbs

#include <iostream>
#include <cstdlib>
#include <fstream>

#include <sstream>


#include "Queue.h"
#include "CImg.h"

using namespace std;
using namespace cimg_library;

string getUserInput(string prompt)
   {
      string t="";
      cout<<prompt;
      getline(cin,t);
      return t;
   }

bool isValidPosition(int x,int y,int height,int width,int r2,int g2,int b2,CImg<unsigned char> &workimage)
   {//a neighbor is blocked if it's outside the image or if it's not the same color as the region that you're exploring.
	  if (x > width || y > height)
			return false; //outside the image
		else if (x < 0 || y < 0)
			return false; //checking for negative coordinates entered
		else if ((workimage(x,y,0,0) == r2) && (workimage(x,y,0,1) == g2) && (workimage(x,y,0,2) == b2))
			return false;
		else
			return true; //not blocked
   }

bool canGoUp(int x,int y,int r1,int g1,int b1,int height,int width,CImg<unsigned char> &workimage,int **a)
   {
	  if (y == height)
		return false;
		else if (a[y-1][x] == 1)
			return false;
	   else if ((workimage(x,y-1,0,0) != r1) &&  (workimage(x,y-1,0,1) != g1) && (workimage(x,y-1,0,2) != g1))
		return false;
	 else
		return true;
   }

bool canGoRight(int x,int y,int r1,int g1,int b1,int height,int width, CImg<unsigned char> &workimage,int **a)
   {
	   if (x == width)
			return false;
		else if (a[y][x+1] == 1)
			return false;
		else if ((workimage(x+1,y,0,0) != r1) && (workimage(x+1,y,0,1) != g1) && (workimage(x+1,y,0,2) != r1))
			return false;
		else
			return true;

   }

bool canGoDown(int x,int y,int r1,int g1,int b1,int height,int width, CImg<unsigned char> &workimage,int **a)
   {
	   if (y == height)
			return false;
		else if (a[y+1][x] == 1)
			return false;
		else if ((workimage(x,y+1,0,0) != r1) && (workimage(x,y+1,0,1) != g1) && (workimage(x,y+1,0,2) != b1))
			return false;
		else
			return true;

   }

bool canGoLeft(int x,int y,int r1,int g1,int b1,int height,int width, CImg<unsigned char> &workimage,int **a)
   {
	  
	   if (x == width)
			return false;
		else if (a[y][x-1] == 1) 
			return false; 
		else if ((workimage(x-1,y,0,0) != r1) && (workimage(x-1,y,0,1) != g1) && (workimage(x-1,y,0,2) != b1))
			return false;
		else
			return true;

   }


int main(int argc, char *argv[])
{
	
	string filename = getUserInput("Enter name of image(.bmp): ");
	string saveImage = "";
	CImg<unsigned char> workimage(filename.c_str());
	int r1 = 0,g1 = 0,b1 = 0,r2 = 0,g2 = 0,b2 = 0; 
	int height = workimage.height();
	int width = workimage.width();
	int x = 0, y = 0;
	string color = "",input = "";
	Queue q; 
	
	int **a = new int*[width]; //array to keep track of visited pixels
     for (int i = 0;i < width;i++)
     {
        a[i] = new int[height];
	}
					
		
	
	for (int x = 0;x < width;x++)
		{
			for (int y = 0; y < height;y++)
			{
				a[x][y] = 0; //0 = not visited / not blocked
			}
		}
	 
	CImgDisplay mainwindow;
	mainwindow.display(workimage);	
	//prompt the user for a color 
	color = getUserInput("What color do you want?(red,green,blue,orange,cyan,teal,yellow,magenta,olive): "); 
	while (true)
	{	
		
		mainwindow.wait();
			
		if (color == "red")
		{
			r2 = 255;
			g2 = 0;
			b2 = 0;
		}
		else if (color == "green")
		{
			r2 = 0;
			g2 = 255;
			b2 = 0;
		}
		else if (color == "blue")
		{
			r2 = 0;
			g2 = 0;
			b2 = 255;
		}
		else if (color == "orange")
		{
			r2 = 255;
			g2 = 128;
			b2 = 0;
		}
		else if	(color == "cyan")
		{
			r2 = 0;
			g2 = 255;
			b2 = 255;
		}
		else if (color == "teal")
		{
			r2 = 0;
			g2 = 128;
			b2 = 128;
		}
		else if (color == "yellow")
		{
			r2 = 255;
			g2 = 255;
			b2 = 0;
		}
		else if (color == "magenta")
		{
			r2 = 255;
			g2 = 0;
			b2 = 255;
		}
		else if (color == "olive")
		{
			r2 = 128;
			g2 = 128;
			b2 = 0;
		}
		else 
		{
			cout << "Choose a color that is listed." << endl;
			exit(0);
		}
		
		if (mainwindow.button()&1)
		{
			x = mainwindow.mouse_x();
			y = mainwindow.mouse_y();
		
	
			//color of region that is being explored
			r1 = workimage(x,y,0,0);
			g1 = workimage(x,y,0,1);
			b1 = workimage(x,y,0,2);
		
	
			if (!isValidPosition(x,y,height,width,r2,g2,b2,workimage))
			cout << "Invalid Position" << endl;
			else
			{
				q.enQ(x);
				q.enQ(y);
			}
		}
	
		while (!q.isEmpty())
		{
			x = q.deQ();
			y = q.deQ();
					
			//cout << "(" << x << "," << y << ")" << endl;
			//check all the neighbors. If neighbor is not blocked, color neighbor to user entered color
            if (canGoUp(x,y,r1,g1,b1,height,width,workimage,a))
            {
               // y = y - 1;
				q.enQ(x);
                q.enQ(y-1);
                a[y-1][x] = 1;  //1 = blocked/already visited
                workimage(x,y-1,0,0) = r2;
				workimage(x,y-1,0,1) = g2;
				workimage(x,y-1,0,2) = b2;                     
            }
                    
            if (canGoRight(x,y,r1,g1,b1,height,width,workimage,a) && a[y][x+1] == 0)
            {
               //x = x + 1;
               q.enQ(x+1);
               q.enQ(y);
              a[y][x+1] = 1;  
              workimage(x+1,y,0,0) = r2;
			  workimage(x+1,y,0,1) = g2;
			  workimage(x+1,y,0,2) = b2;                     
           }
    
            if (canGoDown(x,y,r1,g1,b1,height,width,workimage,a) && a[y+1][x] == 0)
            {
                // y = y + 1;
                 q.enQ(x);
                 q.enQ(y+1);  
                 a[y+1][x] = 1;
                 workimage(x,y+1,0,0) = r2;
		         workimage(x,y+1,0,1) = g2;
				 workimage(x,y+1,0,2) = b2;                           
            }
                    
            if (canGoLeft(x,y,r1,g1,b1,height,width,workimage,a) && a[y][x-1] == 0)
              {
                   // x = x - 1;
                    q.enQ(x-1);
                    q.enQ(y);
                    a[y][x-1] = 1;
		     		workimage(x-1,y,0,0) = r2;
			    	workimage(x-1,y,0,1) = g2;
					workimage(x-1,y,0,2) = b2;
              }
                    
			    //change the pixel's color channel to mark as visited
				a[y][x] = 1;
				workimage(x,y,0,0) = r2;
				workimage(x,y,0,1) = g2;
				workimage(x,y,0,2) = b2;
				//get next points				
		
			if (q.isEmpty())
			{//no neighbors left in queue
			 //prompt user for different color or if they want to save the image
				input = getUserInput("Do you want a different color(Y/N)? ");
				if (input == "Y")
					color = getUserInput("What color do you want?(red,green,blue,orange,cyan,teal,yellow,magenta,olive): ");
				else
				{
					input = getUserInput("Do you want to save the image(Y/N)? ");
					if (input == "Y")
						{
							saveImage = getUserInput("Enter image filename(.bmp): ");
							workimage.save(saveImage.c_str());
							exit(0);
						} 	
					else 
						exit(0);
				
				}
			}
		}
			
			mainwindow.flush();		
			
	}
	
		
//deallocate 2d array
for (int i = 0;i <= width;i++)
    {
        delete[] a[i];
    }
    delete[] a;

}


