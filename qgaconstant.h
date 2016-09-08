#ifndef QGACONSTANT_H
#define QGACONSTANT_H

#include "cpp/qgameconstant.h" // to take APPLCATION contstants
#ifndef ORGANIZATION_NAME
#define ORGANIZATION_NAME "Steel Programming"
#endif
#ifndef APPLICATION_NAME
#define APPLICATION_NAME "GoogleAnalytics Module"
#endif

#ifndef APPLICATION_TITLE
#define APPLICATION_TITLE "Google Analytics Module"
#endif
#ifndef APPLICATION_VERSION
#define APPLICATION_VERSION "0.0.1"
#endif
#ifndef APPLICATION_PACKAGE
#define APPLICATION_PACKAGE "ua.com.sprogram.GoogleAnalyticsModule
#endif

#ifndef APPLICATION_INSTALLER_PACKAGE
#define APPLICATION_INSTALLER_PACKAGE ""
#endif

#define GA_SENDING_FREQUENCY 5000

#define GA_ITEM_TYPE_NONE 0
#define GA_ITEM_TYPE_EVENT 1
#define GA_ITEM_TYPE_PAGEVIEW 2
#define GA_ITEM_TYPE_SCREENVIEW 3

#define GA_ITEM_STATUS_NONE 0
#define GA_ITEM_STATUS_SENDING 1
#define GA_ITEM_STATUS_SEND 2

#define GA_PAUSE_TIME_DEF 5

#endif
