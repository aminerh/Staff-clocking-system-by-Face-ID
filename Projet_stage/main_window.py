import sys
import pickle
import pyodbc
# import some PyQt5 modules
from PyQt5.QtWidgets import QApplication
from PyQt5.QtWidgets import QMessageBox
from PyQt5.QtWidgets import QWidget
from PyQt5.QtGui import QImage
from PyQt5.QtGui import QPixmap
from PyQt5.QtCore import QTimer
from PyQt5.QtCore import QCoreApplication, Qt


# import Opencv module
import cv2

from MyMain import *


class MainWindow(QWidget):
    # class constructor
    


    def __init__(self,CurId):
        # call QWidget constructor
        super().__init__()
        self.ui = Ui_Form()
        self.ui.setupUi(self)
       # self.showFullScreen()
        # load face cascade classifier
        self.face_cascade = cv2.CascadeClassifier("D:/stage/cascades/data/haarcascade_frontalface_alt2.xml")
        #change the path later
        if self.face_cascade.empty():
            QMessageBox.information(self, "Error Loading cascade classifier" , "Unable to load the face	cascade classifier xml file")
            sys.exit()
      
        
       
        #go back to main frame
        self.ui.pushButton.clicked.connect(QCoreApplication.instance().quit)
       
        # create a timer
        self.timer = QTimer()
        # set timer timeout callback function
        self.timer.timeout.connect(self.detectFaces)
        # set control_bt callback clicked  function
        self.ui.control_bt.clicked.connect(self.controlTimer)
        # call the confim function
        #self.ui.pushButton_2.clicked.connect(self.point)


    # detect face
    def detectFaces(self):
        # read frame from video capture
        ret, frame = self.cap.read()

        recognizer = cv2.face.LBPHFaceRecognizer_create()
        recognizer.read("D:/stage/recognizers/face-trainner.yml")
        
        labels = {"person_name": 1}
        with open("D:/stage/pickles/face-labels.pickle", 'rb') as f:
            og_labels = pickle.load(f)
            labels = {v:k for k,v in og_labels.items()}

       

        # resize frame image
        scaling_factor = 0.8
        frame = cv2.resize(frame, None, fx=scaling_factor, fy=scaling_factor, interpolation=cv2.INTER_AREA)

        # convert frame to GRAY format
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # detect rect faces
        face_rects = self.face_cascade.detectMultiScale(gray, 1.3, 5)

        # for all detected faces
        for (x, y, w, h) in face_rects:
            # draw green rect on face
            #print(x,y,w,h)
            roi_gray = gray[y:y+h, x:x+w] #(ycord_start, ycord_end)
            roi_color = frame[y:y+h, x:x+w]

            # recognize? deep learned model predict keras tensorflow pytorch scikit learn
            id_, conf = recognizer.predict(roi_gray)
            if conf>=4 and conf <= 85:
                #print(id_)
                #label_To_Data.append(labels[id_])
                font = cv2.FONT_HERSHEY_SIMPLEX
                name = labels[id_]
                color = (255, 255, 255)
                stroke = 2
                cv2.putText(frame, "", (x,y), font, 1, color, stroke, cv2.LINE_AA)


                img_item = "7.png"
                cv2.imwrite(img_item, roi_color)
                fullname=name.split("_")
                #need to return this id !!!
                
                self.CurId=fullname[2]

                self.ui.textEdit.setPlainText(fullname[0]+" "+fullname[1]+"\n")
                color = (255, 0, 0) #BGR 0-255 
                stroke = 2
                end_cord_x = x + w
                end_cord_y = y + h
                cv2.rectangle(frame, (x, y), (end_cord_x, end_cord_y), color, stroke)
                
        # Display the resulting frame
        # convert frame to RGB format
        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

        # get frame infos
        height, width, channel = frame.shape
        step = channel * width
        # create QImage from RGB frame
        qImg = QImage(frame.data, width, height, step, QImage.Format_RGB888)
        # show frame in img_label
        self.ui.image_label.setPixmap(QPixmap.fromImage(qImg))



    # start/stop timer
    def controlTimer(self):
        # if timer is stopped
        if not self.timer.isActive():
            # create video capture
            self.cap = cv2.VideoCapture(0)
            # start timer
            self.timer.start(20)
            # update control_bt text
            self.ui.control_bt.setText("Stop")
        # if timer is started
        else:
            # stop timer        	
            self.timer.stop()
           
            # release video capture
            self.cap.release()
            # update control_bt text
            self.ui.control_bt.setText("Start")

    def point(self):
        #self.ui.label.setText(str(self.CurId))
       
        conn = pymssql.connect(server=r'WIN-9SCM6JLQTD9', user=r'sa', password=r'FalahFes123',database=r'TEST')
        cursor = conn.cursor()
        data = (1, date.today(), datetime.now().strftime("%H:%M:%S"))
        #CurId is the value of the current id
        cursor.execute("SELECT C.name FROM Perssonel as P,Categorie as C where P.id="+self.CurId+" P.id_C=C.id") 
        cursor.fetchall()
        
        cursor.execute("INSERT INTO Test.dbo.Creneau (id_cr, AccessDate, AccessHour) VALUES(%d, '%s', '%s')" % data)  
        conn.commit()     
        print("Data Successfully Inserted")  
        #print(id); 
        conn.close() 
        
       


if __name__ == '__main__':
    app = QApplication(sys.argv)

    # create and show mainWindow

    mainWindow = MainWindow(0)
    mainWindow.show()

    sys.exit(app.exec_())
