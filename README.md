# Smart Farming IoT dengan ESP32

## Deskripsi Proyek
Proyek ini bertujuan untuk membangun sistem pemantauan otomatis berbasis IoT menggunakan ESP32. Sistem ini dapat memantau kondisi lingkungan pertanian dengan sensor suhu & kelembaban (DHT11), intensitas cahaya (LDR), dan kelembaban tanah. Data yang dikumpulkan akan dikirim secara real-time ke platform ThingSpeak untuk dianalisis dan ditampilkan dalam bentuk visual.

## Fitur Utama
- **Pemantauan otomatis** kondisi tanah dan lingkungan pertanian.
- **ESP32 sebagai pusat kendali** untuk menghubungkan sensor dengan cloud.
- **ThingSpeak sebagai platform** untuk menyimpan dan menampilkan data secara real-time.
- **Aktuator (LED & Buzzer) untuk notifikasi** ketika kondisi tanah kering atau basah.

## Hardware yang Digunakan
- **ESP32** sebagai mikrokontroler utama.
- **DHT11** untuk mengukur suhu dan kelembaban udara.
- **LDR** untuk mengukur intensitas cahaya.
- **Sensor Kelembaban Tanah** untuk memantau kondisi tanah.
- **Resistor 220Ω** untuk membatasi arus pada LED.
- **LED (Merah, Hijau, Biru)** untuk indikasi kondisi tanah.
- **Buzzer** untuk peringatan kondisi kritis.

## Cara Kerja
1. **Pengumpulan Data:** Sensor membaca nilai suhu, kelembaban udara, intensitas cahaya, dan kelembaban tanah secara berkala.
2. **Pengolahan Data:** ESP32 memproses data dan mengontrol LED serta buzzer berdasarkan kondisi tanah.
3. **Pengiriman Data:** Data dikirimkan ke **ThingSpeak** untuk dipantau secara real-time.
4. **Notifikasi Visual & Audio:** LED menyala dan buzzer berbunyi sesuai kondisi kelembaban tanah.

## Instalasi dan Penggunaan
1. **Unduh kode sumber** dari repositori ini.
2. **Hubungkan ESP32 ke jaringan WiFi** dengan mengganti `ssid` dan `password` dalam kode.
3. **Upload kode ke ESP32** menggunakan Arduino IDE.
4. **Buka ThingSpeak** untuk melihat data sensor secara real-time.

## Repositori GitHub
Kode sumber proyek ini dapat diakses di: [GitHub Repository](https://github.com/username/smart-farming-iot) (Ganti dengan repositori Anda).

## Video Demo
Tonton cara kerja alat ini melalui video berikut: [Video Demo](https://youtu.be/demo-video) (Ganti dengan link video Anda).
