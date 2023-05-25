<?php

// Check if Needed Parameters are Set
if(isset($_GET["latitude"]) && isset($_GET["longitude"]) 
    && isset($_GET["ph"]) && isset($_GET["temp"])) 
{
    // Get Values from HTTP GET
    $latitude = $_GET["latitude"];
    $longitude = $_GET["longitude"];
    $ph = $_GET["ph"];
    $temperature = $_GET["temp"];

    // Generate Date and Time Value Based on Now
    $date = date("Y-m-d");
    //date_default_timezone_set("Europe/Berlin"); // make sure that right timezone is used
    $time = date("h:i:s");

    // Configuration of Database
    $servername = "localhost";
    $username = "ESP32";
    $password = "esp32io.com";
    $database_name = "stem"; //database name

    // Create MySQL connection from PHP to MySQL server
    $connection = new mysqli($servername, $username, $password, $database_name);
    // Check Connection
    if ($connection->connect_error) {
        die("MySQL connection failed: " . $connection->connect_error);
    }

    // SQL Query Statement
    $sql = "INSERT INTO measurements (latitude, longitude, date, time, ph, temp, status) 
        VALUES ('$latitude', '$longitude', '$date', '$time', '$ph', '$temperature', 1)";

    // Create Record and Check Success
    if ($connection->query($sql) === TRUE) {
        echo "New record created successfully";
    } else {
        echo "Error: " . $sql . " => " . $connection->error;
    }

    //Close Connection to Databaseserver
    $connection->close();

    } else {
        echo "Not all parameters are set in the HTTP request";
    }
?>