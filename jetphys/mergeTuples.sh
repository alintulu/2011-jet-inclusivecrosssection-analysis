

# Environment
cd /afs/cern.ch/user/m/mhaapale/work/public/CMSSW_5_3_20
eval `scramv1 runtime -sh`
cd -

# Mount EOS
mkdir eos
eosmount eos
ln -s eos/cms/store/group/phys_smp/mhaapale/Jet/ProcessedTree_test/160610_151512/0000 
cd 0000

# Merge files 
hadd tuples.root ProcessedTree_data_?.root

# Copy output
#xrdcp -f output-DATA-1.root root://eoscms.cern.ch//eos/cms/store/group/phys_smp/mhaapale/Jet/ProcessedTree_test/160610_151512/0000/