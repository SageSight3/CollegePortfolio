<?php
	error_reporting(0); //how do suppress loop warnings?
	require("Login/check.php");
	
	echo "<!DOCTYPE html>
<html>
	<head>
		<title>Add a Photo</title>
	</head>
	<body>
		<form action='AddPhoto.php' method='POST' enctype='multipart/form-data'>
			<input type='file' required='required' id='fileUpload' name='fileUpload'><br>
			
			<!--https://www.geeksforgeeks.org/how-to-specify-that-a-user-can-enter-more-than-one-value-in-an-input-element-in-html5/#-->
			<!--look into better ways for keyword input?-->
			<label for ='SageKeywords'>SageKeywords - For now, no spaces in SageKeywords. Separate words with a comma and space: (coin, split, railgun)</label>
			<input type='text' id='SageKeywords' name='SageKeywords'><br>
			<input type='submit' value='Upload'>
		</form>
		<a href='Login/Protected.php'><p>Home</p></a>
	</body>
</html>";
	
	//$photo = isset($_FILES['fileUpload']['name']) ? $_FILES['fileUpload']['name']: '';
	$SageKeywords = preg_split( "/, /", $_REQUEST['SageKeywords']);
	//print_r($photo);
	
	$imgAttr = getimagesize($_FILES['fileUpload']['tmp_name']);
	//print_r($imgAttr);
	$imgHeight = $imgAttr[1];
	echo $imgHeight . '<br>';
	$imgWidth = $imgAttr[0];
	echo $imgWidth . '<br>';
	$imgFormat = $imgAttr['mime'];
	echo $imgFormat . '<br>';
	$imgData = file_get_contents($_FILES['fileUpload']['tmp_name']);
	//echo $imgData;
	
	if($imgHeight == NULL | $imgWidth == NULL | $imgFormat == NULL) {
		echo "That not a photo :cry:";
		exit(0);
	}
	
	$dbHandle = new PDO('mysql:host=localhost;dbname=nations', 'nations', 'nations!');
	$photoAdd = $dbHandle->prepare("INSERT INTO SagePhotos (PhotoData, Height, Width, Format) VALUES (?, ?, ?, ?)");
	if ($photoAdd->execute(array($imgData, $imgHeight, $imgWidth, $imgFormat))) {
		//is there better way to do this?
		$id = "";
		foreach($dbHandle->query("SELECT MAX(ID) FROM SagePhotos") as $value) { //https://www.w3schools.com/sql/func_mysql_max.asp
			$id = $value['MAX(ID)'];
			//echo $value['MAX(ID)']; //must ask for MAX(ID) in assignment, as well
		}
		//echo $id;
		foreach($SageKeywords as $kw) {
			if($kw == "") {
				echo "no empty SageKeywords plz";
				exit(0);
			}
			
			$kwAdd = $dbHandle->prepare("INSERT INTO SageKeywords (PhotoID, Keyword) VALUES (?, ?)"); //what difference between strings in "" and ''?
			if($kwAdd->execute(array($id, $kw))) {
				//echo "kw has been added<br>";
			} else {
				//echo "stimki kw add code";
				echo "<a href='AddPhoto.php'><button type='button'>Try Again</button></a>";
				exit(0);
			}
		}
		echo "Photo has been added. <br>";
		$displayReq = $dbHandle->prepare("SELECT Height, Width, Format FROM SagePhotos WHERE ID = ?");
		$displayAttrs = array();
		if($displayReq->execute(array($id))) {
			$displayAttrs = $displayReq->fetchAll();
		}
		//print_r($displayAttrs);
		echo "<img src='GetImage.php?id=" . $id . "' height='" . $displayAttrs[0][0] . "' width='" . $displayAttrs[0][1] . "' type='" . $displayAttrs[0][2] . "'><br>";
		echo "<a href='EditPhoto.php?id=" . $id . "'><button type='button'>Edit</button></a>";
		exit(0);
	} else {		
		echo "Add failed";
		echo "<a href='AddPhoto.php'><button type='button'>Try Again</button></a>";
	}
	echo "<a href='AddPhoto.php'><button type='button'>Try Again</button></a>";
?>