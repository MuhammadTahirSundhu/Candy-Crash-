/*
 * util.h
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */

#ifndef UTIL_H_
#define UTIL_H_
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include<string>
#include<cmath>
#include <sstream>// for basic math functions such as cos, sin, sqrt
#include "CImg.h"
#include<vector>
using namespace std;

#define FPS 80 // frame per seconds

// define another constant to hold ASCII for Escape key.
#define KEY_ESC 27 // A

//
// ColorName you can refer any color by its name..
// In other words you can use colorname as an index in color array (see below)
enum ColorNames {
	MAROON,
	DARK_RED,
	BROWN,
	FIREBRICK,
	CRIMSON,
	RED,
	TOMATO,
	CORAL,
	INDIAN_RED,
	LIGHT_CORAL,
	DARK_SALMON,
	SALMON,
	LIGHT_SALMON,
	ORANGE_RED,
	DARK_ORANGE,
	ORANGE,
	GOLD,
	DARK_GOLDEN_ROD,
	GOLDEN_ROD,
	PALE_GOLDEN_ROD,
	DARK_KHAKI,
	KHAKI,
	OLIVE,
	YELLOW,
	YELLOW_GREEN,
	DARK_OLIVE_GREEN,
	OLIVE_DRAB,
	LAWN_GREEN,
	CHART_REUSE,
	GREEN_YELLOW,
	DARK_GREEN,
	GREEN,
	FOREST_GREEN,
	LIME,
	LIME_GREEN,
	LIGHT_GREEN,
	PALE_GREEN,
	DARK_SEA_GREEN,
	MEDIUM_SPRING_GREEN,
	SPRING_GREEN,
	SEA_GREEN,
	MEDIUM_AQUA_MARINE,
	MEDIUM_SEA_GREEN,
	LIGHT_SEA_GREEN,
	DARK_SLATE_GRAY,
	TEAL,
	DARK_CYAN,
	AQUA,
	CYAN,
	LIGHT_CYAN,
	DARK_TURQUOISE,
	TURQUOISE,
	MEDIUM_TURQUOISE,
	PALE_TURQUOISE,
	AQUA_MARINE,
	POWDER_BLUE,
	CADET_BLUE,
	STEEL_BLUE,
	CORN_FLOWER_BLUE,
	DEEP_SKY_BLUE,
	DODGER_BLUE,
	LIGHT_BLUE,
	SKY_BLUE,
	LIGHT_SKY_BLUE,
	MIDNIGHT_BLUE,
	NAVY,
	DARK_BLUE,
	MEDIUM_BLUE,
	BLUE,
	ROYAL_BLUE,
	BLUE_VIOLET,
	INDIGO,
	DARK_SLATE_BLUE,
	SLATE_BLUE,
	MEDIUM_SLATE_BLUE,
	MEDIUM_PURPLE,
	DARK_MAGENTA,
	DARK_VIOLET,
	DARK_ORCHID,
	MEDIUM_ORCHID,
	PURPLE,
	THISTLE,
	PLUM,
	VIOLET,
	MAGENTA,
	ORCHID,
	MEDIUM_VIOLET_RED,
	PALE_VIOLET_RED,
	DEEP_PINK,
	HOT_PINK,
	LIGHT_PINK,
	PINK,
	ANTIQUE_WHITE,
	BEIGE,
	BISQUE,
	BLANCHED_ALMOND,
	WHEAT,
	CORN_SILK,
	LEMON_CHIFFON,
	LIGHT_GOLDEN_ROD_YELLOW,
	LIGHT_YELLOW,
	SADDLE_BROWN,
	SIENNA,
	CHOCOLATE,
	PERU,
	SANDY_BROWN,
	BURLY_WOOD,
	TAN,
	ROSY_BROWN,
	MOCCASIN,
	NAVAJO_WHITE,
	PEACH_PUFF,
	MISTY_ROSE,
	LAVENDER_BLUSH,
	LINEN,
	OLD_LACE,
	PAPAYA_WHIP,
	SEA_SHELL,
	MINT_CREAM,
	SLATE_GRAY,
	LIGHT_SLATE_GRAY,
	LIGHT_STEEL_BLUE,
	LAVENDER,
	FLORAL_WHITE,
	ALICE_BLUE,
	GHOST_WHITE,
	HONEYDEW,
	IVORY,
	AZURE,
	SNOW,
	BLACKO,
	DIM_GRAY,
	GRAY,
	DARK_GRAY,
	SILVER,
	LIGHT_GRAY,
	GAINSBORO,
	WHITE,
	BLACK,
	SLATE_BM,
};

