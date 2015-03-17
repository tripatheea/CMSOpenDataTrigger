import FWCore.ParameterSet.Config as cms

CMSOpenDataTrigger = cms.EDFilter('CMSOpenDataTrigger', 
			HLTInput = cms.InputTag('TriggerResults', '', 'HLT'),
                        #flags
			debug=cms.untracked.bool(False),
			taggingMode=cms.untracked.bool(False),
			useMETFilters = cms.bool(True),
			useEEBadScFilter = cms.bool(False),
			tagAndProbeStudies = cms.bool(False),
			dropTriggerSelection = cms.bool(False),
			bSelectionInTaggingMode = cms.bool(False),
			nonIsolatedElectronSelection = cms.bool(False),
			invertedConversionSelection = cms.bool(False),
)
