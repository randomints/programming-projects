const locationSelect = document.querySelector(".geo");
const manualForm = document.querySelector(".manual");
const manualText = document.querySelector(".manualText");
var area;
var latitude;
var longitude;

const nextPrayer = document.querySelector(".item4");
var nextPrayerData;
var nextPrayerUrl;
const todayFajr = document.querySelector(".fajrTime");
const todayDhuhr = document.querySelector(".thuhrTime");
const todayAsr = document.querySelector(".asrTime");
const todayMagrib = document.querySelector(".magribTime");
const todayIsha = document.querySelector(".ishaTime");
var todayPrayerData;
var todayPrayerUrl;

const calendar = document.querySelector(".item2");
const calendarDates = document.querySelector(".dates");
const calendarMonth = document.querySelector("h3");
var days;
var specialDays;
var holidays = [];

const dateInput = document.querySelector(".dateInput");
const dateButton = document.querySelector(".dateButton");
const dateLabel = document.querySelector(".dateLabel");
const dateOutput = document.querySelector(".dateOutput");
const dateForm = document.querySelector(".dateForm");
var gregorianToHijriToggle = true;

var currentTime = new Date();
const day = currentTime.getDate();
const month = currentTime.getMonth() + 1;
const year = currentTime.getFullYear();

function updateAreaManual(e) {
  e.preventDefault();
  area = manualText.value.split(/[,]+/);
  console.log("Submitted value:", area);
  changeUrl();
}

manualForm.addEventListener("submit", updateAreaManual);
locationSelect.addEventListener("change", changeUrl);
dateForm.addEventListener("submit", (e) => {
  e.preventDefault();

  console.log(dateInput.value);
  if (gregorianToHijriToggle) {
    gregorianToHijri(dateInput.value);
  } else {
    hijriToGregorian(dateInput.value);
  }
});

dateButton.addEventListener("click", (e) => {
  e.preventDefault();
  gregorianToHijriToggle = !gregorianToHijriToggle;
});

navigator.geolocation.getCurrentPosition((position) => {
  latitude = position.coords.latitude;
  longitude = position.coords.longitude;
});

function changeUrl() {
  if (locationSelect.value == "Manual") {
    manualForm.style.visibility = "visible";

    todayPrayerUrl = `https://api.aladhan.com/v1/timingsByCity?city=${area[0]}&country=${area[1]}`;
    nextPrayerUrl = `https://api.aladhan.com/v1/nextPrayerByAddress/${day}-${month}-${year}?address=${encodeURIComponent(`${area[0]},${area[1]}`)}`;
  }
  if (locationSelect.value == "Approximate") {
    manualForm.style.visibility = "hidden";
    nextPrayerUrl = `https://api.aladhan.com/v1/nextPrayer/${day}-${month}-${year}?latitude=${Math.ceil(Math.round(latitude) / 10) * 10}&longitude=${Math.ceil(Math.round(longitude) / 10) * 10}`;
    todayPrayerUrl = `https://api.aladhan.com/v1/timings/${day}-${month}-${year}?latitude=${Math.ceil(Math.round(latitude) / 10) * 10}&longitude=${Math.ceil(Math.round(longitude) / 10) * 10}`;
  }
  if (locationSelect.value == "Precise") {
    manualForm.style.visibility = "hidden";
    nextPrayerUrl = `https://api.aladhan.com/v1/nextPrayer/${day}-${month}-${year}?latitude=${latitude}&longitude=${longitude}`;
    todayPrayerUrl = `https://api.aladhan.com/v1/timings/${day}-${month}-${year}?latitude=${latitude}&longitude=${longitude}`;
  }
  fetchNextPrayerData();
  fetchTodayPrayerData();
}


function fetchNextPrayerData() {
  fetch(nextPrayerUrl)
    .then((response) => {
      if (!response.ok) {
        throw new Error(`HTTP error: ${response.status}`);
      }

      return response.json();
    })
    .then((json) => {
      nextPrayerData = json;
      updateNextPrayer();
    });
}