// set of colors ...
static float colors[][3] = { { 0.501960784313726, 0, 0 }, { 0.545098039215686,
		0, 0 }, { 0.647058823529412, 0.164705882352941, 0.164705882352941 }, {
		0.698039215686275, 0.133333333333333, 0.133333333333333 }, {
		0.862745098039216, 0.0784313725490196, 0.235294117647059 }, { 1, 0, 0 },
		{ 1, 0.388235294117647, 0.278431372549020 }, { 1, 0.498039215686275,
				0.313725490196078 }, { 0.803921568627451, 0.360784313725490,
				0.360784313725490 }, { 0.941176470588235, 0.501960784313726,
				0.501960784313726 }, { 0.913725490196078, 0.588235294117647,
				0.478431372549020 },
		{ 1, 0.627450980392157, 0.478431372549020 },
		{ 1, 0.270588235294118, 0 }, { 1, 0.549019607843137, 0 }, { 1,
				0.647058823529412, 0 }, { 1, 0.843137254901961, 0 }, {
				0.721568627450980, 0.525490196078431, 0.0431372549019608 }, {
				0.854901960784314, 0.647058823529412, 0.125490196078431 }, {
				0.933333333333333, 0.909803921568627, 0.666666666666667 }, {
				0.741176470588235, 0.717647058823529, 0.419607843137255 }, {
				0.941176470588235, 0.901960784313726, 0.549019607843137 }, {
				0.501960784313726, 0.501960784313726, 0 }, { 1, 1, 0 }, {
				0.603921568627451, 0.803921568627451, 0.196078431372549 }, {
				0.333333333333333, 0.419607843137255, 0.184313725490196 }, {
				0.419607843137255, 0.556862745098039, 0.137254901960784 }, {
				0.486274509803922, 0.988235294117647, 0 }, { 0.498039215686275,
				1, 0 }, { 0.678431372549020, 1, 0.184313725490196 }, { 0,
				0.392156862745098, 0 }, { 0, 0.501960784313726, 0 }, {
				0.133333333333333, 0.545098039215686, 0.133333333333333 }, { 0,
				1, 0 }, { 0.196078431372549, 0.803921568627451,
				0.196078431372549 }, { 0.564705882352941, 0.933333333333333,
				0.564705882352941 }, { 0.596078431372549, 0.984313725490196,
				0.596078431372549 }, { 0.560784313725490, 0.737254901960784,
				0.560784313725490 },
		{ 0, 0.980392156862745, 0.603921568627451 },
		{ 0, 1, 0.498039215686275 }, { 0.180392156862745, 0.545098039215686,
				0.341176470588235 }, { 0.400000000000000, 0.803921568627451,
				0.666666666666667 }, { 0.235294117647059, 0.701960784313725,
				0.443137254901961 }, { 0.125490196078431, 0.698039215686275,
				0.666666666666667 }, { 0.184313725490196, 0.309803921568627,
				0.309803921568627 },
		{ 0, 0.501960784313726, 0.501960784313726 }, { 0, 0.545098039215686,
				0.545098039215686 }, { 0, 1, 1 }, { 0, 1, 1 }, {
				0.878431372549020, 1, 1 }, { 0, 0.807843137254902,
				0.819607843137255 }, { 0.250980392156863, 0.878431372549020,
				0.815686274509804 }, { 0.282352941176471, 0.819607843137255,
				0.800000000000000 }, { 0.686274509803922, 0.933333333333333,
				0.933333333333333 },
		{ 0.498039215686275, 1, 0.831372549019608 }, { 0.690196078431373,
				0.878431372549020, 0.901960784313726 }, { 0.372549019607843,
				0.619607843137255, 0.627450980392157 }, { 0.274509803921569,
				0.509803921568627, 0.705882352941177 }, { 0.392156862745098,
				0.584313725490196, 0.929411764705882 }, { 0, 0.749019607843137,
				1 }, { 0.117647058823529, 0.564705882352941, 1 }, {
				0.678431372549020, 0.847058823529412, 0.901960784313726 }, {
				0.529411764705882, 0.807843137254902, 0.921568627450980 }, {
				0.529411764705882, 0.807843137254902, 0.980392156862745 }, {
				0.0980392156862745, 0.0980392156862745, 0.439215686274510 }, {
				0, 0, 0.501960784313726 }, { 0, 0, 0.545098039215686 }, { 0, 0,
				0.803921568627451 }, { 0, 0, 1 }, { 0.254901960784314,
				0.411764705882353, 0.882352941176471 }, { 0.541176470588235,
				0.168627450980392, 0.886274509803922 }, { 0.294117647058824, 0,
				0.509803921568627 }, { 0.282352941176471, 0.239215686274510,
				0.545098039215686 }, { 0.415686274509804, 0.352941176470588,
				0.803921568627451 }, { 0.482352941176471, 0.407843137254902,
				0.933333333333333 }, { 0.576470588235294, 0.439215686274510,
				0.858823529411765 },
		{ 0.545098039215686, 0, 0.545098039215686 }, { 0.580392156862745, 0,
				0.827450980392157 }, { 0.600000000000000, 0.196078431372549,
				0.800000000000000 }, { 0.729411764705882, 0.333333333333333,
				0.827450980392157 },
		{ 0.501960784313726, 0, 0.501960784313726 }, { 0.847058823529412,
				0.749019607843137, 0.847058823529412 }, { 0.866666666666667,
				0.627450980392157, 0.866666666666667 }, { 0.933333333333333,
				0.509803921568627, 0.933333333333333 }, { 1, 0, 1 }, {
				0.854901960784314, 0.439215686274510, 0.839215686274510 }, {
				0.780392156862745, 0.0823529411764706, 0.521568627450980 }, {
				0.858823529411765, 0.439215686274510, 0.576470588235294 }, { 1,
				0.0784313725490196, 0.576470588235294 }, { 1, 0.411764705882353,
				0.705882352941177 },
		{ 1, 0.713725490196078, 0.756862745098039 }, { 1, 0.752941176470588,
				0.796078431372549 }, { 0.980392156862745, 0.921568627450980,
				0.843137254901961 }, { 0.960784313725490, 0.960784313725490,
				0.862745098039216 },
		{ 1, 0.894117647058824, 0.768627450980392 }, { 1, 0.921568627450980,
				0.803921568627451 }, { 0.960784313725490, 0.870588235294118,
				0.701960784313725 },
		{ 1, 0.972549019607843, 0.862745098039216 }, { 1, 0.980392156862745,
				0.803921568627451 }, { 0.980392156862745, 0.980392156862745,
				0.823529411764706 }, { 1, 1, 0.878431372549020 }, {
				0.545098039215686, 0.270588235294118, 0.0745098039215686 }, {
				0.627450980392157, 0.321568627450980, 0.176470588235294 }, {
				0.823529411764706, 0.411764705882353, 0.117647058823529 }, {
				0.803921568627451, 0.521568627450980, 0.247058823529412 }, {
				0.956862745098039, 0.643137254901961, 0.376470588235294 }, {
				0.870588235294118, 0.721568627450980, 0.529411764705882 }, {
				0.823529411764706, 0.705882352941177, 0.549019607843137 }, {
				0.737254901960784, 0.560784313725490, 0.560784313725490 }, { 1,
				0.894117647058824, 0.709803921568628 }, { 1, 0.870588235294118,
				0.678431372549020 },
		{ 1, 0.854901960784314, 0.725490196078431 }, { 1, 0.894117647058824,
				0.882352941176471 },
		{ 1, 0.941176470588235, 0.960784313725490 }, { 0.980392156862745,
				0.941176470588235, 0.901960784313726 }, { 0.992156862745098,
				0.960784313725490, 0.901960784313726 }, { 1, 0.937254901960784,
				0.835294117647059 },
		{ 1, 0.960784313725490, 0.933333333333333 }, { 0.960784313725490, 1,
				0.980392156862745 }, { 0.439215686274510, 0.501960784313726,
				0.564705882352941 }, { 0.466666666666667, 0.533333333333333,
				0.600000000000000 }, { 0.690196078431373, 0.768627450980392,
				0.870588235294118 }, { 0.901960784313726, 0.901960784313726,
				0.980392156862745 },
		{ 1, 0.980392156862745, 0.941176470588235 }, { 0.941176470588235,
				0.972549019607843, 1 }, { 0.972549019607843, 0.972549019607843,
				1 }, { 0.941176470588235, 1, 0.941176470588235 }, { 1, 1,
				0.941176470588235 }, { 0.941176470588235, 1, 1 }, { 1,
				0.980392156862745, 0.980392156862745 }, { 0.411764705882353,
				0.411764705882353, 0.411764705882353 }, { 0.501960784313726,
				0.501960784313726, 0.501960784313726 }, { 0.662745098039216,
				0.662745098039216, 0.662745098039216 }, { 0.752941176470588,
				0.752941176470588, 0.752941176470588 }, { 0.827450980392157,
				0.827450980392157, 0.827450980392157 }, { 0.862745098039216,
				0.862745098039216, 0.862745098039216 }, { 0.980392156862745,
				0.501960784313726, 0.447058823529412 }, { 0.960784313725490,
				0.960784313725490, 0.960784313725490 }, { 1, 1, 1 },
		{ 0, 0, 0 }, { 0.734375, 0.734375, 0.734375} };

