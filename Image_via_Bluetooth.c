#include "opencv.hpp"
#include <stdio.h>

int main() {
    // Open the default webcam (0 for the first camera)
    cv::VideoCapture cap(0);

    // Check if the webcam opened successfully
    if (!cap.isOpened()) {
        printf("Error: Could not open webcam\n");
        return -1;
    }

    cv::Mat frame;
    while (1) 
        // Capture a new frame from the webcam
        cap >> frame;

        // Check if the frame is empty
        if (frame.empty()) {
            printf("Error: Could not capture frame\n");
            break;
        }

        // Display the frame in a window
        cv::imshow("Webcam Feed", frame);

        // Break the loop if 'q' is pressed
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }

    // Release the webcam
    cap.release();
    cv::destroyAllWindows();
    return 0;
}
