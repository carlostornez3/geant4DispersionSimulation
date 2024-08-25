#include "generator.hh"
MyPrimaryGenerator::MyPrimaryGenerator(){
    
    particleSource = new G4GeneralParticleSource(); 
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    
    G4ParticleDefinition *particle = particleTable->FindParticle(13);//13 corresponds to a muon in Geant4 database   
    
}
MyPrimaryGenerator::~MyPrimaryGenerator(){
    delete particleSource;

}
void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent){
    particleSource->GeneratePrimaryVertex(anEvent);
    
}

    