//defining some MACROS
#define M_PI 3.141519
#define MAX(A,B) ((A) > (B) ? (A):(B)) // finds max of two numbers
#define MIN(A,B) ((A) < (B) ? (A):(B)) // find min of two numbers
#define ABS(A) ((A) < (0) ? -(A):(A))  // find ABS of a given number

// define some constants

float Deg2Rad(float degree);
float Rad2Deg(float angle);

// function reads the image and give the pixels in
// column major order, every pixel is placed linearly
// in Reg, Green, Blue format and then columnwise same as opengl...
// uses CImg
void ReadImage(string imgname, vector<unsigned char> &imgArray);

// Function draws a circle of given radius and color at the
// given point sx and sy.
void DrawCircle(float sx, float sy, float radius, float*color);
void DrawSquare(int sx, int sy, int size,float* color);
// Function draws a circular curve of given
void Torus2d(int x /*Starting position x*/, int y /*Starting position Y*/,
		float angle, // starting angle in degrees
		float length,           // length of arc in degrees, >0
		float radius,           // inner radius, >0
		float width,            // width of torus, >0
		unsigned int samples,    // number of circle samples, >=3
		float *color = NULL);

// Function draws a line between point P1(x1,y1) and P2(x2,y2)
// of given width and colour
void DrawLine(int x1, int y1, int x2, int y2, int lwidth = 3, float *color =
		NULL);
