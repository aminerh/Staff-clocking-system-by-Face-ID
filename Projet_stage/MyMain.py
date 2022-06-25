# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'untitled.ui'
#
# Created by: PyQt5 UI code generator 5.13.2
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import QSize
from PyQt5.QtGui import QImage, QPalette, QBrush


class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(918, 604)
        oImage = QImage("D:/stage/Projet_stage/images/bg.jpg")
        sImage = oImage.scaled(QSize(918,604))                   # resize Image to widgets size
        palette = QPalette()
        palette.setBrush(QPalette.Window, QBrush(oImage))   
        Form.setPalette(palette)
        Form.setStyleSheet("\n"
"QPushButton{\n"
"    border-radius:15px;\n"
"    background:blue;\n"
"    color:white;\n"
"    font: 75 10pt \"Trebuchet MS\";\n"
"    padding:10px;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    border-radius:15px;\n"
"    background:#49ebff;\n"
"    color:#333;\n"
"    font: 75 10pt \"Trebuchet MS\";\n"
"    padding:10px;\n"
"}")
        self.image_label = QtWidgets.QLabel(Form)
        self.image_label.setGeometry(QtCore.QRect(6, 2, 604, 601))
        self.image_label.setStyleSheet("border:1px solid white;\n"
"border-radius:15px;\n"
"font: 75 18pt \"Trebuchet MS\";")
        self.image_label.setAlignment(QtCore.Qt.AlignCenter)
        self.image_label.setObjectName("image_label")
        self.control_bt = QtWidgets.QPushButton(Form)
        self.control_bt.setGeometry(QtCore.QRect(720, 560, 111, 41))
        self.control_bt.setObjectName("control_bt")
        self.pushButton = QtWidgets.QPushButton(Form)
        self.pushButton.setGeometry(QtCore.QRect(804, 2, 101, 31))
        self.pushButton.setObjectName("pushButton_2")
        self.textEdit = QtWidgets.QPlainTextEdit(Form)
        self.textEdit.setGeometry(QtCore.QRect(630, 60, 281, 481))
        self.textEdit.setStyleSheet("border:2px solid balck;\n"
"border-radius:15px;")
        self.textEdit.setObjectName("textEdit")
        self.label_2 = QtWidgets.QLabel(Form)
        self.label_2.setGeometry(QtCore.QRect(630, 20, 71, 21))
        self.label_2.setStyleSheet("color:white;font:bold;\n " 
            "    font: 75 10pt \"Trebuchet MS\";\n")
        self.label_2.setObjectName("label_2")

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        self.image_label.setText(_translate("Form", "Appuyez sur Démarrer pour lancer la caméra"))
        self.control_bt.setText(_translate("Form", "Démarrer"))
        self.pushButton.setText(_translate("Form", "Fermer"))
        self.label_2.setText(_translate("Form", "LOG"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Form = QtWidgets.QWidget()
    ui = Ui_Form()
    ui.setupUi(Form)
    Form.show()
    sys.exit(app.exec_())
