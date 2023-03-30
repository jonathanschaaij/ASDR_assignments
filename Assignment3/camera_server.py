import cv2
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
from flask import Flask, Response
import threading

app = Flask(__name__)
bridge = CvBridge()
frame = None
lock = threading.Lock()

class CameraSubscriber(Node):
    def __init__(self):
        super().__init__('camera_subscriber')
        self.subscription = self.create_subscription(
            Image,
            'camera',
            self.listener_callback,
            10
        )
        self.subscription

    def listener_callback(self, msg):
        global frame, lock
        with lock:
            frame = bridge.imgmsg_to_cv2(msg, 'bgr8')

def generate():
    global frame, lock
    while True:
        with lock:
            if frame is not None:
                ret, buffer = cv2.imencode('.jpg', frame)
                yield (b'--frame\r\n'
                       b'Content-Type: image/jpeg\r\n\r\n' + buffer.tobytes() + b'\r\n')

@app.route('/image')
def video_feed():
    return Response(generate(), content_type='multipart/x-mixed-replace; boundary=frame')

def main(args=None):
    rclpy.init(args=args)
    camera_subscriber = CameraSubscriber()
    thread = threading.Thread(target=rclpy.spin, args=(camera_subscriber,))
    thread.start()

    app.run(host='0.0.0.0', port=1234)

    rclpy.shutdown()
    thread.join()

if __name__ == '__main__':
    main()

