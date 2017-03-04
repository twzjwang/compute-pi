reset
set style fill solid
set grid
set term png enhanced font 'Verdana,10'
set output 'runtime.png'
set datafile separator ','
set xlabel "N"

plot 'result_clock_gettime.csv' using 1:2 with points linewidth 2  title 'baseline', \
'' using 1:3 with points title 'openmp_2', \
'' using 1:4 with points linewidth 2 title 'openmp_4', \
'' using 1:5 with points linewidth 2 title 'avx', \
'' using 1:6 with points linewidth 2 title 'avxunroll', \
'' using 1:7 with points linewidth 2 title 'montecarlo'
