import rclpy
import math
from rclpy.node import Node
from turtlesim.srv import TeleportAbsolute
from std_srvs.srv import Empty
from geometry_msgs.msg import Twist

class MyPublisher(Node):

    def __init__(turtle):
        super().__init__('my_publisher')
        turtle.publisher = turtle.create_publisher(Twist, '/turtle1/cmd_vel', 10)
        turtle.timer = turtle.create_timer(2.0, turtle.timer_callback)
        turtle.count = 0

    def teleport_absolute(turtle, x, y, theta):
        teleport_service = turtle.create_client(TeleportAbsolute, '/turtle1/teleport_absolute')
        while not teleport_service.wait_for_service(timeout_sec=1.0):
            turtle.get_logger().info('Waiting for the teleport_absolute service!!!')

        request = TeleportAbsolute.Request()
        request.x = 7.5
        request.y = 5.0
        request.theta = 0.0  

        future = teleport_service.call_async(request)
        rclpy.spin_until_future_complete(turtle, future)
        turtle.get_logger().info('Teleportation complete.')

    def clear_turtlesim(turtle):
        clear_service = turtle.create_client(Empty, '/clear')
        while not clear_service.wait_for_service(timeout_sec=1.0):
            turtle.get_logger().info('Waiting for the clear service!!!')

        empty_request = Empty.Request()
        clear_future = clear_service.call_async(empty_request)
        rclpy.spin_until_future_complete(turtle, clear_future)
        turtle.get_logger().info('Clearing complete')

    def timer_callback(turtle):
        if turtle.count < 6:
            if turtle.count % 2 == 0:
                msg = Twist()
                msg.angular.z = 2.07774
                turtle.get_logger().info('Rotate')
            else:
                msg = Twist()
                msg.linear.x = 4.0
                turtle.get_logger().info('Move Forward')
        elif turtle.count >= 6 and turtle.count < 12:
            if turtle.count % 2 == 1:
                msg = Twist()
                msg.angular.z = math.radians(177.7)
                msg.linear.x = 2 * math.pi - 0.025
                turtle.get_logger().info('Move')
            elif turtle.count == 6:
                msg=Twist()
                msg.angular.z = math.radians(30)
                turtle.get_logger().info('Rotate')
            else:
                msg=Twist()
                msg.angular.z = math.radians(-60)
                turtle.get_logger().info('Rotate')
        elif turtle.count == 12: 
            return
        
        turtle.count += 1
        turtle.publisher.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    my_publisher = MyPublisher()
    try:
        my_publisher.teleport_absolute(7.5, 5.0, 0.0)
        my_publisher.clear_turtlesim()
        rclpy.spin(my_publisher)

    finally:
        my_publisher.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()