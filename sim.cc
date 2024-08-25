#include <iostream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4MTRunManager.hh"
#include "G4UIExecutive.hh"
#include "construction.hh"
#include "physics.hh"
#include "action.hh"
#include "G4UIcommand.hh"
#include "G4RunManagerFactory.hh"
#include "G4String.hh"
#include "QGSP_BERT.hh"
#include "G4DecayPhysics.hh"
#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
//#include "G4Random.hh"
#include <ctime>



int main(int argc,char** argv){

    G4long seed = static_cast<G4long>(time(0));

    // Establecer la semilla aleatoria
    G4Random::setTheSeed(seed);
    G4cout<<"The seed is: "<< seed<<G4endl;
    G4UIExecutive *ui=nullptr;
    
    #ifdef G4MULTITHREADED
        G4MTRunManager *runManager=new G4MTRunManager();
    #else
        G4RunManager *runManager=new G4RunManager();
    #endif
 
    
        runManager->SetUserInitialization(new MyDetectorConstruction());
       
        runManager->SetUserInitialization(new MyPhysicsList());
        runManager->SetUserInitialization(new MyActionInitialization());
        G4VModularPhysicsList * physics = new QGSP_BERT();
        //physics->RegisterPhysics(new G4DecayPhysics());
        //physics->RegisterPhysics(new G4EmStandardPhysics());
       // physics->RegisterPhysics(new G4OpticalPhysics());
        runManager->SetUserInitialization(physics);
    
        if(argc==1){
            ui = new G4UIExecutive(argc,argv);
            
        }
        

        G4VisManager *visManager = new G4VisExecutive();
        visManager->Initialize();
        G4UImanager *UImanager = G4UImanager::GetUIpointer();
        if(ui){
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        }else{
            G4String command="/control/execute ";
            G4String fileName = argv[1];
            UImanager->ApplyCommand(command+fileName);
            
        }
        delete ui;
        delete visManager;

    
   
    //delete ui;
    
    delete runManager;
    return 0;
}