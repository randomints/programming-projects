import Graph from "./components/Graph";
import { useState, useEffect } from "react";

const WEATHER_URL =
  "https://api.open-meteo.com/v1/forecast?latitude=25.23&longitude=51.57&current=temperature_2m,wind_speed_10m,precipitation&hourly=temperature_2m,wind_speed_10m,precipitation&timezome=Asia/Qatar";

function App() {
  const [temp, setTemp] = useState(null);
  const [hourlyTemp, setHourlyTemp] = useState([]);
  const [weeklyMax, setWeeklyMax] = useState([]);
  const [weeklyMin, setWeeklyMin] = useState([]);
  const [windSpeed, setWindSpeed] = useState("");
  const [precipitation, setPrecipitation] = useState("");

  function weeklyMinMax(json, type) {
    let arr = [];
    for (let i = 0; i < 7; i++) {
      let day = json.hourly.temperature_2m.slice(i * 24, i * 24 + 24);

      if (type == true) {
        arr.push(Math.min(...day));
      } else {
        arr.push(Math.max(...day));
      }
    }
    return arr;
  }

  useEffect(() => {
    const fetchData = async () => {
      const response = await fetch(WEATHER_URL);
      const json = await response.json();
      setTemp(json.current.temperature_2m);
      console.log(json);

      setHourlyTemp(json.hourly.temperature_2m.slice(0, 24));
      setWeeklyMax(weeklyMinMax(json, false));
      setWeeklyMin(weeklyMinMax(json, true));
      setWindSpeed(`${json.current.wind_speed_10m} km/h`);
      setPrecipitation(`${json.current.precipitation} ml`);
    };
    fetchData();
  }, []);

  return (
    <>
      <div className="appArea">
        <h1>{temp}°C</h1>
        <Graph
          labels={[
            "12AM",
            "",
            "",
            "",
            "",
            "",
            "6AM",
            "",
            "",
            "",
            "",
            "",
            "12PM",
            "",
            "",
            "",
            "",
            "",
            "6PM",
            "",
            "",
            "",
            "",
            "",
          ]}
          min={hourlyTemp}
          max={[]}
          minColor={"rgba(249, 226, 175, 1)"}
        />

        <Graph
          labels={["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"]}
          max={weeklyMax}
          min={weeklyMin}
          maxColor={"rgba(243, 139, 168, 1)"}
          minColor={"rgba(137, 180, 250, 1)"}
        />

        <div className="card smallCard">
          <div>
            <h3>Wind Speed</h3>
            <p>{windSpeed}</p>
          </div>

          <div>
            <h3>Precipitation</h3>
            <p>{precipitation}</p>
          </div>

          <div>
            <h3>Coordinates</h3>
          </div>
        </div>
      </div>
    </>
  );
}

export default App;