function updateNextPrayer() {
  const keys = Object.keys(nextPrayerData.data.timings);
  for (let key of keys) {
    nextPrayer.textContent = `Next Prayer: ${key}, at ${nextPrayerData.data.timings[key]}`;
  }
  nextPrayer.textContent
}

function fetchTodayPrayerData() {
  fetch(todayPrayerUrl)
    .then((response) => {
      if (!response.ok) {
        throw new Error(`HTTP error: ${response.status}`);
      }

      return response.json();
    })
    .then((json) => {
      todayPrayerData = json;
      updateTodayPrayer();
    });
}

function updateTodayPrayer() {
  todayFajr.textContent = `Fajr: ${todayPrayerData.data.timings.Fajr}`;
  todayDhuhr.textContent = `Thuhr: ${todayPrayerData.data.timings.Dhuhr}`;
  todayAsr.textContent = `Asr: ${todayPrayerData.data.timings.Asr}`;
  todayMagrib.textContent = `Maghrib: ${todayPrayerData.data.timings.Maghrib}`;
  todayIsha.textContent = `Isha: ${todayPrayerData.data.timings.Isha}`;
}

function fetchSpecialDays() {
  fetch("https://api.aladhan.com/v1/specialDays")
    .then((response) => {
      if (!response.ok) {
        throw new Error(`HTTP error: ${response.status}`);
      }

      return response.json();
    })
    .then((json) => {
      specialDays = json;
      getHolidays();
      updateCalendar();
    });
}

function getHolidays() {
  holidays = [];

  for (let i = 0; i < specialDays.data.length; i++) {
    if (specialDays.data[i].name == "Eid-ul-Adha" || specialDays.data[i].name == "Eid-ul-Fitr" || specialDays.data[i].name == "End of the holy months" || specialDays.data[i].name == "Lailat-ul-Qadr" || specialDays.data[i].name == "Beginning of the holy months" || specialDays.data[i].name == "1st Day of Ramadan") {
      holidays.push(specialDays.data[i]);
    }
  }
}

function updateCalendar() {
  calendarDates.innerHTML = "";
  days = new Date(year, month, 0).getDate();

  for (let i = 1; i < days + 1; i++) {
    let day = document.createElement("p");
    day.textContent = i;
    for (let k = 0; k < holidays.length; k++) {
      if (month == holidays[k].month && i == holidays[k].day) {
        if (holidays[k].name == "Eid-ul-Fitr") { day.style.color = "red"; }
        if (holidays[k].name == "Eid-ul-Adha") { day.style.color = "blue"; }
        if (holidays[k].name == "Lailat-ul-Qadr") { day.style.color = "green"; }
        if (holidays[k].name == "End of the holy months") { day.style.color = "orange"; }
        if (holidays[k].name == "Beginning of the holy months") { day.style.color = "purple"; }
        if (holidays[k].name == "1st Day of Ramadan") { day.style.color = "pink"; }
      }
    }
    calendarDates.appendChild(day);
  }
}

function hijriToGregorian(date) {
  fetch(`https://api.aladhan.com/v1/hToG/${date}?calendarMethod=UAQ`)
    .then((response) => {
      if (!response.ok) {
        throw new Error(`HTTP error: ${response.status}`);
      }

      return response.json();
    })
    .then((json) => {
      dateOutput.textContent = json.data.gregorian.date;
    });
}

function gregorianToHijri(date) {
  fetch(`https://api.aladhan.com/v1/gToH/${date}?calendarMethod=UAQ`)
    .then((response) => {
      if (!response.ok) {
        throw new Error(`HTTP error: ${response.status}`);
      }

      return response.json();
    })
    .then((json) => {
      dateOutput.textContent = json.data.hijri.date;
    });
}

fetchSpecialDays();
