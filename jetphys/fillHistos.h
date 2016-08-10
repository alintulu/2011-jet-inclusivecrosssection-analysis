//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jul  7 17:14:10 2016 by ROOT version 5.32/00
// from TTree ProcessedTree/ProcessedTree
// found on file: tuples0.root
//////////////////////////////////////////////////////////

#ifndef fillHistos_h
#define fillHistos_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <math.h> 

#include "TMath.h"
#include "TF1.h"
#include "TF2.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TLorentzVector.h"
#include "TRandom3.h"

#include <map>
#include <vector>
#include <string>
#include <set>
#include <cmath>
#include <fstream>

#include "settings.h"
#include "basicHistos.h"
#include "runHistos.h"
#include "tools.h"

#include "IOV.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

// Fixed size dimensions of array or collections stored in the TTree if any.

class fillHistos {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   static const UInt_t kMaxNjet = 100;
   static const UInt_t kMaxNtrg = 64;

      // Declaration of leaf types
   UInt_t          ak5_njet;
   Float_t         ak5_pt[kMaxNjet];   //[ak5_njet]
   Float_t         ak5_eta[kMaxNjet];   //[ak5_njet]
   Float_t         ak5_phi[kMaxNjet];   //[ak5_njet]
   Float_t         ak5_E[kMaxNjet];   //[ak5_njet]
   Float_t         ak5_y[kMaxNjet];  // NOTE: not included in the tuple!
   Bool_t          ak5_tightID[kMaxNjet];   //[ak5_njet]
   Float_t         ak5_area[kMaxNjet];   //[ak5_njet]
   Float_t         ak5_jes[kMaxNjet];   //[ak5_njet]
   Int_t           ak5_igen[kMaxNjet];   //[ak5_njet]
   UInt_t          ak7_njet;
   Float_t         ak7_pt[kMaxNjet];   //[ak7_njet]
   Float_t         ak7_eta[kMaxNjet];   //[ak7_njet]
   Float_t         ak7_phi[kMaxNjet];   //[ak7_njet]
   Float_t         ak7_E[kMaxNjet];   //[ak7_njet]
   Float_t         ak7_area[kMaxNjet];   //[ak7_njet]
   Float_t         ak7_jes[kMaxNjet];   //[ak7_njet]
   Int_t           ak7_to_ak5[kMaxNjet];   //[ak7_njet]
   UInt_t          ngen;
   Float_t         gen_pt[kMaxNjet];   //[ngen]
   Float_t         gen_eta[kMaxNjet];   //[ngen]
   Float_t         gen_phi[kMaxNjet];   //[ngen]
   Float_t         gen_E[kMaxNjet];   //[ngen]
   UInt_t          run;
   UInt_t          lumi;
   ULong64_t       event;
   UInt_t          ntrg;
   Bool_t          triggers[kMaxNtrg];   //[ntrg]
   vector<string>  *triggernames;
   UInt_t          prescales[kMaxNtrg];   //[ntrg]
   Float_t         met;
   Float_t         sumet;
   Float_t         rho;
   Float_t         pthat;
   Float_t         mcweight;
   Float_t         chf[kMaxNjet];   //[ak5_njet]
   Float_t         nhf[kMaxNjet];   //[ak5_njet]
   Float_t         phf[kMaxNjet];   //[ak5_njet]
   Float_t         elf[kMaxNjet];   //[ak5_njet]
   Float_t         muf[kMaxNjet];   //[ak5_njet]
   Float_t         hf_hf[kMaxNjet];   //[ak5_njet]
   Float_t         hf_phf[kMaxNjet];   //[ak5_njet]
   UInt_t          hf_hm[kMaxNjet];   //[ak5_njet]
   UInt_t          hf_phm[kMaxNjet];   //[ak5_njet]
   UInt_t          chm[kMaxNjet];   //[ak5_njet]
   UInt_t          nhm[kMaxNjet];   //[ak5_njet]
   UInt_t          phm[kMaxNjet];   //[ak5_njet]
   UInt_t          elm[kMaxNjet];   //[ak5_njet]
   UInt_t          mum[kMaxNjet];   //[ak5_njet]
   Float_t         beta[kMaxNjet];   //[ak5_njet]
   Float_t         bstar[kMaxNjet];   //[ak5_njet]

   // List of branches
   TBranch        *b_ak5_njet;   //!
   TBranch        *b_ak5_pt;   //!
   TBranch        *b_ak5_eta;   //!
   TBranch        *b_ak5_phi;   //!
   TBranch        *b_ak5_E;   //!
   TBranch        *b_ak5_tightID;   //!
   TBranch        *b_ak5_area;   //!
   TBranch        *b_ak5_jes;   //!
   TBranch        *b_ak5_igen;   //!
   TBranch        *b_ak7_njet;   //!
   TBranch        *b_ak7_pt;   //!
   TBranch        *b_ak7_eta;   //!
   TBranch        *b_ak7_phi;   //!
   TBranch        *b_ak7_E;   //!
   TBranch        *b_ak7_area;   //!
   TBranch        *b_ak7_jes;   //!
   TBranch        *b_ak7_to_ak5;   //!
   TBranch        *b_ngen;   //!
   TBranch        *b_gen_pt;   //!
   TBranch        *b_gen_eta;   //!
   TBranch        *b_gen_phi;   //!
   TBranch        *b_gen_E;   //!
   TBranch        *b_run;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_event;   //!
   TBranch        *b_ntrg;   //!
   TBranch        *b_triggers;   //!
   TBranch        *b_triggernames;   //!
   TBranch        *b_prescales;   //!
   TBranch        *b_met;   //!
   TBranch        *b_sumet;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_pthat;   //!
   TBranch        *b_mcweight;   //!
   TBranch        *b_chf;   //!
   TBranch        *b_nhf;   //!
   TBranch        *b_phf;   //!
   TBranch        *b_elf;   //!
   TBranch        *b_muf;   //!
   TBranch        *b_hf_hf;   //!
   TBranch        *b_hf_phf;   //!
   TBranch        *b_hf_hm;   //!
   TBranch        *b_hf_phm;   //!
   TBranch        *b_chm;   //!
   TBranch        *b_nhm;   //!
   TBranch        *b_phm;   //!
   TBranch        *b_elm;   //!
   TBranch        *b_mum;   //!
   TBranch        *b_beta;   //!
   TBranch        *b_bstar;   //!