// Function draws a rectangle with rounded corners at given x,y coordinates
void DrawRoundRect(float x, float y, float width, float height,
		float* color = 0, float radius = 0.0);
// Function draws a string at given x,y coordinates
void DrawString(int x, int y, int width, int height, const string& str,
		float * color = NULL);
void DrawString(float x, float y, const string& str, float * color = NULL);

// seed the random numbers generator by current time (see the documentation of srand for further help)...
void InitRandomizer();

//This function returns a random value within the specified range of [rmin, rmax] ...
long GetRandInRange(const long &rmin, const long &rmax);

/*To draw a triangle we need three vertices with each vertex having 2-coordinates [x, y] and a color for the triangle.
 * This function takes 4 arguments first three arguments (3 vertices + 1 color) to
 * draw the triangle with the given color.
 * */
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, float *color);
// Draws a rectangle of the specified color
void DrawRectangle(int sx, int sy, int width, int height, float *color);

// Convert a Number to String...

string Num2Str(int t);
#endif /* UTIL_H_ */

const int boundaryLineWidth = 10;
const int boundaryLeftX = 80;
const int boundaryBottomY = 30;
const int boundaryRightX = 780;
const int boundaryTopY = 480;
int score = 0; // Tracks the player's score
int eachLevelScore = 20;
bool gamePause = false;
int levelNo = 0;
///////////////////////
const int row = 13;
const int col = 21;
const int cellSize = 30;
int Level1[row][col];
int scorePoint = 100;
int selectedRow = -1, selectedCol = -1;
bool isDragging = false;
bool gridflag = true;


