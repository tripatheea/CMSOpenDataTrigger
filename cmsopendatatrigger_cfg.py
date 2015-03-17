import FWCore.ParameterSet.Config as cms 
import FWCore.PythonUtilities.LumiList as LumiList 
import FWCore.Utilities.FileUtils as FileUtils

from FWCore.MessageLogger.MessageLogger_cfi import *

process = cms.Process("OPENDATA")
#process.load("Configuration.StandardSequences.Geometry_cff")
#process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

#process.load("FWCore.MessageService.MessageLogger_cfi")

process.GlobalTag.globaltag = 'GR_R_42_V25::All'


process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'root://eospublic.cern.ch//eos/opendata/cms/Run2010B/Jet/AOD/Apr21ReReco-v1/0000/00052C5A-EF70-E011-B43F-00266CF32A00.root'
    )
)

# Process only those luminosity sections in which runs are considered good and should be processed.
#goodJSON = 'Cert_136033-149442_7TeV_Apr21ReReco_Collisions10_JSON_v2.txt' 
#myLumis = LumiList.LumiList(filename = goodJSON).getCMSSWString().split(',') 
#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange() 
#process.source.lumisToProcess.extend(myLumis)


process.myFilterLabel = cms.EDFilter('CMSOpenDataTrigger')


process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('myOutputFile.root')
)

# Change this to set the maximum number of events to process
# -1 means all of them
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(2))

  
process.p = cms.Path(process.myFilterLabel)

process.e = cms.EndPath(process.out)
