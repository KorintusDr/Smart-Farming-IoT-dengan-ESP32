#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

const char* ssid = "samping";     
const char* password = "22223333";  
const char* server = "http://api.thingspeak.com/update";
const char* apiKey = "2ODNAAIW5QV2C43E";

// Pin Sensor & Aktuator
#define SOIL_SENSOR_PIN 34
#define LDR_SENSOR_PIN 35
#define DHT_PIN 4
#define DHT_TYPE DHT11

#define LED_MERAH 16   
#define LED_HIJAU 17   
#define LED_BIRU 18    
#define BUZZER 19      

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
    Serial.begin(115200);
    dht.begin();
    WiFi.begin(ssid, password);

    pinMode(LED_MERAH, OUTPUT);
    pinMode(LED_HIJAU, OUTPUT);
    pinMode(LED_BIRU, OUTPUT);
    pinMode(BUZZER, OUTPUT);

    Serial.print("Menghubungkan ke WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\n Terhubung ke WiFi!");
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {

        int soilValue = analogRead(SOIL_SENSOR_PIN);
        float moisturePercentage = map(soilValue, 4095, 0, 0, 100);

        int ldrValue = analogRead(LDR_SENSOR_PIN);
        float lightIntensity = map(ldrValue, 0, 4095, 0, 100);

        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity();

        Serial.println("\n--------------------------------");
        Serial.print(" Kelembaban Tanah: ");
        Serial.print(moisturePercentage);
        Serial.println("%");

        Serial.print(" Intensitas Cahaya: ");
        Serial.print(lightIntensity);
        Serial.println("%");

        Serial.print(" Suhu: ");
        Serial.print(temperature);
        Serial.println("°C");

        Serial.print(" Kelembaban Udara: ");
        Serial.print(humidity);
        Serial.println("%");

        // Kontrol LED & Buzzer berdasarkan kelembaban tanah
        if (moisturePercentage <= 40) {
            // Tanah kering: LED merah menyala, buzzer berbunyi terus menerus
            digitalWrite(LED_MERAH, HIGH);
            digitalWrite(LED_HIJAU, LOW);
            digitalWrite(LED_BIRU, LOW);
            tone(BUZZER, 1000);  // Bunyi terus
        } 
        else if (moisturePercentage > 40 && moisturePercentage <= 60) {
            // Tanah ideal: LED hijau menyala, buzzer berbunyi 1x setiap 2 detik
            digitalWrite(LED_MERAH, LOW);
            digitalWrite(LED_HIJAU, HIGH);
            digitalWrite(LED_BIRU, LOW);
            tone(BUZZER, 1000);
            delay(500);
            noTone(BUZZER);
            delay(1500);
        } 
        else {
            // Tanah sangat basah: LED kuning menyala, buzzer berbunyi lebih cepat (2x dalam 2 detik)
            digitalWrite(LED_MERAH, LOW);
            digitalWrite(LED_HIJAU, LOW);
            digitalWrite(LED_BIRU, HIGH);
            tone(BUZZER, 1000);
            delay(300);
            noTone(BUZZER);
            delay(300);
            tone(BUZZER, 1000);
            delay(300);
            noTone(BUZZER);
            delay(1100);
        }

        // Kirim data ke ThingSpeak
        HTTPClient http;
        String postData = "api_key=" + String(apiKey) + 
                          "&field1=" + String(moisturePercentage) + 
                          "&field2=" + String(lightIntensity) +
                          "&field3=" + String(temperature) +
                          "&field4=" + String(humidity);

        Serial.print(" Mengirim data ke ThingSpeak: ");
        Serial.println(postData);

        http.begin(server);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        int httpResponseCode = http.POST(postData);

        if (httpResponseCode > 0) {
            Serial.println(" Data berhasil dikirim ke ThingSpeak!");
        } else {
            Serial.print(" Gagal mengirim data, kode error: ");
            Serial.println(httpResponseCode);
        }
        http.end();
    } else {
        Serial.println(" WiFi tidak terhubung! Mencoba kembali...");
        WiFi.begin(ssid, password);
    }

    delay(5000);  
