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


    // Common tree name for both MC and DATA
    TChain *c = new TChain("ak5ak7/OpenDataTree");

    if (_jp_type == "DATA") {
        cout << "Load trees..." << endl;

        // 2011A
        c->AddFile("data/tuples2.root");
        //c->AddFile("data/OpenDataTree_data.root");
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
    fillHistos(c);
}
