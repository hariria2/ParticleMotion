import mysql.connector
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from matplotlib.collections import PatchCollection
from Particle import Particle
from Domain import Domain

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

    def getParticle(self, ids):
        query1 = '';
        query2 = '';
        if ids == 'All':
            sqlquery1 = 'SELECT * FROM Particles';
            sqlquery2 = 'SELECT * FROM ParticleData';

            self._Cursor.execute(sqlquery1);
            data1 = self._Cursor.fetchall();

            self._Cursor.execute(sqlquery2);
            data2 = self._Cursor.fetchall();

            l = len(data1);

            ids = range(0,l);
            self.ShowProgress = 1;
        else:
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

        for idx in range(0,l):
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
        plt.show()
    def Render(self, fignum, t):
        #fig, ax = plt.subplots()

        #patches = []
        #rect = mpatches.Rectangle([0.025, 0.05], 0.05, 0.1, ec="none")
        #patches.append(rect)
        #p = PatchCollection(patches, cmap=plt.cm.hsv, alpha=0.3)
        #ax.add_collection(p)

        plt.figure(fignum)
        self.DrawParticle(self._Particles[0])
        plt.show()


    def __del__(self):
        self._Cursor.close()
        self._Connection.close()
