import { useState } from "react";
import "./App.css";

const WEATHER_URL =
  "https://api.open-meteo.com/v1/forecast?latitude=52.52&longitude=13.41&current=temperature_2m,wind_speed_10m&hourly=temperature_2m,relative_humidity_2m,wind_speed_10m";

function App() {
  const [temp, setTemp] = useState(0);

  function fetchData() {
    fetch(WEATHER_URL)
      .then((response) => {
        if (!response.ok) {
          throw new Error(`HTTP error: ${response.status}`);
        }

        return response.json();
      })
      .then((json) => {
        setTemp(json.current.temperature_2m);
      });
  }

  fetchData("01-01-2025");

  return (
    <>
      <div className="appArea">
        <h1>{temp}</h1>
      </div>
    </>
  );
}

export default App;
