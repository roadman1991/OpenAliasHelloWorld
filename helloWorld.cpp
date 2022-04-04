/********************************************************************
 * (C) Copyright 2006 by Autodesk, Inc. All Rights Reserved. By using
 * this code,  you  are  agreeing  to the terms and conditions of the
 * License  Agreement  included  in  the documentation for this code.
 * AUTODESK  MAKES  NO  WARRANTIES,  EXPRESS  OR  IMPLIED,  AS TO THE
 * CORRECTNESS OF THIS CODE OR ANY DERIVATIVE WORKS WHICH INCORPORATE
 * IT.  AUTODESK PROVIDES THE CODE ON AN 'AS-IS' BASIS AND EXPLICITLY
 * DISCLAIMS  ANY  LIABILITY,  INCLUDING CONSEQUENTIAL AND INCIDENTAL
 * DAMAGES  FOR ERRORS, OMISSIONS, AND  OTHER  PROBLEMS IN THE  CODE.
 *
 * Use, duplication,  or disclosure by the U.S. Government is subject
 * to  restrictions  set forth  in FAR 52.227-19 (Commercial Computer
 * Software Restricted Rights) as well as DFAR 252.227-7013(c)(1)(ii)
 * (Rights  in Technical Data and Computer Software),  as applicable.
 *******************************************************************/

 //
 //	OpenAlias plug-in that creates a window with a single menu.  Invoking the
 //	menu item creates a dialog box.  This example illustrates how to mix 
 //	OpenAlias code and Windows(TM) UI functions together.
 //

 // OpenAlias includes
#include <AlUniverse.h>
#include <AlLiveData.h>
#include <AlFunctionHandle.h>
#include <AlFunction.h>
// 
#include <windows.h>

// Standard C libraries
#include "string.h"
#include <stdlib.h>

// Local includes
#include "helloWorld.h"
#include <iostream>
#include <fstream>

void twodarray2csv(std::string array[][3], std::string filename)
{
    std::ofstream myFile;
    myFile.open(filename);

    for (size_t i = 0; i < sizeof(array); ++i)
    {
        for (size_t j = 0; j < 3; ++j)
      {
            if (j < (3 - 1))
            {
                myFile << array[i][j] << ",";
            }
            else if (j == (3 - 1))
            {
                myFile << array[i][j] << "\n";
            }
        }
    }
    myFile.close();


}

static void createMessage()
{
	std::string myArray[2][3] = 
    {
        { "hello", "jack", "dawson" },
        { "servus", "max", "mustermann" }
    };
	twodarray2csv(myArray, "c:/outputfile.csv");

}

//
// Standard plug-in handles and functions
//
static AlFunctionHandle h;
static AlMomentaryFunction hFunc;

extern "C"
PLUGINAPI_DECL int plugin_init(const char* path)
{
	AlUniverse::initialize();
	hFunc.create("HelloWorld Plug-in", createMessage);
	h.create("HelloWorld_Plug", &hFunc);
	h.addToMenu("mp_objtools");

	AlPrintf(kPrompt, "The Dialog Box plug-in is installed on Palette 'Object Edit'");
	return 0;
}

extern "C"
PLUGINAPI_DECL int plugin_exit(void)
{
	h.deleteObject();
	hFunc.deleteObject();
	return 0;
}
