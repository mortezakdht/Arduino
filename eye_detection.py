import cv2
import serial
import time


ser = serial.Serial('COM3', 9600)  

eye_cascade = cv2.CascadeClassifier(r'C:\Users\morte\OneDrive\Desktop\Arduino\Projet\Projet4\haarcascade_eye.xml')

# Open a webcam
cap = cv2.VideoCapture(0)

# Initialize LED state
led_state = "off"

while True:
    ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detect eyes in the frame
    eyes = eye_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

    # If eyes are detected, consider them as open
    if len(eyes) > 0:
        eye_state = "open"
    else:
        eye_state = "closed"

    # Send the eye state to Arduino only when it changes
    if eye_state != led_state:
        led_state = eye_state
        ser.write(led_state.encode())
        print(f"Eye state: {led_state}")

    # Display the frame with the detected eyes
    cv2.imshow('Eye Detection', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release resources
cap.release()
cv2.destroyAllWindows()
ser.close()