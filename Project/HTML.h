#ifndef HTML_HEADER
#define HTML_HEADER

#define EMBED_FILE(...) #__VA_ARGS__;

namespace HTML {
  static const char* IndexPage =
  #include "HTMLIndex.h"

  static const char* PanelPage = 
  #include "HTMLPanel.h"

  static const char* SettingsPage =
  #include "HTMLSettings.h"

  static const char* Stylesheet =
  #include "HTMLStylesheet.h"
}

#endif