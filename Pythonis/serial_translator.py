# Imports
import serial
from pynput.keyboard import Key, Controller, Listener


# Serial data Processing functions
def splitprocess(split):
    "Processes each element in the "
    processed = split.strip().split(":")
    processed = [s.strip() for s in processed]
    return processed


def serProcess(serdata):
    """Process serial data one line at a time"""
    decoded = serdata.decode()
    splitted = decoded.replace("\n", "").split("\t")
    splitsmap = dict(map(splitprocess, splitted))
    act_keys = ["Roll", "Pitch", "Rbutt", "Bbutt"]
    if (len(splitsmap) > 4) or list(splitsmap.keys()) != act_keys:
        raise ValueError("Format incorrect!")
    return splitsmap


def on_press(key):
    global flag
    if key == Key.tab:  # Exit program on press of tab
        # print("pressed")
        flag = False


def mainloop():
    # Serial and loop defs
    ser = serial.Serial(port="/dev/ttyUSB1", baudrate=115200)
    flag = True

    # Keyboard defs
    keypresser = Controller()
    listener = Listener(on_press=on_press)
    listener.start()

    # Defining key maps for values
    RollKeyMaps = {'flat': None, 'left': Key.left, 'right': Key.right}
    PitchKeyMaps = {'flat': None, 'front': Key.up, 'back': Key.down}
    RbuttKeyMaps = {'No press': None, 'Pressed': Key.shift}
    BbuttKeyMaps = {'No press': None, 'Pressed': Key.space}

    while (flag):
        # processing serial data
        serData = ser.readline()
        try:
            serProcessed = serProcess(serData)
            print(serProcessed)
            excepts = []
        except Exception as e:
            print(f"Exception occurred in processing: {e}")
            excepts.append(e)
            if len(excepts) > 250:  # If data isn't proper for 5 seconds break
                break
            else:
                continue
        # Doing key press
        rollKey = RollKeyMaps[serProcessed["Roll"]]
        pitchKey = PitchKeyMaps[serProcessed["Pitch"]]
        rButtKey = RbuttKeyMaps[serProcessed["Rbutt"]]
        bButtKey = BbuttKeyMaps[serProcessed["Bbutt"]]

        # print(rollState)

        if rollKey is not None:
            keypresser.press(rollKey)
            print("pressed")
        if pitchKey is not None:
            keypresser.press(pitchKey)
        if rButtKey is not None:
            keypresser.press(rButtKey)
        if bButtKey is not None:
            keypresser.press(bButtKey)

    listener.stop()
    ser.close()
    exit()


mainloop()