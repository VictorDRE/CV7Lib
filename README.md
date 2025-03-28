# CV7Lib

**CV7Lib** is an Arduino library that allows you to easily decode wind speed and direction from the CV7 anemometer.

---

## 🌬️ Features

- Parses serial data from a CV7 anemometer
- Extracts wind speed and wind direction
- Lightweight and simple to use
- Compatible with most Arduino boards

---

## 🛠️ Installation

You can install this library manually:

1. Download or clone this repository
2. Move the folder to your `Arduino/libraries/` directory
3. Restart the Arduino IDE

(Once accepted, it will also be installable via the Arduino Library Manager.)

---
## 📸 Picture of the CV7-OEM
![image](https://github.com/user-attachments/assets/7203b2c0-4070-418b-9fb2-59beb2d94665)


## 🔌 Usage

```cpp
#include <CV7Lib.h>

CV7Lib cv7;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    cv7.parseData(data);

    Serial.print("Wind Speed: ");
    Serial.print(cv7.getWindSpeed());
    Serial.print(" m/s, Direction: ");
    Serial.println(cv7.getWindDirection());
  }
}
