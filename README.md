# for Qt5 please use 
# https://github.com/Larpon/QtFirebase

# QtGoogleAnalytics
# Integration classes between Qt and Google Analytics

// usage example

// main.cpp<br>
// include class your KO ;) <br>
#include <qgoogleanalytics.h><br>

// register main class for using in qml<br>
qmlRegisterSingletonType<QGoogleAnalytics>("ua.sp.GoogleAnalytics", 0, 9, "GoogleAnalytics", googleanalytics_qobject_singletontype_provider);

// main.qml<br>
// import registered class for usage<br>
import ua.sp.GoogleAnalytics 0.9

// declare property with registerd class<br>
// I do not know how use singleton clases as object<br>
// but it's normal work as qml object property<br>
property var googleAnalytic: GoogleAnalytics<br>

// init<br>
googleAnalytic.setTID("YOUR-QA-CODE");<br>
googleAnalytic.setScreenSize(Qt.screenWidth, Qt.screenHeight);<br>
googleAnalytic.setOS(Qt.platform.os);<br>

// usage
googleAnalytic.sendScreenview("Game field");<br>
googleAnalytic.sendEvent("Game", "Start", "Level", level);<br>
googleAnalytic.pause(); // stop sending I use when round start in my game <br>
googleAnalytic.resume();
