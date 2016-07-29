// Purpose: Normalize inclusive jet analysis histograms
// Author:  mikko.voutilainen@cern.ch
// Created: March 21, 2010
// Updated: June 2, 2015
#include "TFile.h"
#include "TDirectory.h"
#include "TList.h"
#include "TObject.h"
#include "TKey.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TF1.h"

#include <iostream>

using namespace std;

#include "settings.h"

void recurseFile(TDirectory *indir, TDirectory *outdir,
         double etawid = 1., double etamid = 0.);

// Use this to fix luminosity
double _lumiscale = 1.00;
bool _mc = false;
bool _dt = true;

void normalizeHistos(string type) {

  assert(type==_jp_type);
  _mc = (type=="MC" || type=="HW");
  _dt = (type=="DATA");
  assert((_mc || _dt) && !(_mc && _dt));

  TFile *fin = new TFile(Form("output-%s-1.root",type.c_str()),"READ");
  assert(fin && !fin->IsZombie());

  TFile *fout = new TFile(Form("output-%s-2a.root",type.c_str()),"RECREATE");
  assert(fout && !fout->IsZombie());

  if (_lumiscale!=1 && !_mc)
    cout << "Attention! : Scaling luminosity to the new estimate"
     << " by multiplying with " << _lumiscale << endl;

  cout << "Calling normalizeHistos("<<type<<");" << endl;
  cout << "Input file " << fin->GetName() << endl;
  cout << "Output file " << fout->GetName() << endl;
  cout << "Starting recursive loop. This may take a minute" << endl << flush;

  // Loop over all the directories recursively
  recurseFile(fin, fout);

  cout << endl;
  cout << "Recursive loop done." << endl;
  cout << "Writing output to " << fout->GetName() << endl;
  cout << "This may again take a minute" << endl << flush;
  fout->Write();
  cout << "Output written in " << fout->GetName() << endl;
  fout->Close();
  cout << "Output file closed" << endl;
  fout->Delete();
  cout << "Output file pointer deleted" << endl << flush;


  fin->Close();
  fin->Delete();

} // normalizeHistos


void recurseFile(TDirectory *indir, TDirectory *outdir,
         double etawid, double etamid) {

    TDirectory *curdir = gDirectory;

    // Automatically go through the list of keys (directories)
    TList *keys = indir->GetListOfKeys();
    TListIter itkey(keys);
    TObject *key, *obj;
    TDirectory *dir;

    while ( (key = itkey.Next()) ) {

        if (_debug) 
            std::cout << key->GetName() << endl << flush;
    
        obj = ((TKey*)key)->ReadObj(); assert(obj);
        dir = indir;
    
        // Found a subdirectory: copy it to output and go deeper
        if (obj->InheritsFrom("TDirectory")) {

            //assert(outdir->mkdir(obj->GetName()));
            outdir->mkdir(obj->GetName());
            assert(outdir->cd(obj->GetName()));
            TDirectory *outdir2 = outdir->GetDirectory(obj->GetName()); assert(outdir2);
            outdir2->cd();
      
            assert(indir->cd(obj->GetName()));
            TDirectory *indir2 = indir->GetDirectory(obj->GetName());
            indir2->cd();

            // Check if directory name contains information on eta bin width
            float etamin, etamax;
            if ( (sscanf(indir->GetName(),"Eta_%f-%f",&etamin,&etamax)==2) && (etamax>etamin) ) {
                etawid = 2.*(etamax-etamin);
                etamid = 0.5*(etamax+etamin);
                //cout << "Eta bin width: " << etawid << flush << endl;
            }
    
            recurseFile(indir2, outdir2, etawid, etamid);
        } // inherits from TDirectory

        // Found a plot: normalize if hpt, then copy to output
        else if (obj->InheritsFrom("TH1")) {

            outdir->cd();
            TObject *obj2 = obj->Clone(obj->GetName());

            // Normalize hpt and hselpt histograms
            // Same for hbpt
            if (string(obj2->GetName())=="hpt"      || 
                string(obj2->GetName())=="hpt_pre"  ||
                //string(obj2->GetName())=="hdjmass"  ||
                string(obj2->GetName())=="hpt_g0tw"  ) {

                cout << "." << flush;
            
                TH1D *hpt = (TH1D*)obj2;

                bool ispre = (TString(obj2->GetName()).Contains("_pre"));
            
                TH1D *hlumi = (TH1D*)dir->Get("hlumi"); assert(hlumi);

                for (int i = 1; i != hpt->GetNbinsX()+1; ++i) {

                    // Normalization for bin width in y, pT
                    double norm = hpt->GetBinWidth(i) * etawid;
                    double trigeff = 1.;
                    double pt = hpt->GetBinCenter(i);

                    norm *= trigeff;
                
                    // Normalization for luminosity, except prescaled histogram
                    if (hlumi->GetBinContent(i) != 0 && !ispre && _dt ) {
                        norm *= hlumi->GetBinContent(i);
                    }


                    assert(norm!=0);
                    hpt->SetBinContent(i, hpt->GetBinContent(i) / norm);
                    hpt->SetBinError(i, hpt->GetBinError(i) / norm);
            
                } // for i

            } // hpt

            dir->cd();
        } // inherits from TH1

    } // while key
  
    curdir->cd();
} // recurseFile
