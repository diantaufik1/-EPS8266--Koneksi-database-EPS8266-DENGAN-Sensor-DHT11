<?php
$host = "localhost"; // Nama host atau IP server
$user = "root"; // Username MySQL
$pass = ""; // Password MySQL
$name = "db_sensor"; // Nama database MySQL
// Baca parameter get insert_suhu.php?suhu=x
$suhu = $_GET['suhu'];

// Buat koneksi ke database MySQ
$conn = new mysqli($host, $user, $pass, $name);
// Periksa apakah koneksi sudah berhasil
if ($conn->connect_error) {
die("Koneksi gagal: " . $conn->connect_error);
} //
$sql = "INSERT INTO data (suhu) VALUES ('$suhu')";
// Jalankan dan periksa apakah perintah berhasil dijalankan
if ($conn->query($sql) === TRUE) {
	echo "sukses"; // memberikan informasi bahwa proses insert data berhasil

} else {
	echo "gagal"; // memberikan informasi bahwa proses insert data gagal
}

$conn->close();
?>