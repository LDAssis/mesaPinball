class mesa:
    def __init__ (self):
        self.bx = []
        self.by = []
        self.radio = 0


    class hitBox:
        def __init__ (self):
            self.x = 0
            self.y = 0
            self.w = 0
            self.h = 0

    class lancadorBase:
        def __init__ (self):
            self.x = 0
            self.y = 0
            self.w = 0
            self.h = 0

    hb = hitBox()
    lb = lancadorBase()
    hb.w = 200
    hb.h = 100
    def setposBol(self, posX, posY, radio):
        self.radio = radio
        if (len(self.bx) >= 10):
            del (self.bx[9])
            del (self.by[9])
        self.bx.insert(0, posX)
        self.by.insert(0, posY)

    def getLastPos(self):
        return self.bx[0], self.by[0]

    def setposFlip(self, posX, posY):
        self.hb.x = posX
        self.hb.y = posY

    def getnextPos(self, mult):
        try:
            x1 = int(self.bx[0])
            y1 = int(self.by[0])

            x2 = int(self.bx[1])
            y2 = int(self.by[1])

            valx = x1 - x2
            valy = y1 - y2

            newPosx = (valx * mult) + self.bx[0]
            newPosy = (valy * mult) + self.by[0]

            predictedPosX = newPosx
            predictedPosY = newPosy

            return predictedPosX, predictedPosY
        except:
            return 0, 0

    #return 0 to left and 1 to right flipper and false or true
    def isHit(self):
        predictedPosX, predictedPosY = self.getnextPos(1)
        try:
            xB = predictedPosX
            yB = predictedPosY
            if (xB > self.hb.x) and (xB < self.hb.x+(self.hb.w/2)):
                #Bolinha se econtra a direita
                if (yB > self.hb.y) and (yB < self.hb.y+(self.hb.h)):
                    return True, 1
            if (xB < self.hb.x) and (xB > self.hb.x - (self.hb.w / 2)):
                # Bolinha se econtra a esquerda
                if (yB > self.hb.y) and (yB < self.hb.y + (self.hb.h)):
                    return True, 0
            return False, 99


        except:
            pass











