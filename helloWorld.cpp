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
#include <AlDagNode.h>
#include <AlSurfaceNode.h>
#include <AlSurface.h>
#include <AlObject.h>
#include <AlShader.h>
#include <AlLayer.h>

// 
#include <windows.h>

// Standard C libraries
#include "string.h"
#include <stdlib.h>

// Local includes
#include "helloWorld.h"
#include <iostream>
#include <fstream>
#include <list>
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

void doIt()
{
		
		AlPrintf(kPrompt, "startin do it");
		std::ofstream myFile;
		myFile.open("c:/outputfile.csv");
		const char* currentStage = AlUniverse::currentStage();
		const char* stageWireFileName = AlUniverse::stageWireFileName(currentStage);
		//AlLayer *layer = AlUniverse::firstLayer();
		AlDagNode *dagNode = AlUniverse::firstDagNode();
		AlLayer *layer;
		AlShader *shader;
		AlSurfaceNode *surface_node;
		AlSurface *surface;
		std::list<std::list<const char*>> surfaces;
		std::list<const char*> row;  //empty list
		const char* surface_name;
		const char* layer_name;
		const char* node_name;
		const char* shader_name;

	//while (dagNode)
	for (int i = 0; i < 3; i++)
	{
		AlPrintf(kPrompt, "loop");
		/*if( surface_node = dagNode->asSurfaceNodePtr())
		{
			//surface_name = surface_node->name();
			//row.push_back(surface_name);
			layer = dagNode->layer();
			layer_name = layer->name();
			//row.push_back(layer_name);
			AlPrintf(kPrompt, "loop");
			//node_name = dagNode->name();
			//row.push_back(node_name);
			//surface = surface_node->surface();
			//shader = surface->firstShader();
			//shader_name = shader->name();
			//surfaces.push_back(row);
			//myFile << surface_name << "," << layer_name << "," << node_name << "," << shader_name << "\n";
		}*/
		//row.clear();
	}
	for (int i = 0; i < 3; i++)
	{
		AlPrintf(kPrompt, "2ndforloop");
		myFile << "halloWelt" << ",";
	}
	
	
	
	//get len of surfaces
	
	// declare array n_rows = len of surfaces, n_cols = n_features (name, mat...)
	
	// create csv
	myFile.close();
	
}
static void createMessage()
{
	
	AlPrintf(kPrompt, "Calling Hello World");
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
