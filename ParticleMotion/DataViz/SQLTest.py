from SQLVisualization import SQLVisualization
import matplotlib.pyplot as plt

vis = SQLVisualization('root','','localhost','partsim_v1_10_13_2015')


vis.getParticle('All')
vis.getDomain('All')

plt.figure(1)
plt.subplot(2,1,1)
vis.HistVx(0.05)
plt.subplot(2,1,2)
vis.HistVy(0.05)

plt.figure(2)
plt.subplot(2,1,1)
vis.HistTotalV(0.05)
plt.subplot(2,1,2)
vis.HistKE(0.05)

vis.Render()