//////////////////////////////////////////////////
///////////////////////////////////////////////////////
//////////////////////////////////////////////////////
float Deg2Rad(float degree) {
	return (degree / 180.0) * M_PI;
}
float Rad2Deg(float angle) {
	return angle * (180.0 / M_PI);
}
void DrawSquare(int sx, int sy, int size,float color[]) {
	int mx=size,my=size;
	//cout<<endl<<"Coord  "<<sx<<" "<<sy<<" "<<mx<<" "<<my<<flush;
		glColor3fv(color); // specify the color of the brick
		glBegin(GL_TRIANGLES);
		glVertex4f(sx, sy, 0, 1);
		glVertex4f(sx + mx - 1, sy, 0, 1);
		glVertex4f(sx + mx - 1, sy + my - 1, 0, 1);
		glVertex4f(sx, sy, 0, 1);
		glVertex4f(sx + mx - 1, sy + my - 1, 0, 1);
		glVertex4f(sx, sy + my - 1, 0, 1);
		glEnd();
	}
// seed the random numbers generator by current time (see the documentation of srand for further help)...
void InitRandomizer() {
	srand((unsigned int)time(0)); // time(0) returns number of seconds elapsed since January 1, 1970.
}

//This function returns a random value within the specified range of [rmin, rmax] ...
long GetRandInRange(const long &rmin, const long &rmax) {
	long range = rmax - rmin; // find the range
	long value = (rand() % (long)range) + rmin; // translate the generated number ...
	//	cout << value << endl << flush;
	return value;
}

/*To draw a triangle we need three vertices with each vertex having 2-coordinates [x, y] and a color for the triangle.
* This function takes 4 arguments first three arguments (3 vertices + 1 color) to
* draw the triangle with the given color.
* */
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
	float color[]) {
	glColor3fv(color); // Set the triangle colour
	// ask library to draw triangle at given position...

	glBegin(GL_TRIANGLES);
	/*Draw triangle using given three vertices...*/
	glVertex4i(x1, y1, 0, 1);
	glVertex4i(x2, y2, 0, 1);
	glVertex4i(x3, y3, 0, 1);
	glEnd();
}

const int nvertices = 722;
GLfloat vertices[nvertices][2];
void InitCircleVertices(float radius) {

	float hdegree = M_PI / 360.0;
	float angle = 0;
	for (int i = 0; i < nvertices; ++i) {
		vertices[i][0] = radius * cos(angle);
		vertices[i][1] = radius * sin(angle);
		angle += hdegree;
	}
}
/*To draw a Circle we need a center point (sx, sy) and the radius, along with the color of circle.
* This function takes 4 arguments first two arguments (3 vertices + 1 color) to
* draw the triangle with the given color.
* */
void DrawCircle(float sx, float sy, float radius, float*color) {
	glColor3fv(color); // set the circle color
	InitCircleVertices(radius);
	glBegin(GL_TRIANGLE_FAN);
	glVertex4f(sx, sy, 0, 1);
	for (int i = 0; i < nvertices; ++i)
		glVertex4f(sx + vertices[i][0], sy + vertices[i][1], 0, 1);
	glEnd();
}
// function used to draw curves...
void Torus2d(int x /*Starting position x*/, int y /*Starting position Y*/,
	float angle, // starting angle in degrees
	float length,           // length of arc in degrees, >0
	float radius,           // inner radius, >0
	float width,            // width of torus, >0
	unsigned int samples,   // number of circle samples, >=3
	float *color) {
	angle = Deg2Rad(angle);
	length = Deg2Rad(length);
	if (color) { // set color for the Torus
		glColor3fv(color);
	}
	if (samples < 3)
		samples = 3;
	const float outer = radius + width;
	glBegin(GL_QUAD_STRIP);
	for (unsigned int i = 0; i <= samples; ++i) {
		float a = angle + (i / (float)samples) * length;
		glVertex2f(x + radius * cos(a), y + radius * sin(a));
		glVertex2f(x + outer * cos(a), y + outer * sin(a));
	}
	glEnd();
}

