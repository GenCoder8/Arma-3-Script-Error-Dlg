
#include "\a3\ui_f\hpp\definedikcodes.inc"
#include "defines.h"
#include "resources.h"


loggedErrors = [];



openScriptErrorDlg =
{
private _display = findDisplay SCRIPT_ERROR_DLG;

if(!isnull _display) exitWith {}; // Already open

createDialog "ScriptErrorDlg";

_display = findDisplay SCRIPT_ERROR_DLG;

private _ctrlsGroup = _display displayCtrl 1205;

private _tvCtrl = _display ctrlCreate ["RscTree", 1200, _ctrlsGroup];
_tvCtrl ctrlSetPosition [0,0,1.5,0.55];
_tvCtrl ctrlCommit 0;


call scriptErrorDlgPopulate;


};

closeScriptErrorDlg =
{
 closeDialog 0;
};

scriptErrorDlgPopulate =
{

private _display = findDisplay SCRIPT_ERROR_DLG;
private _tv = _display displayCtrl 1200;

tvClear _tv;

{

 _x call scriptErrorDlgAdd; 

} foreach loggedErrors;

};

scriptErrorDlgAdd =
{
params ["_errId","_msg","_file","_line","_offset","_filecontent","_trace"];


private _display = findDisplay SCRIPT_ERROR_DLG;
private _tv = _display displayCtrl 1200;


#define MAX_FILENAME_SHOWN 64

_pathToFilename =
{
params ["_functionName"];

private _mp = getMissionPath "";

//private _filename = _functionName select [ count _mp, count _functionName ];

_fl = count _functionName;

_str = if(_fl > MAX_FILENAME_SHOWN) then {  format[" ...%1 ",  _functionName select [MAX_FILENAME_SHOWN/2,_fl] ] } else { _functionName };

_str
};

_errPosText =
{
 format["%1 at line %2", _file call _pathToFilename, _line]
};

private _emsgStart = format ["Error %1", _msg];

if(count _file > 0) then
{
_emsgStart = _emsgStart + format [" in %1", _file call _pathToFilename ];
}
else // For errors without a file
{
//_emsgStart = _emsgStart + format [" in "" ... %1 ... "" ", trim (_filecontent) ];

systemchat format [">>> %1 %2", _offset, _line];

_shortText = _filecontent;
if(count _filecontent > 32) then
{
 _shortText = _filecontent select [_offset - 16,32];
};

_emsgStart = _emsgStart + format [" in "" ... %1 ... "" ", trim _shortText ];
};

_emsgStart = _emsgStart + format [" line: %1", _line ];


_tvmainindex = _tv tvAdd [[], _emsgStart ];

for "_i" from (count _trace - 1) to 0 step -1 do
{
 (_trace # _i) params ["_file", "_line", "_scopeName", "_variables"];

// diag_log "-------------------------------------------------------------------------------------------";

//diag_log format [">>>>>>>>!!!!>>>>>>>>>> %1 %2", _file, _line, (_trace # _i)];

 _tvsubindex = _tv tvAdd [[_tvmainindex], format["%1", call _errPosText] ];

{
 _varname = _x;
 _varvalue = "nil";
 _varType = "";

if(!isnil "_y") then
{
_varType = typename _y;

if(_varType == "CODE") then
{
 _varvalue = "Code";
}
else
{
_varvalue = _y;
};
};


 _tv tvAdd [[_tvmainindex,_tvsubindex], format ["%1 %2 = %3",_varType,_varname,_varvalue]];

} foreach _variables;


};

};

scriptErrorDlgReset =
{

 loggedErrors = [];

 call scriptErrorDlgPopulate; // Clears

 call scriptErrorDlgOnNew;

};


addMissionEventHandler ["ScriptError",
{
 params ["_msg","_file","_line","_offset","_filecontent","_trace"];

_this call logErrorInfo;


[] spawn
{
sleep 0.2;

diag_log "allCutLayers:";
{
 diag_log format ["layer: %1", _x];
} foreach allCutLayers;

};

}];



logErrorInfo =
{
 params ["_msg","_file","_line","_offset","_filecontent","_trace"];

private _errid = format ["%1%2", _file, _line];


if(count _file == 0) then // For console errors
{
 private _code = _filecontent;

 if(count _code > 256) then { _code = _code select [0,256]; }; // Some limit 

 _errid = format ["%1%2", _code, _line];
};


if((loggedErrors findif { (_x # 0) == _errid }) >= 0) exitWith {}; // Already logged


private _earr = [_errid] + _this;

loggedErrors pushback _earr;


_earr call scriptErrorDlgAdd;

call scriptErrorDlgOnNew;

};




waituntil { !isnull (findDisplay 46) };



errDlgkey = findDisplay 46 displayAddEventHandler ["KeyDown",
{
params ["_disp", "_key", "_shift", "_ctrl", "_alt"];
 
 _handled = false;

 if(_key == DIK_Z && _ctrl) then
 {
  call openScriptErrorDlg;

  _handled = true;
 };

 _handled
}];


addMissionEventHandler ["Map",
{
 params ["_mapIsOpened", "_mapIsForced"];

[] spawn
{
 sleep 0.01; // must have delay for visibleMap

 call scriptErrorDlgOnNew;
};

}];

scriptErrorDlgOnNew =
{

_holderDisp = 46;
if(visibleMap) then
{
 _holderDisp = 12;
};

// systemchat format ["_holderDisp %1",_holderDisp];

_prevBut = uinamespace getVariable ["openErrsButton", controlNull];
if(!isnull _prevBut) then
{
 ctrlDelete _prevBut;
};

if(count loggedErrors == 0) exitWith {}; // No errors

if(isnull (findDisplay _holderDisp)) then { systemchat "disp err"; };


_openErrsButton = (findDisplay _holderDisp) ctrlCreate ["RscImgButton", -1, controlNull];
_openErrsButton ctrlSetPosition [safezoneX + 0.01, safezoneY + 0.5 , 0.2, 0.2];
_openErrsButton ctrlSetText ERR_IMAGE;
_openErrsButton ctrlCommit 0;


_openErrsButton buttonSetAction " call openScriptErrorDlg; ";

uinamespace setVariable ["openErrsButton", _openErrsButton];


};

// Clears error button, at mission start
call scriptErrorDlgOnNew;

