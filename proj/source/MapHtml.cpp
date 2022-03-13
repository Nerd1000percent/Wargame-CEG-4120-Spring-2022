#include "Map.h"
#include "Unit.h"
#include "nlohmann/json.hpp"

#include <sstream>

const std::string Map::HTML_TEMPLATE = R"(
<!DOCTYPE html>
<html>
<head>
    <style>
        .grid-container {
            display: grid;
            grid-template-columns: ${COLUMNS};
            gap: 10px;
            background-color: #3F3F3F;
            padding: 10px;
            align-content: space-around;
        }
            .grid-container > desert {
                display: grid;
                grid-template-columns: auto;
                background-color: rgb(184 105 41);
                border: 10px solid black;
                text-align: center;
                font-size: 10px;
                height: ${ROW_HEIGHT}px;
                color: black;
            }

            .grid-container > plains {
                display: grid;
                grid-template-columns: auto;
                background-color: rgb(48 150 39);
                border: 10px solid black;
                text-align: center;
                font-size: 10px;
                height: ${ROW_HEIGHT}px;
                color: black;
            }

        .red_button {
            background-color: rgba(0, 0, 0, 0.0);
            border: 10px solid red;
            color: white;
            padding: 15px 32px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 50px;
        }

        .blue_button {
            background-color: rgba(0, 0, 0, 0.0);
            border: 10px solid blue;
            color: white;
            padding: 15px 32px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 50px;
        }

    </style>
</head>
<body>

    <script>
        const mapjson = '${MAP_JSON}';
        var mapdata = JSON.parse(mapjson);

        function getTile(row, col) {
            let dims = mapdata.map.dimensions;
            let rows = dims[0];
            let cols = dims[1];
            let index = cols * row + col;
            let tile = mapdata.map.data[index];
            return tile;
        }

        function getUnits(row, col) {
            let tile = getTile(row, col);
            return tile.units;
        }
    </script>

    <h1>Wargame</h1>

    <p>TODO: put some html here to describe the output below.</p>

    <div class="grid-container">
${TILES}
    </div>
    <p>Units appear below when you click an occupied button above.</p>
    <h2><p id="metadata"></p></h2>
</body>
</html>
)";

std::string Map::getRowHeightHtml() const
{
  return std::to_string(ROW_HEIGHT);
}

std::string Map::getMapJsonHtml() const
{
  nlohmann::json j = *this;
  return j.dump();
}

std::string Map::getTilesHtml() const
{
  size_t rows = m_arrayOfTiles.getDimension(0);
  size_t columns = m_arrayOfTiles.getDimension(1);
  std::stringstream ss;
  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < columns; j++)
    {
      auto& tile = m_arrayOfTiles.at({ i, j });
      auto terrain = tile.getTerrain();
      auto team = tile.getTeam();
      auto units = tile.getUnits();

      double attack = 0;
      double defense = 0;
      for (auto u : units)
      {
        attack += u->getAttackPower();
        defense += u->getDefensePower();
      }
      ss << "        <" << terrain.getName() << ">";
      if (!team.empty())
      {
        ss << R"(<button type="button" class=")" << team << R"(_button" onclick="document.getElementById('metadata').innerHTML = JSON.stringify(window.getUnits)";
        ss << "(" << i << ", " << j << "))\">";
        ss << attack << "/" << defense << "</button>";
      }
      ss << "</" << terrain.getName() << ">" << std::endl;
    }
    ss << std::endl;
  }
  return ss.str();
}

std::string Map::getColumnsHtml() const
{
  size_t columns = m_arrayOfTiles.getDimension(1);
  std::stringstream ss;
  for (size_t j = 0; j < columns; j++)
    ss << (j + 1 < columns ? "auto " : "auto");
  return ss.str();
}

std::string Map::mapToHtml()
{
  std::stringstream ss;
  size_t prevTag = 0;

  // start with the HTML_TEMPLATE.  iterate over all the tags and 
  // replace them with the helper functions.
  for (auto startTag = HTML_TEMPLATE.find('$'); startTag != std::string::npos; startTag=HTML_TEMPLATE.find('$', prevTag))
  {
    // copy the portion of the HTML_TEMPLATE from the prevTag to the current tag
    ss << HTML_TEMPLATE.substr(prevTag, startTag - prevTag);
    auto endTag = HTML_TEMPLATE.find('}', startTag);

    // extract the tag variable
    auto tag = HTML_TEMPLATE.substr(startTag + 2, endTag - startTag - 2);

    // replace the tag with info from the helper function
    ss << (this->*HTML_TAGS.at(tag))();

    // skip to the end of the tag
    prevTag = endTag+1;
  }

  // need to finish copying from the prevTag
  ss << HTML_TEMPLATE.substr(prevTag);
  return ss.str();
}
