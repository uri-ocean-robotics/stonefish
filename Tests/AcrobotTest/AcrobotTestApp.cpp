//
//  AcrobotTestApp.cpp
//  Stonefish
//
//  Created by Patryk Cieslak on 03/03/2014.
//  Copyright (c) 2014 Patryk Cieslak. All rights reserved.
//

#include "AcrobotTestApp.h"

#include "OpenGLTrackball.h"
#include "DCMotor.h"
#include "NativeDialog.h"

AcrobotTestApp::AcrobotTestApp(int width, int height, AcrobotTestManager* sim) : SimulationApp("Acrobot Test", width, height, sim)
{
}

void AcrobotTestApp::DoHUD()
{
    SimulationApp::DoHUD();
    
    char buffer[128];
    GLfloat white[4] = {1.f,1.f,1.f,1.f};

    ui_id label1;
    label1.owner = 1;
    label1.item = 0;
    label1.index = 0;
    
    //sprintf(buffer, "Motor Torque: %1.3lf [Nm]", ((DCMotor*)getSimulationManager()->getActuator(0))->getTorque());
    //getHUD()->DoLabel(label1, 90, getWindowHeight()-50, white, buffer);
    
    ui_id plot;
    plot.owner = 1;
    plot.item = 0;
    plot.index = 0;
    
    //IMGUI::getInstance()->DoXYPlot(plot, getWindowWidth()-310, getWindowHeight() - 240, 300, 200, getSimulationManager()->getSensor(1), 0, getSimulationManager()->getSensor(1), 1, "Arm1");
    
    std::vector<unsigned short> dims;
    dims.push_back(0);
    dims.push_back(1);
 
    if(IMGUI::getInstance()->DoTimePlot(plot, getWindowWidth()-310, 10, 300, 200, (SimpleSensor*)getSimulationManager()->getSensor("Encoder1"), dims, "Arm1"))
    {
        StopSimulation();
        
        NativeDialog* openDialog = new NativeDialog(DialogType_Save, "Save plot data...", "txt");
        openDialog->Show();
     
        char* pathToFile;
        if(openDialog->GetInput(&pathToFile) == DialogResult_OK)
        {
			SimpleSensor* sensor = (SimpleSensor*)getSimulationManager()->getSensor("Encoder1"); 
			sensor->SaveMeasurementsToTextFile(pathToFile);
        }
     
        delete [] pathToFile;
        delete openDialog;
        
        ResumeSimulation();
     }
}