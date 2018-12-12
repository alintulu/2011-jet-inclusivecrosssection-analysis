# 2011-jet-inclusivecrosssection-analysis
Validation code for 2011 jet dataset, based on inclusive jet cross section - step 2: analysis

## Prerequisites

  * This script only works with [ROOT6](https://root.cern.ch/downloading-root)
  * Before you run anything you need to 1) while in directory [jetphys](jetphys) create an empty directory called plots 2) while in directory [code](jetphys/code) checkout and compile the tool RooUnfold which will help you unfold the data with the macro [dagostini.C](jetphys/code/dagostini.C)

  1. Create directory plots
  
    $ cd jetphys
    $ mkdir plots
    
  2. Checkout and compile RooUnfold
  
    $ cd code
    $ svn co https://svnsrv.desy.de/public/unfolding/RooUnfold/trunk RooUnfold
    $ cd RooUnfold
    $ make
    $ cd ..
    
  
  ## Running the analysis
  
  1. Running full analysis
  
  If you want to run the code with data, change nothing. If you want to run the code with MC, go to [settings.h line 25](https://github.com/alintulu/2011-jet-inclusivecrosssection-analysis/blob/master/jetphys/code/settings.h#L25) and change 

  ```
  std::string _jp_type = "DATA"
  ```
  to
  ```
  std::string _jp_type = "MC"
  ```
  When you are happy with the settings, while in the directory [code](jetphys/code) run

  ```
  $ root -l -b -q mk_runFullAnalysis.C
  ```
  2. Run parts of the analysis
  
  Either comment out the parts you don't want to run in [mk_runFullAnalysis.C](jetphys/code/mk_runFullAnalysis.C) or simply choose one make file (exempel [mk_normalizeHistos.C](jetphys/code/mk_normalizeHistos.C))
  
  ```
  root -l -b -q mk_normalizeHistos.C
  ```
  
  If you want to run [drawPlots.C](jetphys/code/drawPlots.C) independently you need to remove `//` from [line 14 and 15](https://github.com/alintulu/2011-jet-inclusivecrosssection-analysis/blob/master/jetphys/code/drawPlots.C#L14-L15). When you do this you make sure that two necessary files are included in the script.

## Datasets used

* For data
  ```
  /Jet/Run2011A-12Oct2013-v1/AOD 
  ```

* For Monte Carlo
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
