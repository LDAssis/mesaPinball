import numpy


class traditional:

    def __init__(self):
        print("Método matemático iniciado")

    def findBase(self, image, cv2, kernel):

        rangomax = numpy.array([60, 60, 255])  # B, G, R
        rangomin = numpy.array([0, 0, 100])
        mask = cv2.inRange(image, rangomin, rangomax)
        # reduce the noise
        opening = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)
        x, y, w, h = cv2.boundingRect(opening)
        posx = x + (w / 2)
        posy = y
        return posx, posy

    def detectCircle(self, image, cv2):
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        gray_blurred = cv2.blur(gray, (3, 3))
        detected_circles = cv2.HoughCircles(gray_blurred,
                                            cv2.HOUGH_GRADIENT, 1, 20, param1=100,
                                            param2=30, minRadius=10, maxRadius=20)
        if detected_circles is not None:
            detected_circles = numpy.uint16(numpy.around(detected_circles))

            for pt in detected_circles[0, :]:
                a, b, r = pt[0], pt[1], pt[2]
                cv2.circle(image, (a, b), r, (0, 255, 0), 2)
                cv2.circle(image, (a, b), 1, (0, 0, 255), 3)
                return a, b, r
        else:
            return 0, 0, 0
