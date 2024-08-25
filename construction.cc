#include "construction.hh"
#include <iostream>
#include <tuple>

G4int MyDetectorConstruction::copyNumberSC;
MyDetectorConstruction::MyDetectorConstruction(){
   
DefineMaterialsBC();

}
MyDetectorConstruction::~MyDetectorConstruction(){}

void MyDetectorConstruction::DefineMaterialsBC(){
      //Scintillation parameters are defined according to a plastic scintillator bc-404. Check https://www.phys.ufl.edu/courses/phy4803L/group_I/muon/bicron_bc400-416.pdf for more details.
   /*
    std::ifstream fin("bc404.txt");
    std::vector<G4double> energy;
    std::vector<G4double> fraction;
    std::vector<G4double> rindexSC;
    std::vector<G4double> rindexWorld;
    std::vector<G4double> rindexMylar;
    std::vector<G4double> absSC;
    std::vector<G4double> reflectivity;

    G4double RindexSC=1.58,RindexWorld=1.0,RindexMylar=1.655, AbsSC=160.*cm, Reflectivity=0.9999;
    while(!fin.eof()){
        fin >> wavelength>>lightOutput;
        G4double Energy=1.239841939*eV/((wavelength/1000));
        lightOutput= lightOutput/100;
        energy.push_back(Energy);
        fraction.push_back(lightOutput);
    }
    G4int numberOfEntries=energy.size();
    
    G4int contador = 0;
    while(contador<numberOfEntries){
        rindexSC.push_back(RindexSC);
        rindexWorld.push_back(RindexWorld);
        rindexMylar.push_back(RindexMylar);
        absSC.push_back(AbsSC);
        reflectivity.push_back(Reflectivity);
        contador++;
    }

    G4OpticalParameters::Instance()->SetScintFiniteRiseTime(true);

    */
    G4NistManager *nist = G4NistManager::Instance();

    worldMat = nist->FindOrBuildMaterial("G4_AIR");
    SCMat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    mylarMat = nist->FindOrBuildMaterial("G4_MYLAR");
    ironMat = nist->FindOrBuildMaterial("G4_Fe");
    /*
    mirrorSurface = new G4OpticalSurface("mirrorSurface");
    mirrorSurface->SetType(dielectric_dielectric);
    mirrorSurface->SetFinish(polishedfrontpainted);
    mirrorSurface->SetModel(unified);

    G4MaterialPropertiesTable *mptSC=new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable *mptWorld=new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable *mptMylar=new G4MaterialPropertiesTable();
    G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();

    mptSC->AddProperty("RINDEX",energy, rindexSC,numberOfEntries);
    mptWorld->AddProperty("RINDEX",energy, rindexWorld,numberOfEntries);
    mptSC->AddProperty("SCINTILLATIONCOMPONENT1",energy,fraction,numberOfEntries);
    mptSC->AddConstProperty("SCINTILLATIONYIELD", 10./keV);
    mptSC->AddConstProperty("RESOLUTIONSCALE", 1.);
    mptSC->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 1.8*ns);
    mptSC->AddConstProperty("SCINTILLATIONRISETIME1", 0.7*ns);
    mptSC->AddProperty("ABSLENGTH",energy,absSC,numberOfEntries);
    mptMirror->AddProperty("REFLECTIVITY", energy, reflectivity);;
    mptMylar->AddProperty("RINDEX",energy, rindexMylar,numberOfEntries);
    SCMat->SetMaterialPropertiesTable(mptSC);
    worldMat->SetMaterialPropertiesTable(mptWorld);
    mylarMat->SetMaterialPropertiesTable(mptMylar);
    mirrorSurface->SetMaterialPropertiesTable(mptMirror);*/
}

