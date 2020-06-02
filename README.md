# Pupil Tracking - University of Michigan Transportation Research Institute

An OpenCV based pupil tracker based on a simple image gradient-based eye center algorithm based off Fabian Timm's algorithm and adapted from the eyeLike program written by Tristan Hume.

## Requirements
- [OpenCV](https://github.com/opencv/opencv)
- [OpenCV-Contrib](https://github.com/opencv/opencv_contrib)

## Import files
Requires a csv file as input that provides coordinates of head and eye. My implementation using OpenCV's deep neural network face detector and Dlib's facial landmark predictor can be found [here](https://github.com/lbouz102/FeatureTracking-UMTRI).

## Credits
- [Using Fabian Timm's Algorithm](https://www.researchgate.net/publication/221415814_Accurate_Eye_Centre_Localisation_by_Means_of_Gradients)
- [Adapted findPupil.cpp from Tristan Hume's eyeLike program](https://github.com/trishume/eyeLike)

Timm and Barth. Accurate eye centre localisation by means of gradients.
In Proceedings of the Int. Conference on Computer Theory and
Applications (VISAPP), volume 1, pages 125-130, Algarve, Portugal,
2011. INSTICC.
