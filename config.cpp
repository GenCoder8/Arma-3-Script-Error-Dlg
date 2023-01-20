class CfgPatches {
	class ErrorDlg {
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
 class ErrorDlg
 {
  class InitFns
  {

   class InitDlg
   {
	file = "errorDlg\modinit.sqf";
	preStart = 1; // Run on arma start
    preInit = 1; // Run on mission start
    recompile = 1;
   };

  };
 };
};

#include "errorDlg.h"

