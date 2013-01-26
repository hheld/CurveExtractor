# CurveExtractor

## Idea
Many applications require the user to input characteristic data for technical components stemming from diagrams
that are available only on a piece of paper or an already scanned image. It is usually quite challenging to extract
a good approximation of curves as data points by hand.

The tool 'CurveExtractor' tries to make this easy and convenient:

1. the user loads an image file
2. the origin and measurement dimensions can easily be set up
3. double-clicking on the shown image adds data points; once created, those can be moved or deleted again (by right-clicking on them)
4. immediately, a best fitting curve is computed and displayed in the background (various curve types for fitting are available)
5. if the user likes the fitted curve, the data points can be saved to a CSV file for further processing

## Tools
CurveExtractor is written in C++ using Qt5 which you can get here:
http://qt-project.org/downloads

The curve fitting is done by solving a (non-)linear least square optimization problem with the solver 'Ceres' available at:
http://code.google.com/p/ceres-solver/

## License
CurveExtractor is released under the New BSD License.

## Screenshots
[See screenshots here](Screenshots)
