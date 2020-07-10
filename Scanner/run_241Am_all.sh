#!/bin/bash
source ~/.bash_profile 
COUNTER=0

while [ $COUNTER -lt 5 ]
do
#	 g4simple run_scanner30_241Am.mac;
#	 mv /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/30deg/raw/scanner_241Am_30deg_0p5mm10mmEA18_realisticSource_temp.root /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/30deg/raw/scanner_241Am_30deg_0p5mm10mmEA18_realisticSource_$COUNTER.root 
#	 /Users/jgruszko/Dev/g4simple/Example/rootPostProc/postprocroot_wDead_wPSA /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/30deg/raw/scanner_241Am_30deg_0p5mm10mmEA18_realisticSource_$COUNTER.root 
#          mv /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/30deg/raw/scanner_241Am_30deg_0p5mm10mmEA18_realisticSource_$COUNTER\_processed_wPSA.root  /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/30deg/processed/scanner_241Am_30deg_0p5mm10mmEA18_realisticSource_$COUNTER\_processed.root 
	 g4simple run_scanner45_241Am.mac;
	 mv /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/45deg/raw/scanner_241Am_45deg_0p5mm10mmEA18_realisticSource_temp.root /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/45deg/raw/scanner_241Am_45deg_0p5mm10mmEA18_realisticSource_$COUNTER.root 
	 /Users/jgruszko/Dev/g4simple/Example/rootPostProc/postprocroot_wDead_wPSA /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/45deg/raw/scanner_241Am_45deg_0p5mm10mmEA18_realisticSource_$COUNTER.root 
         mv /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/45deg/raw/scanner_241Am_45deg_0p5mm10mmEA18_realisticSource_$COUNTER\_processed_wPSA.root /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/45deg/processed/scanner_241Am_45deg_0p5mm10mmEA18_realisticSource_$COUNTER\_processed.root 

	 g4simple run_scanner90_241Am.mac;
	 mv /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/90deg/raw/scanner_241Am_90deg_0p5mm10mmEA18_realisticSource_temp.root /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/90deg/raw/scanner_241Am_90deg_0p5mm10mmEA18_realisticSource_$COUNTER.root 
	 /Users/jgruszko/Dev/g4simple/Example/rootPostProc/postprocroot_wDead_wPSA /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/90deg/raw/scanner_241Am_90deg_0p5mm10mmEA18_realisticSource_$COUNTER.root 
         mv /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/90deg/raw/scanner_241Am_90deg_0p5mm10mmEA18_realisticSource_$COUNTER\_processed_wPSA.root /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm10mmEA18/241Am/90deg/processed/scanner_241Am_90deg_0p5mm10mmEA18_realisticSource_$COUNTER\_processed.root 

	let COUNTER=COUNTER+1
done

