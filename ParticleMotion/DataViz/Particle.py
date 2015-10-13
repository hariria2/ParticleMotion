class Particle:



    def __init__(self, id, mass, domain):
        self._ID = id
        self._Mass = mass
        self._Domain = domain

    def setTime(self, t):
        self._Time = t
    def setX(self, x):
        self._X = x
    def setY(self, y):
        self._Y = y
    def setVx(self,vx):
        self._Vx = vx
    def setVy(self,vy):
        self._Vy = vy
    def setFx(self,fx):
        self._Fx = fx
    def setFy(self, fy):
        self._Fy = fy
    def setDt(self):
        self._dt = self._Time[3]-self._Time[2]
