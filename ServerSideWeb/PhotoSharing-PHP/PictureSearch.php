<?php
	error_reporting(0); //how do suppress loop warnings?
	require("Login/check.php");
	
	echo "<!DOCTYPE html>
<html>
	<head>
		<title>Picture Search</title>
	</head>
	<body>
		<form action='PictureSearch.php' method='POST'  enctype='multipart/form-data'>
			<label for='search'>Separate SageKeywords with a comma and space (ultrakill, secret, ...)</label>
			<input type='text' id='search' name='search'><br>
			<input type='submit' value='search'>
		</form>
		<a href='Login/Protected.php'><p>Home</p></a><br>
		<p>Click a photo to edit it</p>
	</body>
</html>";

	$search = preg_split("/, /", $_REQUEST['search']);
	
	$SagePhotos = array();
	$index = 0;
	$dbHandle = new PDO('mysql:host=localhost;dbname=nations', 'nations', 'nations!');
	foreach($search as $keyword) {
		$subSearch = $dbHandle->prepare("SELECT PhotoID FROM SageKeywords WHERE Keyword = ?");
		if($subSearch->execute(array($keyword))) {
			$photoIDs = $subSearch->fetchAll();
			foreach($photoIDs as $id) {
				$SagePhotos[$index] = $id[0];
				$index++;
			}
		} else {
			echo "smelli code";
		}
	}
	
	foreach ($SagePhotos as $img) {;
		$displayReq = $dbHandle->prepare("SELECT Height, Width, Format FROM SagePhotos WHERE ID = ?");
		$displayAttrs = array();
		if($displayReq->execute(array($img))) {
			$displayAttrs = $displayReq->fetchAll();
		}
		//print_r($displayAttrs);
		echo "<a href='EditPhoto.php?id=" . $img . "'><img src='GetImage.php?id=" . $img . "' height='" . $displayAttrs[0][0] . "' width='" . $displayAttrs[0][1] . "' type='" . $displayAttrs[0][2] . "'></a><br>";
	}
?>