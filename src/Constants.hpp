#ifndef CONFIG_CONSTANTS_HPP
#define CONFIG_CONSTANTS_HPP

#include <QtCore/QString>

namespace config
{
inline QString const DEFAULT_IMAGE{"default"};

inline QString const NAME{"name"};

}
namespace config::paths
{
inline QString const DATABASE_PATH{"/database"};

inline QString const EXPORT_PATH{"/export"};

inline QString const IMAGE_PATH{"/images"};
}

namespace config::tools
{
inline QString const GENERAL{"general"};

inline QString const BUBBLE_VIEW{"bubbleView"};

inline QString const ZOOM_MAPS{"zoomMaps"};

inline QString const CODE_CHARTS{"codeCharts"};

inline QString const EYE_TRACKING{"eyeTracking"};

inline QString const DATA_CLIENT{"dataClient"};

inline QString const DATABASE{"database"};
}


#endif //CONFIG_CONSTANTS_HPP
