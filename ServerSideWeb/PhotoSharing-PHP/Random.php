<?php
	require("Login/check.php");
	
	echo "<!DOCTYPE html>
<html>
	<head>
		<title>Random Image Search</title>
	<head>
	<body>
		<p>Click photo to edit it</p><br>";
	
	$randMax = "";
	$dbHandle = new PDO('mysql:host=localhost;dbname=nations', 'nations', 'nations!');
	foreach($dbHandle->query("SELECT MAX(ID) FROM SagePhotos") as $id) { //https://www.w3schools.com/sql/func_mysql_max.asp
		$randMax= $id['MAX(ID)'];
	}
	
	$photoID = rand(1, $randMax);
	$doesExist = false;
	while(!$doesExist) {
		$verify = $dbHandle->prepare("SELECT ID FROM SagePhotos WHERE ID=?");
		if ($verify->execute(array($photoID))) {
			if($verify->rowCount() == 1) {
				$doesExist = true;
			} else {
				$photoID = rand(1, $randMax);
			}
		}
	}
	
	$displayAttrs = array();
	$displayReq = $dbHandle->prepare("SELECT Height, Width, Format FROM SagePhotos WHERE ID = ?");
	if ($displayReq->execute(array($photoID))) {
		$displayAttrs = $displayReq->fetchAll();
	}
	
	//display image
	echo "<a href='EditPhoto.php?id=" . $photoID . "'><img src='GetImage.php?id=" . $photoID . "' height='". $displayAttrs[0][0] . "' width='" . $displayAttrs[0][1] . "' type='" . $displayAttrs[0][2] . "'></a><br>";
	
	echo "<h3>Keywords</h3>";
	foreach($dbHandle->query("SELECT Keyword FROM SageKeywords WHERE PhotoID = $photoID") as $word) {
		echo $word ['Keyword'] . "<br>";
	}
	
	echo "		<br><a href='Random.php'><button type='button'>Next Image</button></a><br>
		<a href='Login/Protected.php'><p>Home</p></a>
	</body>
</html>";
?>