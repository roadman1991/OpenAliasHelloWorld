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
AlUniverse::AlFileType
getFileType(int format)
{
    switch (format)
    {
    case 9:
        return AlUniverse::kNx;
    case 8:
        return AlUniverse::kVdais;
    case 7: 
        return AlUniverse::kJamais;
    case 6:
        return AlUniverse::kC4x;
    case 5: 
        return AlUniverse::kDxf;
    case 4: 
        return AlUniverse::kJT;
    case 3:
        return AlUniverse::kEdf;
    case 2:
        return AlUniverse::kCatiaV5;
    case 1:
        return AlUniverse::kIges;
    case 0:
    default:
        break;
    }
    
    return AlUniverse::kWire;
}

// See saveLayers.scm to match the AlFileTypes to
// the number in the UI.
char*
getFileExtension(int format)
{
    switch (format)
    {
    case 9:
        return "nx";
    case 8:
        return "vdais";
    case 7: 
        return "jamais";
    case 6:
        return "c4x";
    case 5: 
        return "dxf";
    case 4: 
        return "jt";
    case 3:
        return "edf";
    case 2:
        return "catV5";
    case 1:
        return "igs";
    case 0:
    default:
        break;
    }
    
    return "wire";
}

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

void doIt()
{
		AlLayer *layer = AlUniverse::firstLayer();
		AlDagNode *dagNode = AlUniverse::firstDagNode();
		std::list<AlDagNode> listDagNodes;
	while (*dagNode)
	{
		listDagNodes.insert(dagNode);
		dagNode = dagNode::nextNode();
		//Either we save all layers or the layer must be visible
		//or the layer must be a construction layer.
		/*if(save || !layer->invisible() || 
			AlLayerExt::isConstructionLayer(layer->number()))
		{
			if (pickedOnly && !layer->isPicked())
			{
				layer = AlUniverse::nextLayer(layer);
				continue;
			}

			//Clear the pick list and select only the nodes
			//in this particular layer.
			AlLayerExt::pickNodesOnLayer(layer->number());
	
			//The name of the file is the file name without .wire
			//extension concatenated with the layer name.
			sprintf(fileName, "%s_%s.%s", fileWithoutWire, layer->name(), getFileExtension(format));
			sprintf(buffer, "%s\\%s", dirName, fileName);

			//Verify that fileName does not already exist and if so whether 
			//it should be overwritten. Otherwise prompt the user to enter
			//a new name instead of fileName.
			if(!overwriteAll)
				rc = AlLayerExt::verifyFileName(buffer, fileName);

			if(rc == FileDoesNotExist || rc == DialogBoxYES || rc == DialogBoxYESALL)
			{
				//Save the nodes in this layer to the location and
				//filename specified by buffer.
                if(sSuccess != AlUniverseExt::store(buffer, true, getFileType(format) ) )
 				//if(sSuccess != AlUniverse::storeActive(buffer))
				{
					fprintf(stderr, "^G\n");
					AlPrintf(kPrompt, "*** ERROR: Could not save layer %s.\n", buffer);
				}

				//Set overwrite flag so that we do not query user for
				//overwrite permissions needlessly.
				if(rc == DialogBoxYESALL)
					overwriteAll = TRUE;
			}
			else if(rc == DialogBoxNO)
				AlPrintf(kPrompt, "*** Did not save layer %s.\n", buffer);
			else if(rc == DialogBoxCANCEL)
			{
				AlPrintf(kPrompt, "*** Save layers aborted.\n");
				break;
			}
		}

		//Proceed to the next layer in the scene.
		layer = AlUniverse::nextLayer(layer);*/
	}
}
static void createMessage()
{
	std::string myArray[2][3] = 
    {
        { "hello", "jack", "dawson" },
        { "servus", "max", "mustermann" }
    };
	twodarray2csv(myArray, "c:/outputfile.csv");
	doIt();

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

	//Initialize default values in the option box.
	char *dirScm = makeAltPath( path, "scm" );
	AlInvokeSchemeFile( "saveLayers_init.scm", dirScm );


	h.setOptionBox( "saveLayers.scm", "save_layers.options", dirScm );
		//	Then the scheme file and the icon images would be loaded from
	//	the same path as the plugin rather than from the standard locations
	h.setIconPath( makeAltPath( path, NULL ) );

	// Indicate which menu to add the plugin to. addToMenu()
	// adds the plugin to the bottom of the menu, while
	// appendToMenu() will add it to the top of the menu.
	h.addToMenu( "ma_layers" );

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
