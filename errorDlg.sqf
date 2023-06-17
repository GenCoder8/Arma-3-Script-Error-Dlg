
#include "\a3\ui_f\hpp\definedikcodes.inc"
#include "defines.h"
#include "resources.h"


loggedErrors = [];

if(profilenamespace getVariable ["errDlgEditorPath",""] == "") then
{
profilenamespace setVariable ["errDlgEditorPath","C:\\Program Files\\Notepad++\\notepad++.exe"];
};
if(profilenamespace getVariable ["errDlgEditorArgs",""] == "") then
{
profilenamespace setVariable ["errDlgEditorArgs","%1 -n%2"];
};

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


private _gotoButon = _display displayCtrl 1602;

_gotoButon ctrlEnable false;
_gotoButon ctrlShow false;

if(("ArmaTools" callExtension "isLoaded") == "true") then
{
 _gotoButon ctrlShow true;
};


_tvCtrl ctrlAddEventHandler ["TreeSelChanged",
{
params ["_tvCtrl","_path"];

private _display = findDisplay SCRIPT_ERROR_DLG;

private _gotoButon = _display displayCtrl 1602;

_gotoButon ctrlEnable false;

private _filename = _tvCtrl tvData _path;
private _line = _tvCtrl tvValue _path;

if(_filename != "") then
{
 _gotoButon ctrlEnable true;
};

//systemchat format ["_line %1",  _line];

}];

/*
_tvCtrl ctrlAddEventHandler ["TreeDblClick", 
{ 
params ["_tvCtrl","_path"];

hint str (_tvCtrl tvData _path); 

}];
*/

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

_gotoFile =
{
params ["_path","_file","_line"];
_tv tvSetData [_path, _file];
_tv tvSetValue [_path, _line];

};

private _tvmainindex = _tv tvAdd [[], _emsgStart ];

[[_tvmainindex],_file,_line] call _gotoFile;

for "_i" from (count _trace - 1) to 0 step -1 do
{
 (_trace # _i) params ["_file", "_line", "_scopeName", "_variables"];

// diag_log "-------------------------------------------------------------------------------------------";

//diag_log format [">>>>>>>>!!!!>>>>>>>>>> %1 %2", _file, _line, (_trace # _i)];

private _tvsubindex = _tv tvAdd [[_tvmainindex], format["%1", call _errPosText] ];

[[_tvmainindex,_tvsubindex],_file,_line] call _gotoFile;


{
private _varname = _x;
private _varvalue = "nil";
private _varType = "";

if(!isnil "_y") then
{
_varType = typename _y;

switch (_varType) do
{
 case "CODE": { _varvalue = "Code"; };
 case "STRING": {  _varvalue = '"' + _varvalue + '"'; };
 default { _varvalue = _y; };
};

};


private _index = _tv tvAdd [[_tvmainindex,_tvsubindex], format ["%1 %2 = %3",_varType,_varname,_varvalue] ];


//_tv tvSetData [[_tvmainindex,_tvsubindex,_index], "TEEEEEEEEEEEST!"];


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

_this call logErrorInfoScript;


[] spawn
{
sleep 0.2;

diag_log "allCutLayers:";
{
 diag_log format ["layer: %1", _x];
} foreach allCutLayers;

};

}];



logErrorInfoScript =
{
 params ["_msg","_file","_line","_offset","_filecontent","_trace"];


private _errid = format ["%1_%2", _file, _line];


if(count _file == 0) then // For console errors
{
 private _code = _filecontent;

 if(count _code > 256) then { _code = _code select [0,256]; }; // Some limit 

 _errid = format ["%1%2", _code, _line];
};

[_errid, _this] call logErrorInfoBase;


};

logErrorInfoCustom =
{
 params ["_msg"];

private _errid = _msg;

[_errid,[_msg,"",0, 0, "", diag_stacktrace]] call logErrorInfoBase;

};

logErrorInfoBase =
{
 params ["_errid","_errInfo"];

if((loggedErrors findif { (_x # 0) == _errid }) >= 0) exitWith {}; // Already logged


private _earr = [_errid] + _errInfo;



loggedErrors pushback _earr;


_earr call scriptErrorDlgAdd;

call scriptErrorDlgOnNew;

};


scriptErrorDlgGotoLine =
{
params ["_file"];

private _display = findDisplay SCRIPT_ERROR_DLG;

private _tvCtrl = _display displayCtrl 1200;

private _selPath = tvCurSel _tvCtrl;

private _filename = _tvCtrl tvData _selPath;
private _line = _tvCtrl tvValue _selPath;



// systemchat format ["_line '%1' %2",  _filename, _line];



//_runLine = format ["C:\\Program Files\\Notepad++\\notepad++.exe %1 -n%2", _filename, (str _line)];

private _editorPath = profilenamespace getVariable "errDlgEditorPath";
private _editorArgs = profilenamespace getVariable "errDlgEditorArgs";

systemchat format ["_editorPath '%1' ", _editorPath];
systemchat format ["_editorArgs '%1' ", _editorArgs];

private _argLine = format [_editorArgs,  _filename , _line ];

systemchat format ["args set '%1' ", _argLine];

private _ret = "ArmaTools" callExtension ["ExecuteFile", [_editorPath, _argLine] ];

systemchat (str _ret);



// ["C:\\Program Files\\Notepad++\\notepad++.exe", _filename, "-n" + (str _line)]

};


openScriptErrSettings =
{
createDialog "SEDlgSettings";

private _display = findDisplay SCRIPT_ERROR_DLG_SET;

private _editorPath = _display displayCtrl 1400;
private _editorArgs = _display displayCtrl 1401;

_editorPath ctrlSetText (profilenamespace getVariable ["errDlgEditorPath",""]);

_editorArgs ctrlSetText (profilenamespace getVariable ["errDlgEditorArgs",""]);

};



closeScriptErrSettings =
{

private _display = findDisplay SCRIPT_ERROR_DLG_SET;

private _editorPath = _display displayCtrl 1400;
private _editorArgs = _display displayCtrl 1401;

profilenamespace setVariable ["errDlgEditorPath",ctrlText _editorPath];

profilenamespace setVariable ["errDlgEditorArgs",ctrlText _editorArgs];


closeDialog 0;

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

