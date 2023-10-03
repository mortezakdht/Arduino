import cv2
import serial

ser = serial.Serial('COM3', 9600)  

# Load the Haar Cascade classifiers for left and right eyes
left_eye_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_lefteye_2splits.xml')
right_eye_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_righteye_2splits.xml')

# Open a webcam
cap = cv2.VideoCapture(0)

# Initialize LED states for left and right eyes
left_led_state = "off"
right_led_state = "off"

# Initialize previous states
prev_left_led_state = "off"
prev_right_led_state = "off"

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Convert the frame to grayscale for eye detection
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detect left and right eyes in the frame
    left_eyes = left_eye_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))
    right_eyes = right_eye_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

    # Determine the state for the left eye
    if len(left_eyes) > 0:
        left_led_state = "open"
    else:
        left_led_state = "closed"

    # Determine the state for the right eye
    if len(right_eyes) > 0:
        right_led_state = "open"
    else:
        right_led_state = "closed"

    # Send commands to Arduino only when the state changes
    if left_led_state != prev_left_led_state:
        ser.write(left_led_state.encode())
        print(f"Left Eye state: {left_led_state}")
        prev_left_led_state = left_led_state

    if right_led_state != prev_right_led_state:
        ser.write(right_led_state.encode())
        print(f"Right Eye state: {right_led_state}")
        prev_right_led_state = right_led_state

    # Display the frame with the detected eyes
    for (x, y, w, h) in left_eyes:
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
    for (x, y, w, h) in right_eyes:
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

    cv2.imshow('Eye Detection', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release resources
cap.release()
cv2.destroyAllWindows()
ser.close()