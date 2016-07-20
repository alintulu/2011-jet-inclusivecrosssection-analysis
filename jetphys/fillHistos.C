#define fillHistos_cxx
#include "fillHistos.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void fillHistos::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L fillHistos.C
//      Root > fillHistos t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
    
    if (fChain == 0) {
        return;
    }

    // Read luminosities from file
    if (_dt && _jp_dolumi) loadLumi(_jp_lumifile);

    
    Long64_t nentries = fChain->GetEntriesFast();
    //nentries = 10; // debug
    //nentries = 1000;//very short test runs
    // nentries = 100000;//short test runs
    //nentries = 1000000;//medium test runs
    // nentries = 5000000; // lunch-break run for MC (with trigsim off)
    
    _entries = nentries;

    // Switch all branches ON
    fChain->SetBranchStatus("*", 1);
    
    if (_jp_doBasicHistos) {
        initBasics("Standard");
    }
    
    // Event loop
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        
        // Error check
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        
        // Read event
        fChain->GetEntry(jentry);

        // Write this event to histograms
        if (_jp_doBasicHistos) {
            fillBasics("Standard");
        }    
    }
        
    // Delete histograms and close file properly
    if (_jp_doBasicHistos) {
        writeBasics(); 
    }
   
}


// Initialize basic histograms for trigger and eta bins
void fillHistos::initBasics(std::string name) {
    // Report memory usage to avoid malloc problems when writing file

    TDirectory *curdir = gDirectory;

    // open file for output
    TFile *f = (_outfile ? _outfile: new TFile(Form("output-%s-1.root", _type.c_str()), "RECREATE"));
    assert(f && !f->IsZombie());
    
    f->mkdir(name.c_str());
    assert(f->cd(name.c_str()));

    TDirectory *topdir = f->GetDirectory(name.c_str());
    assert(topdir);
    
    topdir->cd();


    // Rapidity bins + HF + barrel
    double y[] = {0., 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.2, 4.7, 0., 1.3};
    const int ny = sizeof(y) / sizeof(y[0]) - 1;

    // Trigger bins

    // Efficient trigger pT ranges for control plots
    map< string, pair< double, double > > pt;
    for (int itrg = 0; itrg != _jp_ntrigger; ++itrg) {
        string trg = _jp_triggers[itrg];
        double pt1 = _jp_trigranges[itrg][0];
        double pt2 = _jp_trigranges[itrg][1];
        pt[trg] = pair< double, double >(pt1, pt2);
    }

    map< string, double > pttrg;
    for (int itrg = 0; itrg != _jp_ntrigger; ++itrg) {
        string trg = _jp_triggers[itrg];
        double pt0 = _jp_trigthr[itrg];
        pttrg[trg] = pt0;
    }


    // Read first entry from the TTree to get trigger names 
    fChain->GetEntry(0);
    std::vector<std::string> trg_names = *triggernames;

    // Loop over rapidity and trigger bins
    for (int i = 0; i != ny; ++i) {
        if (y[i + 1] > y[i]) { // Create only real bins

            // Subdirectory for rapidity bin
            const char *yname = Form("Eta_%1.1f-%1.1f", y[i], y[i + 1]);
            assert(topdir);

            // Change to the subdirectory
            topdir->mkdir(yname);
            assert(topdir->cd(yname));
            
            TDirectory *ydir = topdir->GetDirectory(yname);
            assert(ydir);
            
            ydir->cd();
            
            // Loop over triggers
            for (std::string trg_name: trg_names) {
                
                if (trg_name == "jt300") {
                    continue;
                }

                // Trigger subdirectory
                const char *trg = trg_name.c_str();
                assert(ydir);
                
                ydir->mkdir(trg);
                ydir->cd(trg);
                
                // Change directory
                TDirectory *dir = ydir->GetDirectory(trg);
                assert(dir);
                
                dir->cd();
                // Initialize and store histogram 
                basicHistos *h = new basicHistos(   dir, trg, "", y[i], y[i + 1], 
                                                    pttrg[trg], pt[trg].first, pt[trg].second, 
                                                    trg_name == "mc", false, _jp_ak4ak8);
            
                _histos[name].push_back(h);
            }
        }    
    }        

    _outfile = f;
    curdir->cd();

} 


