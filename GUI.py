from PyQt5.QtWidgets import *
from PyQt5 import QtCore, QtGui
from PyQt5.QtGui import *
from PyQt5.QtCore import *

import sys
import serial

ser = serial.Serial('com4', 19200)
ser.flushInput()

class boxSelect(QComboBox):
    def __init__(self, parent=None):
        super(boxSelect, self).__init__(parent)    

class App(QWidget):
    def __init__(self):
        super().__init__()
        self.title = 'AutoFan'
        self.left = 10
        self.top = 10
        self.width = 400
        self.height = 100
        self.initUI()

    # GUI
    def initUI(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        self.temperature = QLineEdit(self)
        self.temperature.move(20, 20)

        self.combo_box = boxSelect(self)
        self.combo_box.setGeometry(300, 300, 100, 25)
        self.combo_box.move(165, 20)
        degrees = ["Fahrenheit", "Celcius"]
        self.combo_box.addItems(degrees)


        change_temp = QPushButton("Set Temp", self)
        change_temp.setToolTip("Sets minimum temperature to turn on fan")
        change_temp.move(275, 20)
        change_temp.clicked.connect(self.set_temp)
    
        self.show()
    

    @pyqtSlot()
    def set_temp(self):
        try:
            degree = str(self.combo_box.currentText())
            temp = float(self.temperature.text())
            if degree == "Celcius":
                final_temp = str((temp * 1.8) + 32)
                ser.write(bytes(final_temp, "utf-8"))
            else:
                final_temp = str(temp)
                ser.write(bytes(final_temp, "utf-8"))
            self.temperature.setText("")
        except:
            pass


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = App()
    sys.exit(app.exec_())

