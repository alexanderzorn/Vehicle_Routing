#!/bin/bash
for file in ./ProjektAnalysisKit/A-VRP/*.vrp ; do
        fname=$(basename "$file")
        start_ms=$(ruby -e 'puts (Time.now.to_f * 1000).to_i')
        ./a.out ./ProjektAnalysisKit/A-VRP/$fname
        end_ms=$(ruby -e 'puts (Time.now.to_f * 1000).to_i')
        elapsed_ms=$((end_ms - start_ms))
        echo "Gebrauchte Zeit: $elapsed_ms ms fuer $fname" 
done