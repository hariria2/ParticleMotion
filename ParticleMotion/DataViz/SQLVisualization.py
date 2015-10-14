import mysql.connector
import matplotlib.pyplot as plt
from matplotlib import rc
from Particle import Particle
from Domain import Domain
from math import sqrt
import numpy as np

class SQLVisualization:

    gr = [0.2, 0.7, 0.3];
    re = [0.7, 0.2, 0.3];
    bl = [0.2, 0.3, 0.7];
    yl = [0.7, 0.7, 0.3];

    def __init__(self,usrnm,psswd,hst,db):
        cnx = mysql.connector.connect(user=usrnm, password=psswd,host=hst,database=db)
        self._Connection = cnx
        self._Cursor = cnx.cursor()
        self._Particles = []
        self._ParticleIDs = []
        self._Domains = []
        self._DomainIDs = []


    def getParticle(self, ids, t):
        query1 = '';
        query2 = '';
        if ids == 'All':
            sqlquery1 = 'SELECT * FROM Particles';
            if t == 'All':
                sqlquery2 = 'SELECT * FROM ParticleData';
            else:
                self._T0 = t[0]
                sqlquery2 = 'SELECT * From ParticleData Where Time > %d and Time < %d' %(t[0],t[1])

            self._Cursor.execute(sqlquery1);
            data1 = self._Cursor.fetchall();

            self._Cursor.execute(sqlquery2);
            data2 = self._Cursor.fetchall();

            l = len(data1);

            ids = range(1,l+1);
            self.ShowProgress = 1;
        else: # Make sure you add time picking to this case
            l = len(ids);

            for ii in range(0,l):
                if ii == l-1:
                    query1 = query1 + 'ID = ' + str(ids[ii]);
                else:
                    query1 = query1 + 'ID = ' + str(ids[ii]) + ' or ';

            for ii in range(0,l):
                if ii == l-1:
                    query2 = query2 + 'ParticleID = ' + str(ids[ii]);
                else:
                    query2 = query2 + 'ParticleID = ' + str(ids[ii]) + ' or ';

            sqlquery1 = 'SELECT * FROM Particles Where ' + query1;
            sqlquery2 = 'SELECT * FROM ParticleData Where ' + query2;


            self._Cursor.execute(sqlquery1);
            data1 = self._Cursor.fetchall();

            self._Cursor.execute(sqlquery2);
            data2 = self._Cursor.fetchall();


        # data2 - index, id, time, x, y, vx, vy, fx, fy

        for idx in range(l):
            id = ids[idx]
            alldata = [x for x in data2 if x[1] == id]
            m = data1[idx][1]
            d = data1[idx][2]
            p = Particle(id,m,d)
            p.setTime([x[2] for x in alldata])
            p.setX([x[3] for x in alldata])
            p.setY([x[4] for x in alldata])
            p.setVx([x[5] for x in alldata])
            p.setVy([x[6] for x in alldata])
            p.setFx([x[7] for x in alldata])
            p.setFy([x[8] for x in alldata])
            p.setDt()

            if not (id in self._ParticleIDs):
                self._Particles.append(p)
                self._ParticleIDs.append(id)

    def getDomain(self, ids):

            query1 = '';
            if ids == 'All':
                sqlquery1 = 'SELECT * FROM Domain';

                self._Cursor.execute(sqlquery1);
                data1 = self._Cursor.fetchall();

                l = len(data1);

                ids = range(1,l+1);

            else:
                l = len(ids);

                for ii in range(0,l):
                    if ii == l-1:
                        query1 = query1 + 'ID = ' + str(ids[ii]);
                    else:
                        query1 = query1 + 'ID = ' + str(ids[ii]) + ' or ';

                sqlquery1 = 'SELECT * FROM Domain Where ' + query1;


                self._Cursor.execute(sqlquery1);
                data1 = self._Cursor.fetchall();



            for idx in range(0,l):

                id = ids[idx]
                alldata = [x for x in data1 if x[0] == id]

                d = Domain(id,alldata[idx][1],alldata[idx][2],alldata[idx][3],alldata[idx][4])

                if not (id in self._DomainIDs):
                    self._Domains.append(d)
                    self._DomainIDs.append(id)

    def DrawParticle(self, part):
        plt.plot(part._X,part._Y,'.k')

    def DrawPlace(self, place):
        xmin = place._xmin
        xmax = place._xmax
        ymin = place._ymin
        ymax = place._ymax

        self.polyxs = [obj.polyxs,[xmin, xmin, xmax, xmax]];
        self.polyys = [obj.polyys,[ymin, ymin, ymax, ymax]];

    def PlotLocation(self, part):
        plt.plot(part._X,part._Y,'.k')
        plt.xlabel('x')
        plt.ylabel('y')
    def PlotVelocity(self, part):
        plt.plot(part._Vx,part._Vy,'.k')
        plt.xlabel('v_x')
        plt.ylabel('v_y')
    def PlotForce(self, part):
        plt.plot(part._Fx,part._Fy,'.k')
        plt.xlabel('f_x')
        plt.ylabel('f_y')
    def PlotTimeX(self, part):
        plt.plot(part._Time,part._X,'.k')
    def PlotTimeY(self, part):
        plt.plot(part._Time,part._Y,'.k')
    def PlotTimeVx(self, part):
        plt.plot(part._Time,part._Vx,'.k')
    def PlotTimeVy(self, part):
        plt.plot(part._Time,part._Vy,'.k')
    def PlotTimeFx(self, part):
        plt.plot(part._Time,part._Fx,'.k')
    def PlotTimeFy(self, part):
        plt.plot(part._Time,part._Fy,'.k')

    def HistVx(self,t):
        VV = [x._Vx for x in self._Particles]
        dt = self._Particles[0]._dt
        idx = int(t/dt)
        data = [x[idx] for x in VV]
        pn, bins, patches = plt.hist(data,int(len(self._Particles)/2.),normed=1,rwidth=0.8)
        plt.setp(patches, 'facecolor', 'r', 'alpha', 0.3)
        plt.ylabel('Vx')
        plt.title('time = %d'%t)

    def HistVy(self,t):
        VV = [x._Vy for x in self._Particles]
        dt = self._Particles[0]._dt
        idx = int(t/dt)
        data = [x[idx] for x in VV]
        n, bins, patches = plt.hist(data,int(len(self._Particles)/2.),normed=1,rwidth=0.8)
        plt.setp(patches, 'facecolor', 'r', 'alpha', 0.3)
        plt.ylabel('Vy')
        plt.title('time = %d'%t)

    def HistTotalV(self,t):
        #plt.rc('text', usetex=True)
        #plt.rc('font', family='serif')
        VV = [(x._Mass,x._Vx,x._Vy) for x in self._Particles]
        dt = self._Particles[0]._dt
        idx = int(t/dt)
        data = [x[1][idx]+x[2][idx] for x in VV]
        n, bins, patches = plt.hist(data,int(len(self._Particles)/2.),normed=1,rwidth=0.8)
        plt.setp(patches, 'facecolor', 'r', 'alpha', 0.3)
        plt.ylabel('Vx+Vy')
        plt.title('time = %d'%t)

    def HistKE(self,t, massq):
        VV = [(x._Mass,x._Vx,x._Vy) for x in self._Particles]
        dt = self._Particles[0]._dt
        idx = int(t/dt)
        if massq:
            data = [0.5*x[0]*sqrt(x[1][idx]**2+x[2][idx]**2) for x in VV]
        else:
            data = [sqrt(x[1][idx]**2+x[2][idx]**2) for x in VV]
        n, bins, patches = plt.hist(data,int(len(self._Particles)/2.),normed=1,rwidth=0.8)
        plt.setp(patches, 'facecolor', [0.8,0.5,0.5], 'alpha', 0.7)
        plt.ylabel('KE')
        plt.title('time = %2.2f'%(t+self._T0))

    def Render(self):
        plt.show()
    def __del__(self):
        self._Cursor.close()
        self._Connection.close()
