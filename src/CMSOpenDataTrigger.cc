#include <memory>
#include <iostream>

#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"



#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/HLTGlobalStatus.h"
#include "DataFormats/Provenance/interface/ParameterSetID.h"


#include "DataFormats/Common/interface/TriggerResults.h"


#include "FWCore/ServiceRegistry/interface/Service.h"

#include "FWCore/Common/interface/TriggerNames.h"

#include "FWCore/Common/interface/TriggerResultsByName.h"


#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

using namespace std;
using namespace edm;
using namespace trigger;


class CMSOpenDataTrigger : public edm::EDProducer {
   public:
      explicit CMSOpenDataTrigger(const edm::ParameterSet&);
      ~CMSOpenDataTrigger();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void endRun(edm::Run&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      
      bool triggerFired(const std::string& triggerWildCard, const edm::TriggerResults& triggerResults);
      unsigned int findTrigger(const std::string& triggerWildCard);

      HLTConfigProvider hltConfig_;      
      InputTag hltInputTag_;

};




CMSOpenDataTrigger::CMSOpenDataTrigger(const edm::ParameterSet& iConfig) : 
	hltConfig_() ,
	hltInputTag_("TriggerResults","","HLT") 
{
  
}


CMSOpenDataTrigger::~CMSOpenDataTrigger() { }

void CMSOpenDataTrigger::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;
}


void CMSOpenDataTrigger::beginJob() {

}

void CMSOpenDataTrigger::endJob() {

}


void CMSOpenDataTrigger::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {

  edm::Handle<edm::TriggerResults> trigResults; 

  iEvent.getByLabel(hltInputTag_, trigResults);

  const vector<string> triggerNames = hltConfig_.triggerNames();
  
  for (unsigned int i = 0; i < triggerNames.size(); i++) {
    const string name = triggerNames[i];
    pair<int, int> prescale = hltConfig_.prescaleValues(iEvent, iSetup, name);
    bool fired = triggerFired(name, ( * trigResults));

    cout << (i + 1) << ") " << name << "; " << prescale.first << ", " << prescale.second << "; " << fired << endl;
  }


  /*
  // Alternate way to get triggers. 
  // This is limited in scope; for example, it's extremely difficult to find prescale values this way. 
  // So use this only for testing stuff.
  
  const edm::TriggerNames& trigNames = iEvent.triggerNames(*trigResults);  
  const vector<string> names = trigNames.triggerNames();

  for(unsigned int i = 0; i < names.size(); i++) {
    bool accepted = (* trigResults).accept(trigNames.triggerIndex(names[i]));
    cout << names[i] << ": " << accepted << endl;
  }
  */


}


void CMSOpenDataTrigger::beginRun(edm::Run & iRun, edm::EventSetup const & iSetup){
  bool changed = true;
  if ( hltConfig_.init(iRun, iSetup, hltInputTag_.process(), changed) ) {
    // if init returns TRUE, initialisation has succeeded!
    edm::LogInfo("TopPairElectronPlusJetsSelectionFilter") << "HLT config with process name "
				<< hltInputTag_.process() << " successfully extracted";
  }
  else {
    edm::LogError("TopPairElectronPlusJetsSelectionFilter_Error")
				<< "Error! HLT config extraction with process name " << hltInputTag_.process() << " failed";
  }

}

void CMSOpenDataTrigger::endRun(edm::Run&, edm::EventSetup const&) {

}

void CMSOpenDataTrigger::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&) {

}

void CMSOpenDataTrigger::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&) {

}

bool CMSOpenDataTrigger::triggerFired(const std::string& triggerWildCard, const edm::TriggerResults& triggerResults) {
  bool fired = false;
  unsigned int index = findTrigger(triggerWildCard);

  if (index < triggerResults.size()) {
    if (triggerResults.accept(index)) {
      fired = true;
    }
  }

  return fired;

}

unsigned int CMSOpenDataTrigger::findTrigger(const std::string& triggerWildCard) {
  const std::vector<std::string>& triggers = hltConfig_.triggerNames();
  unsigned int found = 9999;

  size_t length = triggerWildCard.size();
  for (unsigned int index = 0; index < triggers.size(); ++index) {
    if (length <= triggers[index].size() && triggerWildCard == triggers[index].substr(0, length)) {
      found = index;
      break;
    }
  }

  return found;
}




//define this as a plug-in
DEFINE_FWK_MODULE(CMSOpenDataTrigger);
