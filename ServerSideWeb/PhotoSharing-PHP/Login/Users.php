<?php
	require("LoginCheck.php");
	echo "<!DOCTYPE html>
<html>
	<head>
		<title>Users</title>
	</head>
	<body>
		<h3>Users</h3>
		<table style='border-spacing:0;'>";
		
	$dbHandle = new PDO('mysql:host=localhost;dbname=nations', 'nations', 'nations!');
	foreach($dbHandle->query('SELECT username from SageLogin') as $user) {
		echo "<tr><td style='border-style:solid;'>". $user['username'] . "</td><tr>";
	}
		
	echo "		</table>
	<a href='Protected.php'><p>Home</p></a>
	</body>
</html>";
?>