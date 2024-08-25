#include "barSD.hh"

MyBarDetector::MyBarDetector(G4String name):G4VSensitiveDetector(name){

}

MyBarDetector::~MyBarDetector(){

}

G4bool MyBarDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist){
    
    

    G4Track *track=aStep->GetTrack();
    const G4ParticleDefinition* particleDefinition = track->GetDefinition();
    G4String particleName = particleDefinition->GetParticleName();
    G4double parentID=track->GetParentID();
    
    
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    G4StepPoint *preStepPoint=aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint=aStep->GetPostStepPoint();
    G4double time = preStepPoint->GetLocalTime();
   

    G4ThreeVector pos = preStepPoint->GetPosition();
    G4int trackID =  track->GetTrackID();
    

    G4int idEvt =G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    const G4Run* run = G4RunManager::GetRunManager()->GetCurrentRun();
    G4int runID = run->GetRunID();
    G4double Energy = track->GetTotalEnergy();
   track->SetTrackStatus(fStopAndKill);

    man->FillNtupleIColumn(0,0,idEvt); 
    man->FillNtupleIColumn(0,1,runID); 
    man->FillNtupleIColumn(0,2,trackID); 
    man->FillNtupleIColumn(0,3,parentID); 
    man->FillNtupleDColumn(0,4,pos.x()/mm);
    man->FillNtupleDColumn(0,5,pos.y()/mm);
    man->FillNtupleDColumn(0,6,pos.z()/mm);  
    man->FillNtupleDColumn(0,7,Energy/MeV); 
    man->FillNtupleSColumn(0,8,particleName); 
    man->FillNtupleDColumn(0,9,time/ns);    
    man->AddNtupleRow(0); 
        

    




        
    
    

    return true;

}