// Draw lines between two points P1(x1,y1) and P2(x2,y2)
void DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color) {
	glLineWidth(lwidth);
	if (color)
		glColor3fv(color);
	glBegin(GL_LINES);
	glVertex3f(x1, y1, 0.0);
	glVertex3f(x2, y2, 0);
	glEnd();
}

// used for normalized coordinates
void DrawString(int x, int y, int width, int height, const string &score,
float*color) {
	float fx = (float)x / width * 2 - 1, fy = (float)y / height * 2 - 1;
	DrawString(fx, fy, score, color);
}
// Function draws a string at given x,y coordinates
void DrawString(float x, float y, const string& score, float * color) {
	//  A pointer to a font style..
	//  Fonts supported by GLUT are: GLUT_BITMAP_8_BY_13,
	//  GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10,
	//  GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
	//  GLUT_BITMAP_HELVETICA_12, and GLUT_BITMAP_HELVETICA_18.
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	if (color)
		glColor3fv(color);
	glRasterPos3f(x, y, 1);
	//  Draw the characters one by one
	for (int i = 0; i < score.size(); i++)
		glutBitmapCharacter(font_style, score[i]);
	glPopMatrix();
}
//
//  Draws rounded rectangle.
//
//  Slightly tuned version of http://stackoverflow.com/questions/5369507/opengles-1-0-2d-rounded-rectangle
//
#define ROUNDING_POINT_COUNT 16      // Larger values makes circle smoother.

typedef struct {
	float x;
	float y;

} Vector2f;
void DrawRoundRect(float x, float y, float width, float height, float* color,
	float radius) {
	y = y + height;
	Vector2f top_left[ROUNDING_POINT_COUNT];
	Vector2f bottom_left[ROUNDING_POINT_COUNT];
	Vector2f top_right[ROUNDING_POINT_COUNT];
	Vector2f bottom_right[ROUNDING_POINT_COUNT];

	if (radius == 0.0) {
		radius = MIN(width, height);
		radius *= 0.10; // 10%
	}

	int i = 0;
	float x_offset, y_offset;
	float step = (2.0f * M_PI) / (ROUNDING_POINT_COUNT * 4), angle = 0.0f;

	unsigned int index = 0, segment_count = ROUNDING_POINT_COUNT;
	Vector2f bottom_left_corner = { x + radius, y - height + radius };

	while (i != segment_count) {
		x_offset = cosf(angle);
		y_offset = sinf(angle);

		top_left[index].x = bottom_left_corner.x - (x_offset * radius);
		top_left[index].y = (height - (radius * 2.0f)) + bottom_left_corner.y
			- (y_offset * radius);

		top_right[index].x = (width - (radius * 2.0f)) + bottom_left_corner.x
			+ (x_offset * radius);
		top_right[index].y = (height - (radius * 2.0f)) + bottom_left_corner.y
			- (y_offset * radius);

		bottom_right[index].x = (width - (radius * 2.0f)) + bottom_left_corner.x
			+ (x_offset * radius);
		bottom_right[index].y = bottom_left_corner.y + (y_offset * radius);

		bottom_left[index].x = bottom_left_corner.x - (x_offset * radius);
		bottom_left[index].y = bottom_left_corner.y + (y_offset * radius);

		/*top_left[index].x = top_left[index].x;
		top_left[index].y = top_left[index].y;

		top_right[index].x = top_right[index].x;
		top_right[index].y = top_right[index].y;

		bottom_right[index].x = bottom_right[index].x;
		bottom_right[index].y = bottom_right[index].y;

		bottom_left[index].x = bottom_left[index].x;
		bottom_left[index].y = bottom_left[index].y;
		*/
		angle -= step;

		++index;

		++i;
	}

	static GLubyte clr[] = { 156, 207, 255, 128 }; // Light blue, 50% transparent.

	if (color)
		glColor4fv(color);
	else
		glColor4ubv(clr);

	glBegin(GL_TRIANGLE_STRIP);
	{
		// Top
		for (i = segment_count - 1; i >= 0; i--) {
			glVertex2f(top_left[i].x, top_left[i].y);
			glVertex2f(top_right[i].x, top_right[i].y);
		}

		// In order to stop and restart the strip.
		glVertex2f(top_right[0].x, top_right[0].y);
		glVertex2f(top_right[0].x, top_right[0].y);

		// Center
		glVertex2f(top_right[0].x, top_right[0].y);
		glVertex2f(top_left[0].x, top_left[0].y);
		glVertex2f(bottom_right[0].x, bottom_right[0].y);
		glVertex2f(bottom_left[0].x, bottom_left[0].y);

		// Bottom
		for (i = 0; i != segment_count; i++) {
			glVertex2f(bottom_right[i].x, bottom_right[i].y);
			glVertex2f(bottom_left[i].x, bottom_left[i].y);
		}
	}
	glEnd();
} //DrawRoundRect

