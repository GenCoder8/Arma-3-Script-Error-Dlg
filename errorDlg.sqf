
#include "\a3\ui_f\hpp\definedikcodes.inc"
#include "defines.h"


loggedErrors = createhashmap;



openScriptErrorDlg =
{
_display = findDisplay SCRIPT_ERROR_DLG;

if(!isnull _display) exitWith {}; // Already open

createDialog "ScriptErrorDlg";

{

 _y call scriptErrorDlgAdd; 

} foreach loggedErrors;

};

scriptErrorDlgAdd =
{
private _display = findDisplay SCRIPT_ERROR_DLG;
private _tv = _display displayCtrl 1200;



_this params ["_msg","_file","_line","_offset","_filecontent","_trace"];


_pathToFilename =
{
params ["_functionName"];

private _mp = getMissionPath "";

private _filename = _functionName select [ count _mp,  count _functionName ];

_filename
};

_errPosText =
{
 format["%1 at line %2",_functionName call _pathToFilename,_lineNumber]
};


_tvmainindex = _tv tvAdd [[], format ["Error in %1 %2 %3", _msg, _file call _pathToFilename, _line ] ];

for "_i" from (count _trace - 1) to 0 step -1 do
{
 (_trace # _i) params ["_functionName", "_lineNumber", "_scopeName", "_variables"];

// diag_log "-------------------------------------------------------------------------------------------";

 //diag_log format ["%1 at %2", _functionName, _lineNumber];

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


addMissionEventHandler ["ScriptError",
{
 params ["_msg","_file","_line","_offset","_filecontent","_trace"];

_this call logErrorInfo;



}];



logErrorInfo =
{
 params ["_msg","_file","_line","_offset","_filecontent","_trace"];


private _errid = format ["%1%2", _file, _line];

// systemchat _errid;

if(count (loggedErrors getorDefault [_errid,[]]) > 0) exitWith {}; // Already logged

loggedErrors set [_errid, _this];

_this call scriptErrorDlgAdd;


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