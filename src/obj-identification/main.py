from ultralytics import YOLO
import cv2, math

vid = cv2.VideoCapture(1)

model = YOLO("yolo-Weights/yolov8n.pt")

while True:
    ret, img = vid.read() # Read video
    
    if not ret: # Camera not found error
        raise SystemError('Uh oh! Stinky!\nYour camera doesn\'t work.')
        break

    # Draw bounding boxes with labels
    results = model(img, stream=True)
    for r in results:
        boxes = r.boxes

        for box in boxes:
            # Bounding box
            x1, y1, x2, y2 = box.xyxy[0]
            x1, y1, x2, y2 = int(x1), int(y1), int(x2), int(y2) # convert to int values

            # Place box in frame
            cv2.rectangle(img, (x1, y1), (x2, y2), (255, 0, 255), 3)

            # Metrics
            cls = int(box.cls[0]) # Class name (object type)
            confidence = math.ceil((box.conf[0]*100))/100 # Confidence

            # Object details
            try:
                txt = f'{model.names[cls]}, {confidence}'
            except:
                txt = '?'
            org = [x1, y1]
            font = cv2.FONT_HERSHEY_SIMPLEX
            fontScale = 1
            color = (255, 0, 0)
            thickness = 2
            cv2.putText(img, txt, org, font, fontScale, color, thickness)

    cv2.imshow('Object Detection', img)
    if cv2.waitKey(1) == ord('q'):
        break

vid.release()
cv2.destroyAllWindows()