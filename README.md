Penjelasan Kode:
Inisialisasi RTC dan LCD:

RTC menggunakan pustaka RTClib.
LCD diinisialisasi untuk menampilkan data (opsional).
Sensor Kecepatan:

Sensor kecepatan terhubung ke pin interrupt (pin 2).
Fungsi calculateSpeed menghitung kecepatan berdasarkan waktu antara dua pulsa dari sensor.
Loop Utama:

Membaca waktu dari RTC dan menampilkan waktu serta kecepatan di Serial Monitor dan LCD.
Catatan:
Pastikan untuk menginstal pustaka RTClib dan LiquidCrystal di Arduino IDE Anda.
Anda mungkin perlu menyesuaikan keliling roda dan kalibrasi sensor sesuai dengan kebutuhan Anda.
