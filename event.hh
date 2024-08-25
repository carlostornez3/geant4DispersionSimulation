#ifndef EVENT_HH
#define EVENT_HH
#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"
//#include "g4root.hh"
#include "run.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh"
class MyEventAction:public G4UserEventAction{
public:
MyEventAction(MyRunAction*);
~MyEventAction();
G4Mutex mutex; 
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

private:
};


#endif