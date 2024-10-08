#include "run.hh"
#include "construction.hh"
#include "G4UIcommand.hh"


 //Creation of histograms
 //#include "G4RootAnalysisManager.hh"

MyRunAction::MyRunAction(){
   G4AnalysisManager *man =G4AnalysisManager::Instance();
       
        man->SetNtupleMerging(true);
        man->SetActivation(true);
        man->CreateNtuple("DispersionInformation","DispersionInformation");
        man->CreateNtupleIColumn("EventId");
        man->CreateNtupleIColumn("RunId");
        man->CreateNtupleIColumn("ParticleId");
        man->CreateNtupleIColumn("ParentId");
        man->CreateNtupleDColumn("fX");
        man->CreateNtupleDColumn("fY");
        man->CreateNtupleDColumn("fZ");  
        man->CreateNtupleDColumn("fEnergy");
        man->CreateNtupleSColumn("SParticleName"); 
        man->CreateNtupleDColumn("fLocalTime");
        man->FinishNtuple(0);
    fileName = "output";
    fMessenger = new G4GenericMessenger(this, "/file/", "Outputfile");
    fMessenger->DeclareProperty("fileName", fileName, "Set the name of the output root file");

        




   

}
MyRunAction::~MyRunAction(){

}
void MyRunAction::BeginOfRunAction(const G4Run * run){
    G4AnalysisManager *man =G4AnalysisManager::Instance();

    G4int runID = run->GetRunID();
    std::stringstream strRunID;
    strRunID<<runID;

    file = strRunID.str() +"_"+ fileName +".root";
    man->OpenFile(file);


}
void MyRunAction::EndOfRunAction(const G4Run *){
    G4AnalysisManager *man =G4AnalysisManager::Instance();

    

    man->Write();

    man->CloseFile();
}




        
        
       
        

        
        

        


        

        
       
       
       
        


