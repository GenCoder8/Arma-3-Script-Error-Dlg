class CfgPatches {
	class ScriptErrorDlg {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		author[] = {"GC8"};
		authorUrl = "armagc.blogspot.com";

      requiredAddons[] = {};
	};
};

class CfgFunctions
{
 class ScriptErrorDlg
 {
  class InitFns
  {

   class InitDlg
   {
	file = "scriptErrorDlg\modinit.sqf";
	// preStart = 1; // Run on arma start
    preInit = 1; // Run on mission start
    recompile = 1;
   };

  };
 };
};

#include "errorDlg.h"

