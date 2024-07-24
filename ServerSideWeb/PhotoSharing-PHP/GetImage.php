<?php
	require("Login/check.php");
	$imgID = $_GET['id'];
	$dbHandle = new PDO('mysql:host=localhost;dbname=nations', 'nations', 'nations!');
	$imgData = "";
	$imgGet = $dbHandle->prepare("SELECT PhotoData from SagePhotos where ID = ?");
	if($imgGet->execute(array($imgID))) {
		$imgData = $imgGet->fetchAll();
	} else {
		exit(0);
	}
	echo $imgData[0][0];
?>