TEMPLATE = subdirs
CONFIG  += ordered

SUBDIRS += frame_delayer
SUBDIRS += gaussian_blur
SUBDIRS += gray_conv
SUBDIRS += subtractor
SUBDIRS += cv_camera
SUBDIRS += canny
SUBDIRS += sobel
SUBDIRS += harris_corner
SUBDIRS += config_message_test
SUBDIRS += image_file
SUBDIRS += video_file

# Dev only items
equals(BACKEND, "Dev") {
SUBDIRS += tpg
}
