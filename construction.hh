#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include <assert.h>
#include <cmath>
#include "G4TwoVector.hh"
#include "G4PhysicalConstants.hh"
#include "G4ExtrudedSolid.hh"
#include "G4Polyhedra.hh"
#include "G4TessellatedSolid.hh"
#include "G4OpticalPhysics.hh"
#include "G4GenericMessenger.hh"
#include "G4SubtractionSolid.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4String.hh"
#include <tuple>
#include "G4SDManager.hh"
#include "barSD.hh"


class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();
    G4LogicalVolume *GetScoringVolume() const{return fScoringVolume;}
    void rectangularPhysicalVolume(G4double length, G4double width, G4double thickness,G4double sensorLength, G4double Xcoordinate, G4double Ycoordinate, G4double Zcoordinate,G4Material* MylarM ,G4Material *material, G4VPhysicalVolume *physicalVolume, G4LogicalVolume *logicalDetector, G4LogicalVolume *logicSC, G4String nombre);
    
        

    virtual G4VPhysicalVolume *Construct();
    
    static G4int copyNumberSC;

private: 
    G4LogicalVolume *logicDetector;
    G4GenericMessenger *fMessenger;
    G4LogicalVolume *fScoringVolume;
   
    G4VPhysicalVolume *physWorld,*physSC,*physDetectorX1,*physDetectorX2,*physDetector,*physMylar,*physDetectorY1,*physDetectorY2,*physDetector1,*physDetector2, *upperDetector, *lowerDetector;
    virtual void ConstructSDandField();
    
    
    G4Box *solidWorld,*solidDetector, *innerBox,*externalBox,*sensorBox,*solidDetector2;
    G4LogicalVolume *logicWorld,*logicSC, *logicMylar;
   
    
    G4VSolid* xtru, *xtruExternal, *xtruInner;
    G4SubtractionSolid  *externalInner, *externalSensor1, *externalSensor2,*externalSensor;

    G4VPhysicalVolume *physX1,*physY1, *physBC, *physCZ, *physFerm, *physEJS1, *physEJS2, *physEJS0, *physAcorde, *physUnamEJ, *physX2;

    G4RotationMatrix* yRot = new G4RotationMatrix;

    G4Material *worldMat,*SCMat, *mylarMat,*air,*BCMat, *EJMat,*ironMat;
    G4Material *poly;
    G4Material *aluminium;
    G4Material* Freon;
    G4Material *copper;
    void DefineMaterialsBC();
    G4double ironBeamDistance, ironPlasticDistance, ironThickness;
    
};
#endif
