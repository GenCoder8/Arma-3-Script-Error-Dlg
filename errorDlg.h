

#include "parent.h"

#include "defines.h"

#define UI_GRID_X	(safezoneX)
#define UI_GRID_Y	(safezoneY)
#define UI_GRID_W	(2.5 * pixelW * pixelGrid)
#define UI_GRID_H	(2.5 * pixelH * pixelGrid)
#define UI_GRID_WAbs	(0)
#define UI_GRID_HAbs	(0)


/* #Beneqo
$[
	1.063,
	["scripterrorsdlg",[["safezoneX","safezoneY","0","0"],"2.5 * pixelW * pixelGrid","2.5 * pixelH * pixelGrid","UI_GRID"],0,0,0],
	[1200,"ScriptErrorTree : RscControlsGroup",[2,"#(argb,8,8,3)color(1,1,1,1)",["38 * UI_GRID_W + UI_GRID_X","5.5 * UI_GRID_H + UI_GRID_Y","25.5 * UI_GRID_W","19.5 * UI_GRID_H"],[-1,-1,-1,-1],[-1,-1,-1,-1],[-1,-1,-1,-1],"","-1"],[]],
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
#define SEDLG_Y (safeZoneY + safezoneH - SEDLG_H - 0.01)




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

class TreeControlsGroup : RscControlsGroup
{
 idc = 1205;
 text = "#(argb,8,8,3)color(1,1,1,1)";
 x = 0;
 y = SEDLG_BUT_H;
 w = 0.8;
 h = 0.8 - (SEDLG_BUT_H * 2) + 0.04;
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

class SettingsButton: RscImgButton
{
 action = "call openScriptErrSettings;";

 idc = 1603;
 text = "a3\missions_f_exp\data\img\lobby\ui_campaign_lobby_background_tablet_button_settings_ca.paa";
 x = 0.75;
 y = 1 - 0.25;
 w = SEDLG_BUT_H;
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

class RscButton_1602: RscButton
{
	action = "call scriptErrorDlgGotoLine;";

	idc = 1602;
	text = "Goto file & line"; //--- ToDo: Localize;
 x = 0.55;
 y = 0;
 w = SEDLG_BUT_W;
 h = SEDLG_BUT_H;
};

class Version : RscText
{
// text = "");
 idc = 1604;
 x = 0.40;
 y = 1 - 0.25;
 w = 0.3;
 h = SEDLG_BUT_H;
};

};

};




};

};




/* #Zysycy
$[
	1.063,
	["errdlgsettings",[["safezoneX","safezoneY","0","0"],"2.5 * pixelW * pixelGrid","2.5 * pixelH * pixelGrid","UI_GRID"],0,0,0],
	[1400,"",[2,"",["18 * UI_GRID_W + UI_GRID_X","15.5 * UI_GRID_H + UI_GRID_Y","28 * UI_GRID_W","2.5 * UI_GRID_H"],[-1,-1,-1,-1],[-1,-1,-1,-1],[-1,-1,-1,-1],"","-1"],[]],
	[1000,"",[2,"Text editor file path",["18 * UI_GRID_W + UI_GRID_X","12.5 * UI_GRID_H + UI_GRID_Y","9.5 * UI_GRID_W","2.5 * UI_GRID_H"],[-1,-1,-1,-1],[-1,-1,-1,-1],[-1,-1,-1,-1],"","-1"],[]],
	[1600,"",[2,"Close",["43.5 * UI_GRID_W + UI_GRID_X","27.5 * UI_GRID_H + UI_GRID_Y","5 * UI_GRID_W","2.5 * UI_GRID_H"],[-1,-1,-1,-1],[-1,-1,-1,-1],[-1,-1,-1,-1],"","-1"],["action = |call closeScriptErrSettings;|;"]],
	[1401,"",[2,"",["18 * UI_GRID_W + UI_GRID_X","21.5 * UI_GRID_H + UI_GRID_Y","28 * UI_GRID_W","2.5 * UI_GRID_H"],[-1,-1,-1,-1],[-1,-1,-1,-1],[-1,-1,-1,-1],"","-1"],[]],
	[1001,"",[2,"Text editor arguments",["18 * UI_GRID_W + UI_GRID_X","18.5 * UI_GRID_H + UI_GRID_Y","9.5 * UI_GRID_W","2.5 * UI_GRID_H"],[-1,-1,-1,-1],[-1,-1,-1,-1],[-1,-1,-1,-1],"","-1"],[]]
]
*/





class SEDlgSettings
{
 idd = SCRIPT_ERROR_DLG_SET;

 movingEnable = false;
 
 //onUnload = "";

 class controlsBackground 
 {
 
 	class Background: IGUIBack
    {
	idc = 3700;
	x = 15.5 * UI_GRID_W + UI_GRID_X;
	y = 5.5 * UI_GRID_H + UI_GRID_Y;
	w = 33 * UI_GRID_W;
	h = 24.5 * UI_GRID_H;
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
// GUI EDITOR OUTPUT START (by GC, v1.063, #Zysycy)
////////////////////////////////////////////////////////

class RscEdit_1400: RscEdit
{
	idc = 1400;
	x = 18 * UI_GRID_W + UI_GRID_X;
	y = 15.5 * UI_GRID_H + UI_GRID_Y;
	w = 28 * UI_GRID_W;
	h = 2.5 * UI_GRID_H;
};
class RscText_1000: RscText
{
	idc = 1000;
	text = "Text editor file path"; //--- ToDo: Localize;
	x = 18 * UI_GRID_W + UI_GRID_X;
	y = 12.5 * UI_GRID_H + UI_GRID_Y;
	w = 9.5 * UI_GRID_W;
	h = 2.5 * UI_GRID_H;
};
class RscButton_1600: RscButton
{
	action = "call closeScriptErrSettings;";

	idc = 1600;
	text = "Close"; //--- ToDo: Localize;
	x = 43.5 * UI_GRID_W + UI_GRID_X;
	y = 27.5 * UI_GRID_H + UI_GRID_Y;
	w = 5 * UI_GRID_W;
	h = 2.5 * UI_GRID_H;
};
class RscEdit_1401: RscEdit
{
	idc = 1401;
	x = 18 * UI_GRID_W + UI_GRID_X;
	y = 21.5 * UI_GRID_H + UI_GRID_Y;
	w = 28 * UI_GRID_W;
	h = 2.5 * UI_GRID_H;
};
class RscText_1001: RscText
{
	idc = 1001;
	text = "Text editor arguments"; //--- ToDo: Localize;
	x = 18 * UI_GRID_W + UI_GRID_X;
	y = 18.5 * UI_GRID_H + UI_GRID_Y;
	w = 9.5 * UI_GRID_W;
	h = 2.5 * UI_GRID_H;
};
////////////////////////////////////////////////////////
// GUI EDITOR OUTPUT END
////////////////////////////////////////////////////////



};

};