//#endif
/*typedef struct
{
float x;
float y;

} Vector2f;
*/

void RoundRect(int x, int y, int width, int height, int radius,
	int resolution) {
	float step = (2.0f * M_PI) / resolution, angle = 0.0f, x_offset, y_offset;

	int i = 0;

	unsigned int index = 0, segment_count = (int)(resolution / 4);

	Vector2f *top_left = (Vector2f *)malloc(segment_count * sizeof(Vector2f)),
		*bottom_left = (Vector2f *)malloc(
		segment_count * sizeof(Vector2f)), *top_right =
		(Vector2f *)malloc(segment_count * sizeof(Vector2f)),
		*bottom_right = (Vector2f *)malloc(
		segment_count * sizeof(Vector2f)), bottom_left_corner = { x
		+ radius, y - height + radius };

	while (i != segment_count) {
		x_offset = cosf(angle);
		y_offset = sinf(angle);

		top_left[index].x = bottom_left_corner.x - (x_offset * radius);
		top_left[index].y = (height - (radius * 2.0f)) + bottom_left_corner.y
			- (y_offset * radius);

		top_right[index].x = (width - (radius * 2.0f)) + bottom_left_corner.x
			+ (x_offset * radius);
		top_right[index].y = (height - (radius * 2.0f)) + bottom_left_corner.y
			- (y_offset * radius);

		bottom_right[index].x = (width - (radius * 2.0f)) + bottom_left_corner.x
			+ (x_offset * radius);
		bottom_right[index].y = bottom_left_corner.y + (y_offset * radius);

		bottom_left[index].x = bottom_left_corner.x - (x_offset * radius);
		bottom_left[index].y = bottom_left_corner.y + (y_offset * radius);

		top_left[index].x = roundf(top_left[index].x);
		top_left[index].y = roundf(top_left[index].y);

		top_right[index].x = roundf(top_right[index].x);
		top_right[index].y = roundf(top_right[index].y);

		bottom_right[index].x = roundf(bottom_right[index].x);
		bottom_right[index].y = roundf(bottom_right[index].y);

		bottom_left[index].x = roundf(bottom_left[index].x);
		bottom_left[index].y = roundf(bottom_left[index].y);

		angle -= step;

		++index;

		++i;
	}

	glBegin(GL_TRIANGLE_STRIP);
	{
		// Top
		{
			i = 0;
			while (i != segment_count) {
				//glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
				glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
				glVertex2i(top_left[i].x, top_left[i].y);

				//glColor4f( 0.0f, 1.0f, 0.0f, 1.0f );
				glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
				glVertex2i(top_right[i].x, top_right[i].y);

				++i;
			}
		}

		// In order to stop and restart the strip.
		glColor4f(0.0f, 1.0f, 0.0f, 1.5f);
		glVertex2i(top_right[0].x, top_right[0].y);

		glColor4f(0.0f, 1.0f, 0.0f, 1.5f);
		glVertex2i(top_right[0].x, top_right[0].y);

		// Center
		{
			//glColor4f( 0.0f, 1.0f, 0.0f,  1.0f );
			glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
			glVertex2i(top_right[0].x, top_right[0].y);

			//glColor4f( 1.0f, 0.0f, 0.0f,  1.0f );
			glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
			glVertex2i(top_left[0].x, top_left[0].y);

			//glColor4f( 0.0f, 0.0f, 1.0f,  1.0f );
			glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
			glVertex2i(bottom_right[0].x, bottom_right[0].y);

			//glColor4f( 1.0f, 1.0f, 0.0f,  1.0f );
			glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
			glVertex2i(bottom_left[0].x, bottom_left[0].y);
		}

		// Bottom
		i = 0;
		while (i != segment_count) {
			//glColor4f( 0.0f, 0.0f, 1.0f,  1.0f );
			glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
			glVertex2i(bottom_right[i].x, bottom_right[i].y);

			//glColor4f( 1.0f, 1.0f, 0.0f,  1.0f );
			glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
			glVertex2i(bottom_left[i].x, bottom_left[i].y);

			++i;
		}
	}
	glEnd();

	glBegin(GL_LINE_STRIP);

	//glColor4f( 0.0f, 1.0f, 1.0f, 1.0f );
	glColor4f(1.0f, 0.5f, 0.0f, 1.0f);

	// Border
	{
		i = (segment_count - 1);
		while (i > -1) {
			glVertex2i(top_left[i].x, top_left[i].y);

			--i;
		}

		i = 0;
		while (i != segment_count) {
			glVertex2i(bottom_left[i].x, bottom_left[i].y);

			++i;
		}

		i = (segment_count - 1);
		while (i > -1) {
			glVertex2i(bottom_right[i].x, bottom_right[i].y);

			--i;
		}

		i = 0;
		while (i != segment_count) {
			glVertex2i(top_right[i].x, top_right[i].y);

			++i;
		}

		// Close the border.
		glVertex2i(top_left[(segment_count - 1)].x,
			top_left[(segment_count - 1)].y);
	}
	glEnd();

	glBegin(GL_LINES);

	//glColor4f( 0.0f, 1.0f, 1.0f, 1.0f );
	glColor4f(0.0f, 0.5f, 1.0f, 1.0f);

	// Separator
	{
		// Top bar
		glVertex2i(top_right[0].x, top_right[0].y);

		glVertex2i(top_left[0].x, top_left[0].y);

		// Bottom bar
		glVertex2i(bottom_left[0].x, bottom_left[0].y);

		glVertex2i(bottom_right[0].x, bottom_right[0].y);
	}
	glEnd();

	free(top_left);
	free(bottom_left);
	free(top_right);
	free(bottom_right);
}