// Loop over histogram container to fill them
void fillHistos::fillBasics(std::string name) {
    
    for (auto const& h: _histos[name]) {
        fillBasic(h);
    }
}

// Fill basic histograms after applying pt, y cuts
void fillHistos::fillBasic(basicHistos *h) {
    // Check valididty
    assert(h && "Invalid histogram set!");

    // Index of the trigger corresponding to this histogram
    unsigned int trg_index = find(triggernames->begin(), triggernames->end(), h->trigname) - triggernames->begin();
 
    // Return if not triggered
    bool fired = (triggers[trg_index]);
    if (!fired)
        return;

    // Luminosity information
    double lum;
    if (_dt && h->lums[run][lumi]==0) {
        lum = _lums[run][lumi];
    }

    // Check for missing prescale
    unsigned int prescale = prescales[trg_index];
    if (prescale == 0 && fired) {
        *ferr   << "Prescale zero for trigger " << h->trigname
                << " in run " << run << "!" << endl << flush; 
        assert(false);
    }

    // Add this event to the luminosity sum
    h->lumsum += lum / prescale;

    // Loop over jets of this event
    for (unsigned int i = 0; i != njet; ++i) {
        if (_debug)
            cout << "Loop over jet " << i << "/" << njet << endl;

        double pt = fabs(jet_pt[i]);
        double eta = fabs(jet_eta[i]);

        if (pt > _jp_recopt && eta >= h->ymin && eta < h->ymax)  {

            // Fill raw pT spectrum
            h->hpt->Fill(jet_pt[i]);

            // Prescaled pT
            if (_dt) {
                h->hpt_pre->Fill(pt, prescales[trg_index]);
            }

        }
    }
} 


void fillHistos::writeBasics() {

    for (map< string, vector< basicHistos * > >::iterator it = _histos.begin(); it != _histos.end(); ++it) {
        
            
        // Loop over all histograms of all directories of the output file
        for (unsigned int i = 0; i != it->second.size(); ++i) {

            basicHistos *h = it->second[i];
            for (int j = 0; j != h->hlumi->GetNbinsX() + 1; ++j) {

                // For data, save effective luminosity information
                h->hlumi->SetBinContent(j, _dt ? h->lumsum : 1.);
                std::cout << h->lumsum << " " << h->trigname << std::endl;
            }

            // Delete basic histos
            delete h; 
        }             
    }   

    cout << "\nOutput stored in " << _outfile->GetName() << endl;
    _outfile->Close();
    _outfile->Delete();
}


// Load luminosity information
void fillHistos::loadLumi(const std::string filename) {

    // Open file
    std::ifstream CSVfile(filename);
    assert(CSVfile.is_open());

    // Read header
    std::string header;
    getline(CSVfile, header, '\r');
    std::cout << "CSV header: " << header << std::endl;
    
    // Require proper header format
    assert(header == string("Run:Fill,LS,UTCTime,Beam Status,E(GeV),Delivered(/ub),Recorded(/ub),avgPU"));
      
    double lumsum(0);
    bool skip(false);
    
    // One line of the file
    std::string line;

    // Total number of lumisections
    unsigned int nls;

    while ( getline(CSVfile, line, '\r') ) {

        double rec;     // Recorded lumi in ub        
        unsigned int rn;// Run
        unsigned int ls;// Lumisection

        // Parse one line
        sscanf(line.c_str(),"%d:%*d,%d:%*d,%*d/%*d/%*d %*d:%*d:%*d,STABLE BEAMS,%*f,%*f,%lf,%*f", &rn, &ls, &rec);
        double lum = rec*1e-6; // Recorded luminosity in pb

        _lums[rn][ls] = lum;
        lumsum += lum;

        ++nls;
        assert(nls<100000000);
    }

    std::cout << "Called loadLumi(\"" << filename << "\"):" << endl;
    std::cout << "Loaded " << _lums.size() << " runs with "
              << nls << " lumi sections containing "
              << lumsum << " pb-1 of data " << std::endl;
    std::cout << "This corresponds to " << nls*23.3/3600
              << " hours of data-taking" << endl;
      
} 