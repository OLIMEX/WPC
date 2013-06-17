// OLIMEX Weekend Programming Challenge Issue-13  WPC13

// Problem: 
//			Convert picture to ASCII art
//			Make code which converts picture to ASCII art.
//			Hints: This is very easy challenge although seems hard at first sight. Just convert the picture from color to
//			gray scale, then select font which you will use to print ASCII art and analyze it which letters you could use
//			for gray scale print ¨C every letter have some coefficient of filling from 0 for the space to 255 for solid bar,
//			use letters which are spread well in the font size space. Then slice your image at rectangles with the font size,
//			calculate the median grey scale for each rectangle and print the corresponding ASCII character with same grey
//			scale value.
//			As test image you can use everything ¨C from Olimex logo to Lena above.
//			Share your results!

// Language: C++
// Date: 16/06/2013
// Miller Wang

#include <iostream>
#include <graphics.h>
#include <stdlib.h>

using namespace std;

//Visible characters.
#define NUMBER 126
//16*8 size.
#define WIDTH 8
#define HEIGHT 16

class Ascii
{	
public:
	int GreyScale[NUMBER];
	char AscCode[NUMBER];
	Ascii();
	void AscArt(Ascii One, char file[]);
	char GetAsc(Ascii One, int Grey);
};

//Initialization.
Ascii::Ascii()
{
	//Start from ' ' character.
	//End with '~'.
	int i=31;
	while(i++<126)		
	{		
		GreyScale[i]=i;
		AscCode[i]=i;			
	}
}


void Ascii::AscArt(Ascii One, char file[])
{
	int ImageGrey, ImageWidth, ImageHeight;
	int i, j, w, h;
	IMAGE newImage;     //Image object.
	
	loadimage(&newImage, file);
	SetWorkingImage(&newImage);
	
	ImageWidth=getwidth()/WIDTH;
	ImageHeight=getheight()/HEIGHT;	
	
	//Convert image 
	for(i=0; i <ImageHeight; i++) 
	{ 
		for(j=0; j<ImageWidth; j++) 
		{ 
			ImageGrey=0; 
			
			//Caculate average grey scale.
			for(h=0; h<HEIGHT; h++) 
				for(w=0; w<WIDTH; w++) 
				{ 
					ImageGrey=ImageGrey+GetRValue(RGBtoGRAY(getpixel(j*WIDTH+w, i*HEIGHT+h)));
				} 
				ImageGrey=ImageGrey/(WIDTH*HEIGHT); 
				ImageGrey=(255-ImageGrey)*90/255;
				putchar(GetAsc(One, ImageGrey));				
		} 		
		putchar('\n');     //Each time print one line.
	}	
}

//Get Ascii code character
char Ascii::GetAsc(Ascii One, int Grey)

{
	int max, min, middle;	
	max=NUMBER;
	min=31;
	
	if(Grey<=One.GreyScale[min]) 
	{ 
		return One.AscCode[min]; 
	} 
	else if (Grey >= One.GreyScale[NUMBER-1]) 
	{ 
		return One.AscCode[NUMBER-1]; 
	} 
	else 
	{ 
		while((max-min) > 1) 
		{ 
			middle=(max+min) >> 1; 
			if(Grey > One.GreyScale[middle]) 
			{ 
				min=middle;
			} 
			else 
			{ 
				max=middle;
			} 
		} 
		return One.AscCode[middle]; 
	} 	
}

int main()
{	
	Ascii NewAscii;
	char file[NUMBER];     //File path + file name.
	cout<<"Input image file path and file name(includes extension name) to convert:"<<endl;
	cout<<"Such as: C:\\a.jpg"<<endl;
	cin>>file;
	system("cls");
	NewAscii.AscArt(NewAscii, file);
	system("pause");	
	return 0;
}