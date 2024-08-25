#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
//#include "G4GenericAnalysisManager.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
//#include "g4root.hh"
#include "G4AnalysisManager.hh"
//using G4AnalysisManager = G4GenericAnalysisManager;

class MyRunAction:public G4UserRunAction{
public:
    MyRunAction();
    ~MyRunAction();
    virtual void BeginOfRunAction(const G4Run *);
    virtual void EndOfRunAction(const G4Run *);
};
#endif