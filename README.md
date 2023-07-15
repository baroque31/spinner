

# Welcome to Spinner

Spinner is a program which generates gcode for 3D printing “spun
shells”, these are spiral prints created by “spinning” a 2D “profile” of
points. The profiles may have extraordinary overhangs and Spinner will
continuously adjust the layer height to insure a clean print. See the
complete Manual in the ***doc*** directory.

# What this repo contains:

This repo will build two executable objects:

1.  The *spinner* itself. This will end up in spinner/spinner following
    the build. This program is used to convert profile data to gcode. It
    uses a json file to configure basic printer and model
    characteristics.
2.  The *profile maker*. This will end up in profile_maker/profile_maker.
    This program contains a number of examples which use the geometry
    library to develop curved profiles. You must modify this program, or
    make your own to develop your own profile shapes.

# To Build:
As far as I know, this builds only on Linux.  It uses at least one C++20 feature. I expect it would compile fine under windows with g++.

1.  The **jsoncpp** library is required and must be installed to build (<https://github.com/open-source-parsers/jsoncpp>)
2.  cd src
3.  make

The resulting executables are src/spinner/spinner and
src/profile_maker/profile_maker
