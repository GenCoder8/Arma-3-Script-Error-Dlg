
#include "parent.h"

#include "defines.h"

#define UI_GRID_X	(safezoneX)
#define UI_GRID_Y	(safezoneY)
#define UI_GRID_W	(2.5 * pixelW * pixelGrid)
#define UI_GRID_H	(2.5 * pixelH * pixelGrid)
#define UI_GRID_WAbs	(0)
#define UI_GRID_HAbs	(0)


/* #Mucito
$[
	1.063,
	["scripterrorsdlg",[["safezoneX","safezoneY","0","0"],"2.5 * pixelW * pixelGrid","2.5 * pixelH * pixelGrid","UI_GRID"],0,0,0],
	[1200,"ScriptErrorTree : RscTree",[2,"#(argb,8,8,3)color(1,1,1,1)",["38 * UI_GRID_W + UI_GRID_X","5.5 * UI_GRID_H + UI_GRID_Y","25.5 * UI_GRID_W","19.5 * UI_GRID_H"],[-1,-1,-1,-1],[-1,-1,-1,-1],[-1,-1,-1,-1],"","-1"],[]],
	[1600,"",[2,"Close",["39.5 * UI_GRID_W + UI_GRID_X","27 * UI_GRID_H + UI_GRID_Y","7.5 * UI_GRID_W","2 * UI_GRID_H"],[-1,-1,-1,-1],[-1,-1,-1,-1],[-1,-1,-1,-1],"","-1"],["action = |call closeScriptErrorDlg|;"]],
	[1601,"",[2,"Reset error list",["39 * UI_GRID_W + UI_GRID_X","2 * UI_GRID_H + UI_GRID_Y","7.5 * UI_GRID_W","2 * UI_GRID_H"],[-1,-1,-1,-1],[-1,-1,-1,-1],[-1,-1,-1,-1],"","-1"],["action = |call scriptErrorDlgReset;|;"]]
]
*/


import RscTree;


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

// Inside controls group only
#define SEDLG_BUT_W 0.3
#define SEDLG_BUT_H 0.1

// The dialog size
#define SEDLG_W 0.85
#define SEDLG_H 0.85
#define SEDLG_X (safeZoneX + safezoneW - SEDLG_W - 0.01)
#define SEDLG_Y (safeZoneY + (safezoneH / 2) - (SEDLG_H / 2) )




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
	x = SEDLG_X;
	y = SEDLG_Y;
	w = SEDLG_W;
	h = SEDLG_H;
	moving = false;
	
	colorBackground[] = {0,0,1,1};
	
    };
 
 };
	
 class objects 
 {
 };
	
	
class controls 
{



class ScriptErrorCtrlGroup: ControlsGroupNoScrollBars
{
	idc = 2303;
	x = SEDLG_X;
	y = SEDLG_Y;
	w = SEDLG_W;
	h = SEDLG_H;

class Controls
{

class ScriptErrorTree : RscTree
{
 idc = 1200;
 text = "#(argb,8,8,3)color(1,1,1,1)";
 x = 0;
 y = SEDLG_BUT_H;
 w = 0.8;
 h = 0.8 - (SEDLG_BUT_H * 2);
};

class RscButton_1601: RscButton
{
 action = "call scriptErrorDlgReset;";

 idc = 1601;
 text = "Reset error list"; //--- ToDo: Localize;
 x = 0;
 y = 0;
 w = SEDLG_BUT_W;
 h = SEDLG_BUT_H;
};

class RscButton_1600: RscButton
{
 action = "call closeScriptErrorDlg;";

 idc = 1600;
 text = "Close"; //--- ToDo: Localize;
 x = 0;
 y = 1 - 0.25;
 w = SEDLG_BUT_W;
 h = SEDLG_BUT_H;
};

};

};




};

};
