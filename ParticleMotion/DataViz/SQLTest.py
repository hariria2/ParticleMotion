from SQLVisualization import SQLVisualization
import matplotlib.pyplot as plt

vis = SQLVisualization('root','','localhost','partsim_v1_10_6_2015')


vis.getParticle('All')
vis.getDomain('All')

plt.figure(2)
plt.subplot(3,1,1)
vis.PlotLocation(vis._Particles[5])
plt.subplot(3,1,2)
vis.PlotVelocity(vis._Particles[5])
plt.subplot(3,1,3)
vis.PlotForce(vis._Particles[5])
plt.show()
