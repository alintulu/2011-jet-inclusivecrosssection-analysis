# 2011-jet-inclusivecrosssection-analysis
Validation code for 2011 jet dataset, based on inclusive jet cross section - step 2: analysis

## Prerequisites

  * This script only works with [ROOT6](https://root.cern.ch/downloading-root)
  * Before you run anything you need to 1) while in directory [jetphys](jetphys) create an empty directory called plots, this is where the ouput plots will go. 2) While in directory [code](jetphys/code) checkout and build the framework [RooUnfold](http://hepunx.rl.ac.uk/~adye/software/unfold/RooUnfold.html) which will help you unfold the data with the macro [dagostini.C](jetphys/code/dagostini.C)

  1. Create directory plots
  ```
    $ cd jetphys
    $ mkdir plots
  ```
  2. Checkout and build RooUnfold
  ```
    $ cd code
    $ svn co https://svnsrv.desy.de/public/unfolding/RooUnfold/trunk RooUnfold
    $ cd RooUnfold
    $ make
    $ cd ..
  ```  
  
  ## Running the analysis
  
  1. Running full analysis
  
  You can run the code with either data or Monte Carlo samples as input. If you want to run the code with data, change nothing. If you want to run the code with MC, go to [settings.h line 25](https://github.com/alintulu/2011-jet-inclusivecrosssection-analysis/blob/master/jetphys/code/settings.h#L25) and change 

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
  
  Either comment out the parts you don't want to run in [mk_runFullAnalysis.C](jetphys/code/mk_runFullAnalysis.C) or simply choose one make file to run (exempel [mk_normalizeHistos.C](jetphys/code/mk_normalizeHistos.C))
  
  ```
  $ root -l -b -q mk_normalizeHistos.C
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

## Variables of output root files

 * In `output-DATA/MC-1/2a/2b.root`
  ```
  hpt = raw pT spectrum
  hpt_pre (only for data) = prescaled pT spectrum
  hlumi (only for data, for MC hlumi = 1) = effective luminosity
  hpt_g0tw (only for MC) = unbiased generator spectrum (needed for unfolding)
  ```
 * In `output-DATA/MC-2c.root`
  ```
  gnlo = graph of theory points with centered bins
  gnlocut = graph of theory points with centered bins but only up to expected pT
  gnlofit = graph of theory points with centered bins but graph is divided with fit to check stability
  fnlo = initial fit of NLO curve
  hnlo = generated spectrum fitted to the NLO curve
  ```
 * In `output-DATA/MC-3.root`
  ```
  grcorrpt = graph of corrected pt
  hcoorpt = histogram of corrected pt
  gfold = "unfolding corrections" (unfolded / original)
  fus = initial fit of the NLO curve
  fs = smeared theory curve
  fres = resolution function
  grationlo = NLO ratio to unsmeared fit
  gratio = data ratio to (smeared) fit
  hreco = copy over relevant part of hpt
  htrue = copy of relevant part of hnlo
  mt = response matrix, measured X truth
  my = measured projections of response to X-axis
  mx = truth projections of response to Y-axis
  hCov = unfolding covariance matrix
  ```

## Ouput plots

* `met_sumet_ratio_of_different_pt_events.pdf`

  Graph explaining the cut made at [line 106 in fillHistos.C](https://github.com/alintulu/2011-jet-inclusivecrosssection-analysis/blob/master/jetphys/code/fillHistos.C#L106). For jets with higher pT [FILL]

* `eta_spectra.pdf`

* `jets_per_bin.pdf`

  Graph to illustrate the number of jets detected by the triggers. There is no specific reason for some curves being filled other than to show the structure of curve. The shaded area of the filled curves indicate where the different triggers will be stitched together. In the macro [combineHistos.C](jetphys/code/combineHistos.C) jets from the shaded area of one trigger histogram will be stitched together with jets from the other shaded areas of other trigger histograms to form one complete histogram.
  
* `roounfold_comparison_AK5_DATA.pdf`

  Comparison of different unfolding methods
  
* `roounfold_matrix_AK5_DATA.pdf`

  Unfolding matrix for different eta intervals
  
* `roounfold_matrix0_AK5_DATA.pdf`

  Unfolding matrix for |y|<0.5
  
* `roounfold_ratiotofwd_AK5_DATA.pdf`
