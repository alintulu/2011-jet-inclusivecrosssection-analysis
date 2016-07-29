// Purpose: Fill jet physics analysis histograms
// Author:  mikko.voutilainen@cern.ch
// Created: March 20, 2010
// Updated: June 1, 2015

// void mk_fillHistos() {
{
    // gROOT->ProcessLine(".exception");

    // Jet energy corrections and uncertainties
    // Localized version available in github.com/miquork/jecsys/
    // Copied from there
    gROOT->ProcessLine(
        ".L CondFormats/JetMETObjects/src/Utilities.cc+");
    gROOT->ProcessLine(
        ".L CondFormats/JetMETObjects/src/JetCorrectorParameters.cc+");
    gROOT->ProcessLine(
        ".L CondFormats/JetMETObjects/src/SimpleJetCorrector.cc+");
    gROOT->ProcessLine(
        ".L CondFormats/JetMETObjects/src/FactorizedJetCorrector.cc+");

    // For JEC uncertainty
    gROOT->ProcessLine(
        ".L CondFormats/JetMETObjects/src/SimpleJetCorrectionUncertainty.cc+");
    gROOT->ProcessLine(
        ".L CondFormats/JetMETObjects/src/JetCorrectionUncertainty.cc+");

    // compile code
    gROOT->ProcessLine(".L tools.C+");
    gROOT->ProcessLine(".L runHistos.C+");
    gROOT->ProcessLine(".L basicHistos.C+");

    gROOT->ProcessLine(".L fillHistos.C+g"); // +g for assert to work

// This is already included in the .C files above
// Including it again breaks CLING in ROOT 6.04.10
#include "settings.h"

    std::string algo = "ak7";
    if (_jp_algo == "AK8")
        algo = "ak8";
    if (_jp_algo == "AK7")
        algo = "ak7";
    if (_jp_algo == "AK4")
        algo = "ak4";

    // Common tree name for both MC and DATA
    TChain *c = new TChain("ak7/OpenDataTree");

    if (_jp_type == "DATA") {
        cout << "Load trees..." << endl;

        // 2011A
        c->AddFile("data/tuples0.root");
        //c->AddFile("root://eoscms.cern.ch//eos/cms/store/group/phys_smp/mhaapale/Jet/crab_OpenDataTree_all/160722_132928/0000/tuples0.root");
        
        cout << "Got " << c->GetEntries() << " entries" << endl;
    }
    else if (_jp_type == "MC") 
    {
        cout << "Load trees..." << endl;

        c->AddFile("MC/MC_tuples.root");  
        cout << "Got " << c->GetEntries() << " entries" << endl;
    }

    // Awkward patch for ROOT6:
    // Call 'Loop()' and 'delete this;' inside constructor;
    fillHistos(c);
}
