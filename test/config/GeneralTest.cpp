#include <doctest/doctest.h>

#include <config/General.hpp>

#include <QtCore/QJsonObject>
#include <QtCore/QString>

using namespace config;

TEST_CASE("config/GeneralTest")
{
    SUBCASE("load") {
        SUBCASE("Tool") {
            static QMap<QString, General::Tool> const tools{
                {"bubbleView", General::Tool::BubbleView},
                {"zoomMaps", General::Tool::ZoomMaps},
                {"codecharts", General::Tool::CodeCharts},
                {"eyeTracking", General::Tool::EyeTracking},
                {"dataClient", General::Tool::DataClient},
            };

            for (auto it = tools.keyBegin(); it != tools.keyEnd(); ++it) {
                auto const tool = *it;
                SUBCASE(tool.toStdString().c_str()) {
                    QJsonObject const object{
                        {"activatedTool", tool},
                        {"masterPath", ""},
                        {"imagePath", ""},
                        {"exportPath", ""},
                        {"displayMode", "fullScreen"},
                    };

                    auto const config = General::load(object);
                    CHECK(config.activatedTool == tools[tool]);
                }
            }
        }
    }
}
