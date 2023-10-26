import cv2
import time
import numpy
import serial

from mesa import mesa
from traditional import traditional
from deepLearning import deepLearning

prev_frame_time = 0
new_frame_time = 0
kernel = numpy.ones((5, 5), numpy.uint8)

captura = cv2.VideoCapture(0)

m = mesa()
trad = traditional()
deep = deepLearning()

mode = 0


arduino = serial.Serial('COM3', 9600)

def getImage():
    global captura
    ret, frame = captura.read()
    frame = cv2.resize(frame, (800, 600))
    return frame


def calcFrame():
    global prev_frame_time
    global new_frame_time
    new_frame_time = time.time()
    fps = 1 / (new_frame_time - prev_frame_time)
    prev_frame_time = new_frame_time
    fps = int(fps)
    fps = str(fps)
    return fps

def resize_with_black_borders(image, width, height):
  """
  Redimensiona uma imagem para um tamanho especificado, mantendo a proporção e adicionando bordas pretas.

  Args:
    image: A imagem a ser redimensionada.
    width: O novo tamanho da largura da imagem.
    height: O novo tamanho da altura da imagem.

  Returns:
    A imagem redimensionada com bordas pretas.
  """

  # Calcula a proporção da imagem original
  ratio = image.shape[1] / image.shape[0]

  # Calcula o tamanho da imagem redimensionada
  newWidth = width
  newHeight = int(newWidth / ratio)

  # Redimensiona a imagem com bordas pretas
  resizedImage = cv2.copyMakeBorder(
      image, 0, 0, int((width - newHeight) / 2), int((width - newHeight) / 2),
      cv2.BORDER_CONSTANT, value=(0, 0, 0))

  return resizedImage

while (True):
    image = getImage()
    fps = calcFrame()
    font = cv2.FONT_HERSHEY_SIMPLEX
    x, y, r = 0, 0, 0
    if mode == 0:
        x, y, r = trad.detectCircle(image, cv2)
        m.setposBol(x,y,r)
        x, y = trad.findBase(image,cv2,kernel)
        m.setposFlip(x,y)
    else:
        imageRGB = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        #imageRGB = resize_with_black_borders(imageRGB, 256,256)
        imageRGB = cv2.resize(imageRGB, (256, 256))
        x, y, r = deep.inference(imageRGB)
        x = int(x * 3.160)
        y = int(y * 2.343)
        r = int(r * 3.125)
        m.setposBol(x,y,r)


    for i in range(len(m.bx)):
        if i == 0:
            cv2.circle(image, (m.bx[i], m.by[i]), int(r), (0, 255, 0), 2)
        cv2.circle(image, (m.bx[i], m.by[i]), 1, (255, 0, 0), 2)

    try:
        x, y = m.getnextPos(2)
        cv2.circle(image, (x, y), 1, (255, 0, 255), 2)
    except:
        print("Erro ao predizer bolinha")

    hit, lado = m.isHit()
    if hit:
        if lado == 1:
            arduino.write('2'.encode())
        if lado == 0:
            arduino.write('1'.encode())

    print(str(hit) + " - " + str(lado))
    if m.hb.x != 0:
        cv2.rectangle(image, (int(m.hb.x), int(m.hb.y)), (int(m.hb.x+(m.hb.w/2)), int(m.hb.y+m.hb.h)), (0, 255, 0), 1)
        cv2.rectangle(image, (int(m.hb.x - (m.hb.w/2)), int(m.hb.y)), (int(m.hb.x), int(m.hb.y+m.hb.h)), (0, 255, 0), 1)

    if mode == 0:
        cv2.putText(image, 'Math', (0, 70), font, 1, (100, 255, 0), 2, cv2.LINE_AA)
    if mode == 1:
        cv2.putText(image, 'Ai', (0, 70), font, 1, (100, 255, 0), 2, cv2.LINE_AA)

    cv2.putText(image, fps, (0, 45), font, 2, (100, 255, 0), 2, cv2.LINE_AA)
    cv2.imshow("Video", image)

    k = cv2.waitKey(1) & 0xff
    print(k)
    if k == 116:
        if mode == 1:
            mode = 0
        else:
            mode = 1
    if k == 27:
        break

captura.release()
cv2.destroyAllWindows()
arduino.close()
