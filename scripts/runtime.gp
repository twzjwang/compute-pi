reset
set style fill solid
set grid
set logscale y
set term png enhanced font 'Verdana,10'
set output 'runtime.png'

plot [:][:]'output.txt' using 2:xtic(1) with lines title 'time', \
'' using ($10-0.06):($2+0.001):2 with labels title ' ', \
'' using 4:xtic(1) with lines title 'error'  , \
'' using ($10+0.3):($4+0.0015):4 with labels title ' '
