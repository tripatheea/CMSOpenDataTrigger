#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/HLTGlobalStatus.h"
#include "DataFormats/Provenance/interface/ParameterSetID.h"


#include "DataFormats/Common/interface/TriggerResults.h"

//
// class declaration
//

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

      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
CMSOpenDataTrigger::CMSOpenDataTrigger(const edm::ParameterSet& iConfig)
{
   //register your products
/* Examples
   produces<ExampleData2>();

   //if do put with a label
   produces<ExampleData2>("label");
 
   //if you want to put into the Run
   produces<ExampleData2,InRun>();
*/
   //now do what ever other initialization is needed
  
}


CMSOpenDataTrigger::~CMSOpenDataTrigger()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void CMSOpenDataTrigger::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  using namespace std;

  int eventNum = iEvent.id().event();
  int runNum = iEvent.id().run();

  cout << "Event Number: " << eventNum << endl;
  cout << "Run Number: " << runNum << endl;

  edm::Handle<edm::TriggerResults> trigger_results_collection;
  iEvent.getByLabel("TriggerResults", trigger_results_collection);
  
  cout << "Trigger Results Collection Size: " << trigger_results_collection->size() << endl;

  edm::ParameterSetID pset_id = trigger_results_collection->parameterSetID();
  
  edm::ParameterSet pset = edm::ParameterSet();
  pset.setID(pset_id);

  cout << pset_id << endl; 
  

  // You do this on the parameter set not on the parameter ID.
  //vector<string> trigger_names = parameter_set_id.getParameter<Strings>("@trigger_paths");

  //for(unsigned int j = 0; j < trigger_names.size(); j++) {
  //  cout << trigger_names[j] << endl;
  //}
  
  for (unsigned int i = 0; i < trigger_results_collection->size(); i++) {
    const edm::HLTPathStatus trigger = (* trigger_results_collection)[i];
    //cout << trigger->getTriggerNames() << endl;
  }
  
}

// ------------ method called once each job just before starting event loop  ------------
void 
CMSOpenDataTrigger::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CMSOpenDataTrigger::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
CMSOpenDataTrigger::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
CMSOpenDataTrigger::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
CMSOpenDataTrigger::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
CMSOpenDataTrigger::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
CMSOpenDataTrigger::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(CMSOpenDataTrigger);
