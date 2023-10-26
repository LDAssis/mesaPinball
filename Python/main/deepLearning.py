import torch

class deepLearning:
    def __init__(self):
        self.model = torch.hub.load('ultralytics/yolov5', 'custom', 'best256pV9.onnx')

    def inference(self, image):
        results = self.model(image, size=256)
        lists = results.pandas().xywh
        xb = 0
        yb = 0
        radio = 0

        xf1 = 0
        yf1 = 0

        xf2 = 0
        yf2 = 0
        print(results)
        gam = 0
        try:
            for l in lists:
                if int(l["class"][gam]) == 0:
                    print("Entrou aq")
                    xb = l.xcenter[0].astype(int)
                    yb = l.ycenter[0].astype(int)
                    radio = ((l.width[0].astype(int)) / 2)
                    return xb, yb, radio
            gam = gam+1
        except:
            print("Nada encontrado")


        return xb,yb, radio