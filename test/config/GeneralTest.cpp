#include <doctest/doctest.h>

#include <config/General.hpp>

#include <QtCore/QCoreApplication>
#include <QtCore/QJsonObject>
#include <QtCore/QString>

#include <iomanip>
#include <unordered_map>

using namespace config;

std::ostream &operator<<(std::ostream &os, QString const &str)
{
    if (str.isNull()) {
        return os << "<NULL>";
    }
    return os << std::quoted(str.toStdString());
}

TEST_CASE("config/GeneralTest")
{
    SUBCASE("load") {
        SUBCASE("Tool") {
            static std::unordered_map<QString, General::Tool> const TOOLS{
                {"bubbleView", General::Tool::BubbleView},
                {"zoomMaps", General::Tool::ZoomMaps},
                {"codecharts", General::Tool::CodeCharts},
                {"eyeTracking", General::Tool::EyeTracking},
                {"dataClient", General::Tool::DataClient},
            };

            for (auto const &[toolName, toolValue]: TOOLS) {
                SUBCASE(toolName.toStdString().c_str()) {
                    QJsonObject const object{
                        {"activatedTool", toolName},
                        {"masterPath", "dummy"},
                        {"imagePath", "dummy"},
                        {"exportPath", "dummy"},
                        {"displayMode", "fullScreen"},
                    };

                    auto const config = General::load(object);
                    CHECK(config.activatedTool == toolValue);
                }
            }
        }

        SUBCASE("Paths") {
            SUBCASE("Empty strings default to sub paths") {
                int argc{1};
                char app_name[] = "test";
                char *argv[] = {app_name};
                QCoreApplication app{argc, argv};

                static std::unordered_map<QString, QString> const EMPTY_PATHS{
                    {"null", {}},
                    {"empty", ""},
                };

                for (auto const &[name, path]: EMPTY_PATHS) {
                    SUBCASE(name.toStdString().c_str()) {
                        QJsonObject const object{
                            {"activatedTool", {}},
                            {"masterPath", "/dummy"},
                            {"imagePath", path},
                            {"exportPath", path},
                            {"displayMode", "fullScreen"},
                        };

                        auto const config = General::load(object);
                        CHECK(config.masterPath == "/dummy");
                        CHECK(config.imagePath == "/dummy/images");
                        CHECK(config.exportPath == "/dummy/export");
                    }
                }
            }
        }

        SUBCASE("Non-empty path") {
            QJsonObject const object{
                {"activatedTool", {}},
                {"masterPath", "/dummy"},
                {"imagePath", "/images"},
                {"exportPath", "/export"},
                {"displayMode", "fullScreen"},
            };

            auto const config = General::load(object);
            CHECK(config.masterPath == "/dummy");
            CHECK(config.imagePath == "/images");
            CHECK(config.exportPath == "/export");
        }
    }
}
