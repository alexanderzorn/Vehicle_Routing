#!/bin/bash
>zeiten.txt
>knoten.txt
>namen.txt
for file in ./A-VRP/*.vrp ; do
        fname=$(basename "$file")
        start_ms=$(ruby -e 'puts (Time.now.to_f * 1000).to_i')
        groesse=$(./test ./A-VRP/$fname)
        end_ms=$(ruby -e 'puts (Time.now.to_f * 1000).to_i')
        elapsed_ms=$((end_ms - start_ms))
        echo "$elapsed_ms" >>zeiten.txt
	echo "$groesse" >>knoten.txt
	echo "$fname" >>namen.txt
done