void DrawRectangle(int sx, int sy, int mx, int my, float *color) {
	glColor3fv(color); // specify the color of the rectangle
	glBegin(GL_TRIANGLES);
	glVertex4f(sx, sy, 0, 1);
	glVertex4f(sx + mx - 1, sy, 0, 1);
	glVertex4f(sx + mx - 1, sy + my - 1, 0, 1);
	glVertex4f(sx, sy, 0, 1);
	glVertex4f(sx + mx - 1, sy + my - 1, 0, 1);
	glVertex4f(sx, sy + my - 1, 0, 1);
	glEnd();
}
string Num2Str(int t) {
	stringstream s;
	s << t;
	return s.str();
}

void ReadImage(string imgname, vector<unsigned char> &imgArray) {
	using namespace cimg_library;
	CImg<unsigned char> img(imgname.c_str());
	imgArray.resize(img.height() * img.width() * 3, 0);
	int k = 0;
	unsigned char *rp = img.data();
	unsigned char *gp = img.data() + img.height() * img.width();
	unsigned char *bp = gp + img.height() * img.width();

	for (int j = 0; j < img.width(); ++j) {
		int t = j;
		for (int i = 0; i < img.height(); ++i, t += img.width()) {
			imgArray[k++] = rp[t];
			imgArray[k++] = gp[t];
			imgArray[k++] = bp[t];
		}
		//imgArray[i][j] = img[k++];
	}
}

