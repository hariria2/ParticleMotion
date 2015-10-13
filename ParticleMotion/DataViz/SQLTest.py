from SQLVisualization import SQLVisualization
import matplotlib.pyplot as plt

vis = SQLVisualization('root','','localhost','partsim_v1_10_6_2015')


vis.getParticle('All')
vis.getDomain('All')

plt.figure(1)
plt.subplot(2,1,1)
vis.HistVx(4.11)
plt.subplot(2,1,2)
vis.HistVy(4.11)

plt.figure(2)
vis.HistKE(4.11)
vis.Render()
