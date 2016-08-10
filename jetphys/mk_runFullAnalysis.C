// Purpose: Jet physics analysis chain based on ROOT6 (6.02/10)
// Author:  mikko.voutilainen@cern.ch
// Created: March 20, 2010
// Updated: June 1, 2015
{

    // ***** BEFORE RUNNING THE ANALYSIS ****** //
    // NB: more detailed instructions are at the end
    // * Provide JSON file (output JSON to lumicalc/)
    // * Provide lumicalc_by_LS.csv (run lumiCalc.py on lxplus with JSON)
    // * Provide prescale files (run lumicalc/prescales.C on lxplus)
    // * Point mk_fillHistos.C to correct data/MC files, 
    //   mk_theory.C to correct theory, and fillHistos.C to correct JSON etc.
    //   [tbd: make these all configurable]
    // * Optimize bins for given luminosity (optimizeBins.C, basicHistos.C)
    //
    // (Check that new runs are listed in JetMETTau stream)
    // (Update trigger thresholds in mk_combineHistos.C)
    // (Update lumi and max pT in settings.h)
    // Reoptimize bins for given luminosity (optimizeBins.C, basicHistos.C)
    // Instructions of getting the external data are at the end

    // ***** AFTER RUNNING THE ANALYSIS ****** //
    // (=> update his part)
    // Check the new results in the Analysis Note:
    // cd pas; cp -pi ../comparisons/pasPF.root .; root -l -b -q mk_pasPlots.C
    // cp -p fig7_Comparison_*_LUM.pdf ../latex/figs/
    // cp -p pflow_*_LUM.pdf ../latex/figs/
    // cd ../latex; sh copy_anplots.sh; pdflatex inclbpfjets.tex


    // Setup directories
    //gROOT->ProcessLine(".! mkdir pdf");

    // Load settings
    //#include "settings.h"

    // Step 1:  - make histograms of measured jet properties (pt, dijet mass)
    //          - make histograms of correction factors (JEC, JER)
    //         (- for MC include generator truth information for analysis closure)
    std::cout << "\nStep 1: Histogram measured jet pt and correction factors"
        << "\n========================================================\n";
    gROOT->ProcessLine(".x mk_fillHistos.C");
 
    // Step 2a: - apply corrections, normalize luminosity and eta width
    std::cout << "\nStep 2a: Apply corrections and normalization factors"
       << "\n====================================================\n";
    gROOT->ProcessLine(".x mk_normalizeHistos.C");

    // Step 2b: - stitch different triggers together
    std::cout << "\nStep 2b: Stitch different triggers together"
       << "\n===========================================\n";
    gROOT->ProcessLine(".x mk_combineHistos.C");

    // Step 2c:  - reformat theory curves
    std::cout << "\nStep 2c: Reformat theory predictions"
       << "\n======================================\n";
    //  gROOT->ProcessLine(".x mk_theory.C");

    // Step 3: - unfold spectrum using d'Agostini method
    std::cout << "\nStep 3: Unfold spectrum using d'Agostini method"
       << "\n===================================================\n";
    //gROOT->ProcessLine(".x mk_dagostini.C");


    // Step 6:  - produce pretty plots of analysis steps
    std::cout << "\nStep 6: Draw plots (raw spectra, triggers, unfolding)"
       << "\n=====================================================\n";
    ///gROOT->ProcessLine(".x mk_drawPlots.C");

    // Step 7: - plot systematics
    std::cout << "\nStep 7: Draw plots (systematics)"
       << "\n================================\n";
    //gROOT->ProcessLine(".x mk_drawSystematics.C");

    // Step 8: - plot summary
    std::cout << "\nStep 8: Draw plots (summary)"
       << "\n================================\n";

    // Step 9: - plot summary
    std::cout << "\nStep 9a: Draw plots (comparison)"
       << "\n================================\n";
    //gROOT->ProcessLine(".x mk_drawComparison.C");

    // Get pixellumi_by_LS.csv file with pixelLumiCalc.py (new, Feb22)
    // --------------------------------------------------
    // https://hypernews.cern.ch/HyperNews/CMS/get/luminosity/122.html
    // cmsrel CMSSW_5_0_1
    // cmsenv
    // cvs co -r HEAD RecoLuminosity/LumiDB
    // cd RecoLuminosity/LumiDB/; scram b
    // setenv FRONTIER_FORCELOAD long
    // cd lumicalc
    // - ../RecoLuminosity/LumiDB/scripts/pixelLumiCalc.py -i lumiSummary_Jan16th.json overview [total recorded for double-checking below: 4.943/fb]
    // - ../RecoLuminosity/LumiDB/scripts/pixelLumiCalc.py -i lumiSummary_Jan16th.json lumibyls -o pixellumi_by_LS.csv
    // - $HOME> rsync -rut lxplus.cern.ch:~/scratch0/CMSSW_4_2_8/src/lumicalc .

}