G4VPhysicalVolume *MyDetectorConstruction::Construct(){
    
   
    //World volume is created

    G4double xWorld = 10.5*m, yWorld= 10.5*m, zWorld = 10.5*m;
    solidWorld= new G4Box("solidWorld",xWorld,yWorld,zWorld);
    logicWorld = new G4LogicalVolume(solidWorld,worldMat, "logicWorld");
    physWorld =new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicWorld,"physWorld",0,false,0,true);





    G4double scLenght = 1.*m, scWidth = 5*cm, scThickness = 5.*cm;
    G4double ironLength=1*m, ironWidth = 1*m, ironThickness = 1*m;
    G4double  ironPosition = 0*cm;
    G4double scPosition = ironPosition+ironThickness*0.5+ 500*cm;
    G4double sensorLength = 6*mm;


    G4Box *solidIron = new G4Box("solidIron", ironLength, ironWidth, ironThickness);
    G4LogicalVolume *logicIron = new G4LogicalVolume(solidIron, ironMat, "logicIron");
    G4VPhysicalVolume *physIron = new G4PVPlacement(0,G4ThreeVector(0.,0.,ironPosition), logicIron, "physIron", logicWorld,false, 1, true);

    

    //rectangularPhysicalVolume(EJ2length, EJ2width, EJ2thickness,detectorLength, 0.*cm, 0.*cm, 488.45*cm,mylarMat,EJMat,physSC, logicDetector, logicDetectorEJ5,"EJ5");
    
    
    G4Box *solidScintillator = new G4Box("solidScintillator",scWidth/2,scLenght/2,scThickness/2);
    logicSC= new G4LogicalVolume(solidScintillator,SCMat, "logicSC");
   // physSC = new G4PVPlacement(0,G4ThreeVector(0.,0.,scPosition), logicSC, "physSC", logicWorld,false, 2, true);

        G4ThreeVector yTrans1(0,scLenght/2,0);
        G4ThreeVector yTrans2(0,-1*scLenght/2,0);
        yRot->rotateY(0*rad);
        innerBox = new G4Box("innerBox",scWidth/2,scLenght/2,scThickness/2);
        externalBox = new G4Box("externalBox",(scWidth/2)+1*mm,(scLenght/2)+1*mm,(scThickness/2)+1*mm);
        sensorBox = new G4Box("sensorBox",sensorLength/2,1.*mm,sensorLength/2);

        externalInner= new G4SubtractionSolid("External-Inner", externalBox, innerBox);
        externalSensor1=new G4SubtractionSolid("External-Inner-Sensor1", externalInner, sensorBox, yRot, yTrans1);
        externalSensor2=new G4SubtractionSolid("External-Inner-Sensor2", externalSensor1, sensorBox, yRot, yTrans2);
        logicMylar= new G4LogicalVolume(externalSensor2,mylarMat, "logicMylar");
        physMylar =new G4PVPlacement(0,G4ThreeVector(0.,0.,scPosition),logicMylar,"physMylar",logicWorld,false,2,true);

        

    
        physSC =new G4PVPlacement(0,G4ThreeVector(0.,0.,scPosition),logicSC,"physSC",logicWorld,false,3,true);
        
        
        G4LogicalVolume *logicSensor = new G4LogicalVolume(sensorBox, worldMat, "logicSensor");
        upperDetector=new G4PVPlacement(0,G4ThreeVector(0.,(scLenght/2)+1*mm,scPosition),logicSensor,"physDetector1",logicWorld,false,4,true);
        lowerDetector =new G4PVPlacement(0,G4ThreeVector(0.,(-1*scLenght/2)-1*mm,scPosition),logicSensor,"physDetector2",logicWorld,false,5,true);
    //fScoringVolume=logicSC;

    return physWorld;
} 



//Predefined method used to tell Geant4 what objects are detectors. 
void MyDetectorConstruction::ConstructSDandField(){
   
  //  MyBarDetector *mybardetector = new MyBarDetector("mybardetector");
   // MyPhotoDetector *myphotodetector = new MyPhotoDetector("myphotodetector");
   
   
   //logicDetector->SetSensitiveDetector(myphotodetector);
   //logicPhotoSensorUpHex->SetSensitiveDetector(myphotodetector);
    
    //logicSC->SetSensitiveDetector(mybardetector);  
}

void MyDetectorConstruction::rectangularPhysicalVolume(G4double length, G4double width, G4double thickness,G4double sensorLength, G4double Xcoordinate, G4double Ycoordinate, G4double Zcoordinate,G4Material* MylarM ,G4Material *material, G4VPhysicalVolume *physicalVolume, G4LogicalVolume *logicalDetector, G4LogicalVolume *logicSC, G4String nombre){
        
        
        G4ThreeVector yTrans1(0,length/2,0);
        G4ThreeVector yTrans2(0,-1*length/2,0);
        yRot->rotateY(0*rad);
        innerBox = new G4Box("innerBox",width/2,length/2,thickness/2);
        externalBox = new G4Box("externalBox",(width/2)+1*mm,(length/2)+1*mm,(thickness/2)+1*mm);
        sensorBox = new G4Box("sensorBox",sensorLength/2,1.*mm,sensorLength/2);

        externalInner= new G4SubtractionSolid("External-Inner", externalBox, innerBox);
        externalSensor1=new G4SubtractionSolid("External-Inner-Sensor1", externalInner, sensorBox, yRot, yTrans1);
        externalSensor2=new G4SubtractionSolid("External-Inner-Sensor2", externalSensor1, sensorBox, yRot, yTrans2);
        logicMylar= new G4LogicalVolume(externalSensor2,MylarM, "logicMylar");
        //G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin",logicMylar,mirrorSurface);
        physMylar =new G4PVPlacement(0,G4ThreeVector(0.,0.,Zcoordinate),logicMylar,"physMylar",logicWorld,false,copyNumberSC+1,true);

        

    
        physicalVolume =new G4PVPlacement(0,G4ThreeVector(0.,0.,Zcoordinate),logicSC,"physSC",logicWorld,false,copyNumberSC+2,true);
        
        
        
        upperDetector=new G4PVPlacement(0,G4ThreeVector(0.,(length/2)+1*mm,Zcoordinate),logicalDetector,"physDetector1",logicWorld,false,copyNumberSC+3,true);
        lowerDetector =new G4PVPlacement(0,G4ThreeVector(0.,(-1*length/2)-1*mm,Zcoordinate),logicalDetector,"physDetector2",logicWorld,false,copyNumberSC+4,true);

        
        G4cout<<nombre<<" "<< "UpperDetector: "<<copyNumberSC+3<<" LowerDetector :"<<copyNumberSC+4<<" PhysicalVolume: "<<copyNumberSC+2<<"PhysMylar: "<<copyNumberSC+1<<G4endl;
        copyNumberSC=copyNumberSC+4;
        
}
