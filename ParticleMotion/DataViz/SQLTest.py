from SQLVisualization import SQLVisualization
import matplotlib.pyplot as plt

vis = SQLVisualization('root','','localhost','partsim_v1_10_13_2015')

trange = [40,48]
toShow = [0.1,0.5,1,2,4,7]
snapshots = [x + trange[0] for x in toShow]

print snapshots
vis.getParticle('All',trange)
vis.getDomain('All')



n = 1;
plt.figure(1)
for t in toShow:
    plt.subplot(3,2,n)
    n = n+1
    vis.HistKE(t,True)

#vis.Render()

# no variability
vis2 = SQLVisualization('root','','localhost','partsim_v2_10_13_2015')


vis2.getParticle('All',trange)
vis2.getDomain('All')



n = 1;
plt.figure(2)
for t in toShow:
    plt.subplot(3,2,n)
    n = n+1
    vis2.HistKE(t,True)

vis2.Render()
