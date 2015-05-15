set terminal svg
set output "Plot.svg"
set xlabel "Window Number"
plot "Output.txt" with lines, "Output.txt" with points
