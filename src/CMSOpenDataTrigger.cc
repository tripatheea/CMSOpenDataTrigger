#include <memory>
#include <iostream>

#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "FWCore/Framework/interface/EDFilter.h"

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


class CMSOpenDataTrigger : public edm::EDFilter {
   public:
      explicit CMSOpenDataTrigger(const edm::ParameterSet&);
      ~CMSOpenDataTrigger();


      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      virtual bool beginRun(edm::Run&, edm::EventSetup const&);

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

	HLTConfigProvider hltConfig_;

   private:

      virtual void setupEventContent(edm::Event& iEvent);

      
      InputTag hltInputTag_;

};




CMSOpenDataTrigger::CMSOpenDataTrigger(const edm::ParameterSet& iConfig) : 
  hltConfig_(),
  hltInputTag_(iConfig.getParameter<edm::InputTag>("HLTInput"))
{
  
}


CMSOpenDataTrigger::~CMSOpenDataTrigger() { }

void CMSOpenDataTrigger::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;
  desc.add < InputTag > ("HLTInput");
}


void CMSOpenDataTrigger::beginJob() {

}


bool CMSOpenDataTrigger::filter(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  setupEventContent(iEvent);
  
  edm::Handle<edm::TriggerResults> trigResults; //our trigger result object
  edm::InputTag trigResultsTag("TriggerResults","","HLT"); //make sure have correct process on MC
  
  iEvent.getByLabel(trigResultsTag,trigResults);
  
  const edm::TriggerNames& trigNames = iEvent.triggerNames(*trigResults);  
  const vector<string> names = trigNames.triggerNames();

  for(unsigned int i = 0; i < names.size(); i++) {
    bool accepted = (* trigResults).accept(trigNames.triggerIndex(names[i]));
    cout << names[i] << ": " << accepted << endl;
  }

  return 0;

}


void CMSOpenDataTrigger::endJob() {

}


bool CMSOpenDataTrigger::beginRun(edm::Run & iRun, edm::EventSetup const & iSetup){
  bool changed = true;
  bool correct = hltConfig_.init(iRun, iSetup, hltInputTag_.process(), changed);
	
  return 0;
}




void CMSOpenDataTrigger::setupEventContent(edm::Event& iEvent) {

}

//define this as a plug-in
DEFINE_FWK_MODULE(CMSOpenDataTrigger);
