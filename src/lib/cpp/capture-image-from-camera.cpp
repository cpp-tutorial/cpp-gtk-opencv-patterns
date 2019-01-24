#include "capture-image-from-camera.hpp"

CaptureImageFromCamera::CaptureImageFromCamera():
captureThread(nullptr),
propagateThread(nullptr),
lastFrameSystemClock(std::chrono::system_clock::now()),
videoCapture(0) {
    startCapturing();
}

CaptureImageFromCamera::~CaptureImageFromCamera() {
    stopCapturing();
}

void CaptureImageFromCamera::startCapturing() {
    if (!captureThread) {
        keepCapturing = true;
        captureThread = new std::thread([this] {
            doCapture();
        });
    }
}

void CaptureImageFromCamera::stopCapturing() {
    if (captureThread) {
        keepCapturing = false;
        captureThread->join();
        free(captureThread);
        captureThread = nullptr;
    }
    if (propagateThread) {
        propagateThread->join();
        free(propagateThread);
        propagateThread = nullptr;
    }
}

void CaptureImageFromCamera::doCapture() {
    do {
        videoCapture.grab();
        videoCapture.grab();
        videoCapture.grab();
        videoCapture.read(webcam);
        if (webcam.size().width > 0) {
            doPropagate();
            updateFrameRate();
        }
    } while (keepCapturing);
}

void CaptureImageFromCamera::updateFrameRate() {
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    std::chrono::duration<float> difference = now - lastFrameSystemClock;
    
    frameRate = 1 / difference.count();
}

float CaptureImageFromCamera::getFrameRate() {
    return frameRate;
}

void CaptureImageFromCamera::doPropagate() {
    if (propagateThread) {
        propagateThread->join();
    }
    propagateThread = new std::thread([this] {
        eventBus.propagate(EventImageCaptured(webcam));
    });
}

EventImageCaptured::EventImageCaptured(cv::Mat i):
capturedImage(i){
}

cv::Mat EventImageCaptured::getCapturedImage() {
    return capturedImage;
}
