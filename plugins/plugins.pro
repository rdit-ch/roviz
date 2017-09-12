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
SUBDIRS += tvg

# Simulation only items
equals(BACKEND, "Dev") {
SUBDIRS += tpg
SUBDIRS += tig
}
