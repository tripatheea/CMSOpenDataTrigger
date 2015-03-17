#include "../interface/CMSOpenDataTrigger.h"

CMSOpenDataTrigger::CMSOpenDataTrigger(const edm::ParameterSet& iConfig) {
  useL1EventSetup = false;
  useL1GtTriggerMenuLite = true;
}


CMSOpenDataTrigger::~CMSOpenDataTrigger() { }


// ------------ method called to produce the data  ------------
void CMSOpenDataTrigger::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {

  int eventNum = iEvent.id().event();
  int runNum = iEvent.id().run();

  cout << "Event Number: " << eventNum << endl;
  cout << "Run Number: " << runNum << endl;
  
  edm::Handle<edm::TriggerResults> trigResults; //our trigger result object
  edm::InputTag trigResultsTag("TriggerResults","","HLT"); //make sure have correct process on MC
  
  //data process=HLT, MC depends, Spring11 is REDIGI311X
  
  iEvent.getByLabel(trigResultsTag,trigResults);
  
  const edm::TriggerNames& trigNames = iEvent.triggerNames(*trigResults);  
  const vector<string> names = trigNames.triggerNames();

  for(unsigned int i = 0; i < names.size(); i++) {
    bool accepted = (* trigResults).accept(trigNames.triggerIndex(names[i]));
    cout << names[i] << ": " << accepted << endl;
  }

}

// ------------ method called once each job just before starting event loop  ------------
void CMSOpenDataTrigger::beginJob() {

}

// ------------ method called once each job just after ending the event loop  ------------
void CMSOpenDataTrigger::endJob() {

}

// ------------ method called when starting to processes a run  ------------
void CMSOpenDataTrigger::beginRun(edm::Run & iRun, edm::EventSetup const & iSetup){

}

// ------------ method called when ending the processing of a run  ------------
void CMSOpenDataTrigger::endRun(edm::Run&, edm::EventSetup const&) {

}

// ------------ method called when starting to processes a luminosity block  ------------
void CMSOpenDataTrigger::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&) {

}

// ------------ method called when ending the processing of a luminosity block  ------------
void CMSOpenDataTrigger::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&) {

}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void CMSOpenDataTrigger::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(CMSOpenDataTrigger);