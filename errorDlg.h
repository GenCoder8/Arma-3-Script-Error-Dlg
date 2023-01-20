
#include "parent.h"

#include "defines.h"

#define UI_GRID_X	(safezoneX)
#define UI_GRID_Y	(safezoneY)
#define UI_GRID_W	(2.5 * pixelW * pixelGrid)
#define UI_GRID_H	(2.5 * pixelH * pixelGrid)
#define UI_GRID_WAbs	(0)
#define UI_GRID_HAbs	(0)

import RscTree;




class ScriptErrorDlg
{
 idd = SCRIPT_ERROR_DLG;

 movingEnable = false;
 
 //onUnload = "";

 class controlsBackground 
 {
 
 	class Background: IGUIBack
    {
	idc = 3700;
	x = 16 * UI_GRID_W + UI_GRID_X;
	y = 6 * UI_GRID_H + UI_GRID_Y;
	w = 36 * UI_GRID_W;
	h = 27.5 * UI_GRID_H;
	moving = false;
	
	colorBackground[] = {0,0,0,1};
	
    };
 
 };
	
 class objects 
 {
 };
	
	
class controls 
{

////////////////////////////////////////////////////////
// GUI EDITOR OUTPUT START (by GC, v1.063, #Musazo)
////////////////////////////////////////////////////////

class RscPicture_1200: RscTree
{
	idc = 1200;
	text = "#(argb,8,8,3)color(1,1,1,1)";
	x = 34 * UI_GRID_W + UI_GRID_X;
	y = 7 * UI_GRID_H + UI_GRID_Y;
	w = 34 * UI_GRID_W;
	h = 25.5 * UI_GRID_H;
};
////////////////////////////////////////////////////////
// GUI EDITOR OUTPUT END
////////////////////////////////////////////////////////


};

};
