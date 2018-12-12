
# Environment
cd /afs/cern.ch/user/m/mhaapale/work/public/CMSSW_5_3_20
eval `scramv1 runtime -sh`
cd -
ln -s /afs/cern.ch/user/m/mhaapale/work/public/JetAnalysis/jetphys . 
cd jetphys

# Run ROOT script 
root -q mk_fillHistos.C

# Copy output
xrdcp -f output-DATA-1.root root://eoscms.cern.ch//eos/cms/store/group/phys_smp/mhaapale/Jet/ProcessedTree_test/160610_151512/0000/