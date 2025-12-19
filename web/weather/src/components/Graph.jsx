import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
} from "chart.js";

import { Line } from "react-chartjs-2";

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
);

function Graph(props) {
  const data = {
    labels: props.labels,
    datasets: [
      {
        label: "Temperature:",
        fill: false,
        lineTension: 0.3,
        backgroundColor: props.maxColor,
        borderColor: props.maxColor,
        data: props.max,
      },
      {
        label: "Temperature:",
        fill: false,
        lineTension: 0.3,
        backgroundColor: props.minColor,
        borderColor: props.minColor,
        data: props.min,
      },
    ],
  };

  const options = {
    scales: {
      x: {
        ticks: {
          color: "#cdd6f4",
        },
      },
      y: {
        ticks: {
          color: "#cdd6f4",
        },
      },
    },
    plugins: {
      legend: {
        display: false,
      },
    },
  };

  return (
    <div className="card bigCard">
      <Line options={options} data={data} />
    </div>
  );
}

export default Graph;