   fillHistos(TTree *tree=0);

   
   virtual ~fillHistos();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   std::ofstream *ferr;
   std::string _type;
   TFile * _outfile;
   std::map<std::string, std::vector<basicHistos*> > _histos;

   void initBasics(std::string name);
   void fillBasics(std::string name);
   void fillBasic(basicHistos *h);
   void writeBasics();
   void loadLumi(const std::string filename);
   

private:

   // Monte Carlo or Data
   bool _mc;
   bool _dt;

   // MC weights
   double _w, _w0;

   // Recorded luminosity by run and lumisection numbers
   std::map<int, std::map<int, float> > _lums;

   // Helper variable
   TLorentzVector p4;

};

#endif

#ifdef fillHistos_cxx
fillHistos::fillHistos(TTree *tree)
{
   // Reset output file pointer
   _outfile = NULL;

   Init(tree);
   Loop();
}

fillHistos::~fillHistos()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}


Int_t fillHistos::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

Long64_t fillHistos::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void fillHistos::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   triggernames = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;

   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   _type.assign(_jp_type);
   _dt = (_type=="DATA");
   _mc = !_dt;
   
   fChain->SetBranchAddress("ak5_njet", &ak5_njet, &b_ak5_njet);
   fChain->SetBranchAddress("ak5_pt", ak5_pt, &b_ak5_pt);
   fChain->SetBranchAddress("ak5_eta", ak5_eta, &b_ak5_eta);
   fChain->SetBranchAddress("ak5_phi", ak5_phi, &b_ak5_phi);
   fChain->SetBranchAddress("ak5_E", ak5_E, &b_ak5_E);
   fChain->SetBranchAddress("ak5_tightID", ak5_tightID, &b_ak5_tightID);
   fChain->SetBranchAddress("ak5_area", ak5_area, &b_ak5_area);
   fChain->SetBranchAddress("ak5_jes", ak5_jes, &b_ak5_jes);
   fChain->SetBranchAddress("ak5_igen", ak5_igen, &b_ak5_igen);
   fChain->SetBranchAddress("ak7_njet", &ak7_njet, &b_ak7_njet);
   fChain->SetBranchAddress("ak7_pt", ak7_pt, &b_ak7_pt);
   fChain->SetBranchAddress("ak7_eta", ak7_eta, &b_ak7_eta);
   fChain->SetBranchAddress("ak7_phi", ak7_phi, &b_ak7_phi);
   fChain->SetBranchAddress("ak7_E", ak7_E, &b_ak7_E);
   fChain->SetBranchAddress("ak7_area", ak7_area, &b_ak7_area);
   fChain->SetBranchAddress("ak7_jes", ak7_jes, &b_ak7_jes);
   fChain->SetBranchAddress("ak7_to_ak5", ak7_to_ak5, &b_ak7_to_ak5);
   fChain->SetBranchAddress("ngen", &ngen, &b_ngen);
   fChain->SetBranchAddress("gen_pt", &gen_pt, &b_gen_pt);
   fChain->SetBranchAddress("gen_eta", &gen_eta, &b_gen_eta);
   fChain->SetBranchAddress("gen_phi", &gen_phi, &b_gen_phi);
   fChain->SetBranchAddress("gen_E", &gen_E, &b_gen_E);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("ntrg", &ntrg, &b_ntrg);
   fChain->SetBranchAddress("triggers", triggers, &b_triggers);
   fChain->SetBranchAddress("triggernames", &triggernames, &b_triggernames);
   fChain->SetBranchAddress("prescales", prescales, &b_prescales);
   fChain->SetBranchAddress("met", &met, &b_met);
   fChain->SetBranchAddress("sumet", &sumet, &b_sumet);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("pthat", &pthat, &b_pthat);
   fChain->SetBranchAddress("mcweight", &mcweight, &b_mcweight);
   fChain->SetBranchAddress("chf", chf, &b_chf);
   fChain->SetBranchAddress("nhf", nhf, &b_nhf);
   fChain->SetBranchAddress("phf", phf, &b_phf);
   fChain->SetBranchAddress("elf", elf, &b_elf);
   fChain->SetBranchAddress("muf", muf, &b_muf);
   fChain->SetBranchAddress("hf_hf", hf_hf, &b_hf_hf);
   fChain->SetBranchAddress("hf_phf", hf_phf, &b_hf_phf);
   fChain->SetBranchAddress("hf_hm", hf_hm, &b_hf_hm);
   fChain->SetBranchAddress("hf_phm", hf_phm, &b_hf_phm);
   fChain->SetBranchAddress("chm", chm, &b_chm);
   fChain->SetBranchAddress("nhm", nhm, &b_nhm);
   fChain->SetBranchAddress("phm", phm, &b_phm);
   fChain->SetBranchAddress("elm", elm, &b_elm);
   fChain->SetBranchAddress("mum", mum, &b_mum);
   fChain->SetBranchAddress("beta", beta, &b_beta);
   fChain->SetBranchAddress("bstar", bstar, &b_bstar);
   Notify();
}

Bool_t fillHistos::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void fillHistos::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

#endif // #ifdef fillHistos_cxx
