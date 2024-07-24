<?php
	require("Login/check.php");
	
	$id = $_GET['id'];
	
	$dbHandle = new PDO ('mysql:host=localhost;dbname=nations', 'nations', 'nations!');
	$dbHandle->query("DELETE FROM SagePhotos WHERE ID = $id");
	$dbHandle->query("DELETE FROM SageKeywords WHERE PhotoID = $id");
	
	echo "Photo has been deleted";
	echo "<a href='Login/Protected.php'><p>Home</p></a>";
?>