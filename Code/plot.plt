set terminal svg
set output "Plots/Plot.svg"
set xlabel "Window Number"
plot "Data/GenomeData.txt" with lines, "Data/GenomeData.txt" with points
