def PlotStuff(Vis):
    myPart = vis._Particles[5]
    plt.figure(1)
    plt.subplot(3,1,1)
    vis.PlotLocation(myPart)
    plt.subplot(3,1,2)
    vis.PlotVelocity(myPart)
    plt.subplot(3,1,3)
    vis.PlotForce(myPart)

    plt.figure(2)
    plt.subplot(3,2,1)
    vis.PlotTimeX(myPart)
    plt.subplot(3,2,2)
    vis.PlotTimeY(myPart)
    plt.subplot(3,2,3)
    vis.PlotTimeVx(myPart)
    plt.subplot(3,2,4)
    vis.PlotTimeVy(myPart)
    plt.subplot(3,2,5)
    vis.PlotTimeFx(myPart)
    plt.subplot(3,2,6)
    vis.PlotTimeFy(myPart)
    vis.Render(1)
