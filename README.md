# QtGoogleAnalytics
# Integration classes between Qt and Google Analytics

// usage example

// main.cpp
// include class your KO ;) 
#include <qgoogleanalytics.h>

// register main class for using in qml
qmlRegisterSingletonType<QGoogleAnalytics>("ua.sp.GoogleAnalytics", 0, 9, "GoogleAnalytics", googleanalytics_qobject_singletontype_provider);

// main.qml
// import registered class for usage
import ua.sp.GoogleAnalytics 0.9

// declare property with registerd class
// I do not know how use singleton clases as object
// but it's normal work as qml object property
property var googleAnalytic: GoogleAnalytics

// init
googleAnalytic.setTID("YOUR-QA-CODE");
googleAnalytic.setScreenSize(Qt.screenWidth, Qt.screenHeight);
googleAnalytic.setOS(Qt.platform.os);

// usage
googleAnalytic.sendScreenview("Game field");
googleAnalytic.sendEvent("Game", "Start", "Level", level);
googleAnalytic.pause(); // stop sending I use when round start in my game
googleAnalytic.resume();
