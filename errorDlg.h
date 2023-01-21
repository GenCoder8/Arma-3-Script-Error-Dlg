
#include "parent.h"

#include "defines.h"

#define UI_GRID_X	(safezoneX)
#define UI_GRID_Y	(safezoneY)
#define UI_GRID_W	(2.5 * pixelW * pixelGrid)
#define UI_GRID_H	(2.5 * pixelH * pixelGrid)
#define UI_GRID_WAbs	(0)
#define UI_GRID_HAbs	(0)

import RscTree;


/* #Mucito
$[
	1.063,
	["scripterrorsdlg",[["safezoneX","safezoneY","0","0"],"2.5 * pixelW * pixelGrid","2.5 * pixelH * pixelGrid","UI_GRID"],0,0,0],
	[1200,"ScriptErrorTree : RscTree",[2,"#(argb,8,8,3)color(1,1,1,1)",["38 * UI_GRID_W + UI_GRID_X","5.5 * UI_GRID_H + UI_GRID_Y","25.5 * UI_GRID_W","19.5 * UI_GRID_H"],[-1,-1,-1,-1],[-1,-1,-1,-1],[-1,-1,-1,-1],"","-1"],[]],
	[1600,"",[2,"Close",["39.5 * UI_GRID_W + UI_GRID_X","27 * UI_GRID_H + UI_GRID_Y","7.5 * UI_GRID_W","2 * UI_GRID_H"],[-1,-1,-1,-1],[-1,-1,-1,-1],[-1,-1,-1,-1],"","-1"],["action = |call closeScriptErrorDlg|;"]],
	[1601,"",[2,"Reset error list",["39 * UI_GRID_W + UI_GRID_X","2 * UI_GRID_H + UI_GRID_Y","7.5 * UI_GRID_W","2 * UI_GRID_H"],[-1,-1,-1,-1],[-1,-1,-1,-1],[-1,-1,-1,-1],"","-1"],["action = |call scriptErrorDlgReset;|;"]]
]
*/

class RscImgButton: RscButton
{
type = CT_ACTIVETEXT;
style = ST_PICTURE + ST_KEEP_ASPECT_RATIO;
action = "";
tooltip = "";

color[] = {1,1,1,1};
	colorActive[] = 
	{
		1,
		1,
		1,
		1
	};
	colorDisabled[] = 
	{
		1,
		1,
		1,
		0.25
	};
};


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
	x = 38 * UI_GRID_W + UI_GRID_X;
	y = 5.5 * UI_GRID_H + UI_GRID_Y;
	w = 25.5 * UI_GRID_W;
	h = 19.5 * UI_GRID_H;
	moving = false;
	
	colorBackground[] = {0,0,1,1};
	
    };
 
 };
	
 class objects 
 {
 };
	
	
class controls 
{

////////////////////////////////////////////////////////
// GUI EDITOR OUTPUT START (by GC, v1.063, #Mucito)
////////////////////////////////////////////////////////

class ScriptErrorTree : RscTree
{
	idc = 1200;
	text = "#(argb,8,8,3)color(1,1,1,1)";
	x = 38 * UI_GRID_W + UI_GRID_X;
	y = 5.5 * UI_GRID_H + UI_GRID_Y;
	w = 25.5 * UI_GRID_W;
	h = 19.5 * UI_GRID_H;
};
class RscButton_1600: RscButton
{
	action = "call closeScriptErrorDlg";

	idc = 1600;
	text = "Close"; //--- ToDo: Localize;
	x = 39.5 * UI_GRID_W + UI_GRID_X;
	y = 27 * UI_GRID_H + UI_GRID_Y;
	w = 7.5 * UI_GRID_W;
	h = 2 * UI_GRID_H;
};
class RscButton_1601: RscButton
{
	action = "call scriptErrorDlgReset;";

	idc = 1601;
	text = "Reset error list"; //--- ToDo: Localize;
	x = 39 * UI_GRID_W + UI_GRID_X;
	y = 2 * UI_GRID_H + UI_GRID_Y;
	w = 7.5 * UI_GRID_W;
	h = 2 * UI_GRID_H;
};
////////////////////////////////////////////////////////
// GUI EDITOR OUTPUT END
////////////////////////////////////////////////////////




};

};
