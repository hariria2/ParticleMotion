from SQLVisualization import SQLVisualization


vis = SQLVisualization('root','','localhost','partsim_v1_10_6_2015')


vis.getParticle('All')
vis.getDomain('All')

vis.PlotLocation(vis._Particles[25])
