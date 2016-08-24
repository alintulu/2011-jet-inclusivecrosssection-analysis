# 2011-jet-inclusivecrosssection-ntupleproduction
Validation code for 2011 jet dataset, based on inclusive jet cross section - step 1: ntuple production

***Work in progress***

## TODO list
* Provide links to the data and Monte Carlo tuples in the OpenData portal
(On LXPLUS: ```/afs/cern.ch/user/m/mhaapale/work/public/Jet-Tuples-Summer2016```)
* Change paths of the input files
* Analyse Data and Monte Carlo 
* Prettier plots
* Code was tested in ROOT 6, while the virtual machine runs ROOT 5

## Instructions 

* Clone this repository
* Download jet tuples
* Run analysis
```
cd jetphys/
root mk_runFullAnalysis.C
```

## Datasets used:
* Data
  ```
  /Jet/Run2011A-12Oct2013-v1/AOD 
  ```

* Monte Carlo
  ```
  /QCD_Pt-15to30_TuneZ2_7TeV_pythia6/Summer11LegDR-PU_S13_START53_LV6-v1/AODSIM
  /QCD_Pt-30to50_TuneZ2_7TeV_pythia6/Summer11LegDR-PU_S13_START53_LV6-v1/AODSIM
  /QCD_Pt-50to80_TuneZ2_7TeV_pythia6/Summer11LegDR-PU_S13_START53_LV6-v1/AODSIM
  /QCD_Pt-80to120_TuneZ2_7TeV_pythia6/Summer11LegDR-PU_S13_START53_LV6-v1/AODSIM
  /QCD_Pt-120to170_TuneZ2_7TeV_pythia6/Summer11LegDR-PU_S13_START53_LV6-v1/AODSIM
  /QCD_Pt-170to300_TuneZ2_7TeV_pythia6/Summer11LegDR-PU_S13_START53_LV6-v1/AODSIM
  /QCD_Pt-300to470_TuneZ2_7TeV_pythia6/Summer11LegDR-PU_S13_START53_LV6-v1/AODSIM
  /QCD_Pt-470to600_TuneZ2_7TeV_pythia6/Summer11LegDR-PU_S13_START53_LV6-v1/AODSIM
  /QCD_Pt-600to800_TuneZ2_7TeV_pythia6/Summer11LegDR-PU_S13_START53_LV6-v1/AODSIM
  /QCD_Pt-800to1000_TuneZ2_7TeV_pythia6/Summer11LegDR-PU_S13_START53_LV6-v1/AODSIM
  ```
